#pragma once

// Select the pin feeding the mono amplifier:
// 1 = speaker 1 (Arduino pin 5 / PC6)
// 0 = speaker 2 (Arduino pin 13 / PC7, or pin 6 / PD7 with alternate wiring)
//
// This Arduboy Jr project defaults to speaker 1, the usual mono amp input.
// Set it to 0 if the amp input is wired to speaker 2 instead.
#ifndef ARDEX_AUDIO_SPEAKER1
#define ARDEX_AUDIO_SPEAKER1 1
#endif
