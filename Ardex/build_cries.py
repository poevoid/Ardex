#!/usr/bin/env python3
"""Batch OGG -> ArdVoice FX bank, preserving the existing sprite data.

Requires Python 3, FFmpeg, Java and the bundled vocoder0.2.jar.
The original vocoder accepts unsigned 8-bit mono 8000 Hz WAV only; this
front end decodes OGG, runs the original codec, and packs its exact bytes.
"""
import argparse
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent
FX = ROOT / "fxdata"
COUNT = 251
PAGE = 256
MAX_FLASH = 16 * 1024 * 1024


def files_by_entry(directory):
    found = {}
    for path in sorted(directory.glob("*.ogg")):
        match = re.search(r"(?:^|[^0-9])0*([0-9]{1,3})$", path.stem)
        if not match or not 1 <= int(match.group(1)) <= COUNT:
            raise ValueError(f"Cannot find entry number (1..251) in {path.name}")
        number = int(match.group(1))
        if number in found:
            raise ValueError(f"Duplicate entry {number}: {found[number]} and {path}")
        found[number] = path
    return found


def encode(path, number, quality, ffmpeg, jar, temporary):
    wav = temporary / f"p{number:03d}.wav"
    subprocess.run([ffmpeg, "-nostdin", "-loglevel", "error", "-y",
                    "-i", str(path), "-ac", "1", "-ar", "8000",
                    "-c:a", "pcm_u8", str(wav)], check=True)
    run = subprocess.run(["java", "-jar", str(jar), str(wav),
                          "-q", str(quality), "-anp", f"p{number:03d}"],
                         text=True, stdout=subprocess.PIPE,
                         stderr=subprocess.PIPE, check=True)
    match = re.search(r"const\s+uint8_t\s+\w+\[\]\s+PROGMEM\s*=\s*\{([^}]+)\}", run.stdout, re.S)
    if match is None:
        raise ValueError(f"No ArdVoice array for {path.name}: {run.stdout} {run.stderr}")
    data = bytes(int(token, 16) for token in re.findall(r"0x[0-9a-fA-F]{2}", match.group(1)))
    if len(data) < 2:
        raise ValueError(f"Empty ArdVoice array for {path.name}")
    chunks = data[0] | ((data[1] & 15) << 8)
    coeffs = data[1] >> 4
    if not 1 <= chunks <= 4095 or coeffs > 10 or len(data) != 2 + chunks * (2 + coeffs):
        raise ValueError(f"Invalid ArdVoice header/length for {path.name}: {len(data)} bytes")
    return data


def build(args):
    sources = files_by_entry(args.audio_dir)
    missing = [i for i in range(1, COUNT + 1) if i not in sources]
    if missing and not args.allow_missing:
        raise ValueError(f"Missing {len(missing)} cries: {', '.join(map(str, missing))}")
    if not sources and not args.allow_missing:
        raise ValueError("No .ogg files found")
    if sources and not shutil.which(args.ffmpeg):
        raise ValueError(f"FFmpeg is unavailable: {args.ffmpeg}")
    if sources and not shutil.which("java"):
        raise ValueError("Java is unavailable")
    base = (FX / "sprites-data.bin").read_bytes()
    header = (FX / "sprites-header.h").read_text()
    previous_size = int(re.search(r"FX_DATA_BYTES\s*=\s*(\d+)", header).group(1))
    if len(base) != previous_size:
        raise ValueError(f"Sprite bytes changed: expected {previous_size}, got {len(base)}")
    save_page = int(re.search(r"FX_SAVE_PAGE\s*=\s*0x([0-9a-fA-F]+)", header).group(1), 16)

    encoded = {}
    with tempfile.TemporaryDirectory() as work:
        for i, path in sources.items():
            encoded[i] = encode(path, i, args.quality, args.ffmpeg, args.vocoder, Path(work))
            print(f"{i:03d} {path.name}: {len(encoded[i])} bytes")

    # Table entry 0 is the first sprite/cry (No. 1); zero marks missing audio.
    offsets = bytearray(COUNT * 3)
    payload = bytearray()
    for i in range(1, COUNT + 1):
        if i in encoded:
            addr = len(base) + len(offsets) + len(payload)
            offsets[(i - 1) * 3:i * 3] = addr.to_bytes(3, "little")
            payload.extend(encoded[i])
    bank = offsets + payload
    data = base + bank
    pages = (len(data) + PAGE - 1) // PAGE
    start_page = save_page - pages
    if start_page < 0 or save_page * PAGE > MAX_FLASH:
        raise ValueError(f"FX data does not fit before save page: {len(data)} bytes")
    # The development-upload .bin ends at the chip's last page. The original
    # uploaded file includes the 16 reserved save pages after data padding.
    save_pages = MAX_FLASH // PAGE - save_page
    full = data + b"\xff" * (pages * PAGE - len(data) + save_pages * PAGE)

    header = re.sub(r"FX_DATA_PAGE\s*=\s*0x[0-9a-fA-F]+", f"FX_DATA_PAGE  = 0x{start_page:04X}", header)
    header = re.sub(r"FX_DATA_BYTES\s*=\s*\d+", f"FX_DATA_BYTES = {len(data)}", header)
    header += f"\n// 251 little-endian 24-bit cry addresses; zero means no cry.\nconstexpr uint24_t cryIndex = 0x{len(base):06X};\n"
    FX.mkdir(parents=True, exist_ok=True)
    (FX / "cries.bin").write_bytes(bank)
    (FX / "fxdata-data.bin").write_bytes(data)
    (FX / "fxdata.bin").write_bytes(full)
    (FX / "fxdata.h").write_text(header)
    (FX / "fxdata-save.bin").write_bytes(b"\xff\xff")
    print(f"Created {len(encoded)}/{COUNT} cries; FX_DATA_PAGE=0x{start_page:04X}; data={len(data)} bytes")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("audio_dir", type=Path, help="Folder of numbered .ogg cries (1.ogg, p001.ogg, etc.)")
    parser.add_argument("--quality", type=int, choices=range(11), default=4)
    parser.add_argument("--vocoder", type=Path, default=ROOT / "vocoder0.2.jar")
    parser.add_argument("--ffmpeg", default="ffmpeg")
    parser.add_argument("--allow-missing", action="store_true", help="For partial hardware testing only")
    args = parser.parse_args()
    try:
        build(args)
    except (ValueError, OSError, subprocess.CalledProcessError) as error:
        parser.exit(1, f"Error: {error}\n")


if __name__ == "__main__":
    main()
