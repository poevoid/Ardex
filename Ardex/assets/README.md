# Ardex with FX cries

This project preserves the supplied working sprite data and adds a cry player
based on ArdVoice. The FX image includes all 251 OGG cries supplied in
`cries.7z`. Press **A** to play the selected entry's cry. Left and right
change entries; B toggles shiny sprites.

## Build the 251 cry bank on Windows

1. Install Java and FFmpeg so `java` and `ffmpeg` work in Command Prompt.
   Python 3 must also be available as `python`.
2. Extract the original `cries.7z` archive into one directory containing
   **251 OGG files** numbered by entry:
   `1.ogg` through `251.ogg`, `001.ogg` through `251.ogg`, or
   `p001.ogg` through `p251.ogg`. Each file must end in its unique entry
   number. The converter checks missing and duplicate numbers.
3. In Command Prompt run:

   ```bat
   cd path\to\Ardex
   build_cries.cmd "C:\path\to\cries"
   ```

   Optional: `build_cries.cmd "C:\path\to\cries" --quality 6`
   (default quality 4). The original vocoder is included unchanged.
   `build_cries.py` adds OGG decoding, 251 file batching, validation and
   indexed FX packing to the original vocoder's output.

The converter creates `fxdata\fxdata.bin`, `fxdata\fxdata-data.bin`,
`fxdata\fxdata.h`, and `fxdata\cries.bin`. Compile `Ardex.ino` with
Arduboy2 and ArduboyFX installed (ArduboyG, SpritesU and the FX adaptation
of ArdVoice are bundled under `src`). Upload **both** the newly compiled
sketch and the newly generated development data `fxdata.bin` to the same
Arduboy FX. Merely uploading the sketch leaves the FX flash pointing at the
old data page.

The bundled generated binary already contains all 251 real cries. Run the
converter again if you change any sound files or select another quality.
At the default quality, the cry bank is 66,517 bytes, the combined FX data
is 2,988,867 bytes, and `FX_DATA_PAGE` is `0xD254`.

## Layout

The first 2,922,350 bytes of FX data are an exact copy of the supplied
sprite data. The appended `cries.bin` starts with 251 little endian 24 bit
FX data addresses (No. 1 is entry zero); a zero address means no cry.
The compressed ArdVoice records follow the table. Each record retains its
original two byte header (12 bit chunk count and 4 bit coefficient count)
and `chunk count * (2 + coefficient count)` bytes of frames.

`fxdata.bin` is padded to pages and includes the original reserved save
pages at the end. The generated `FX_DATA_PAGE` accounts for the increased
length; the sprite address constants stay the same. The Arduino code looks
up one 24 bit cry address when A is pressed. ArdVoice prefetches frames from
FX in `service()`, then its timer interrupt decodes buffered records in RAM.
This keeps the interrupt from disturbing sprite reads through FX SPI.

The existing `fxdata.txt` adds `raw_t cryIndex = "cries.bin"` after the
sprites. The included Python builder creates the upload image directly,
using the original generated sprite header as its source for page and sprite
constants. Do not run an unrelated FX data build over the generated files
unless you also upload its matching `fxdata.bin` and compile its matching
`fxdata.h`.

## Limits and verification

The converter rejects malformed vocoder output, missing files and images that
exceed the chip's available space. The ArdVoice adaptation targets the AVR
Timer4 speaker setup used by the supplied library. Playback on a physical
Arduboy cannot be verified here without the target Arduino toolchain and
device.

The ArdVoice source retains the original Apache 2.0 attribution. See
`src/ARDVOICE-LICENSE.txt`; the Ardex project license remains in `LICENSE`.
