# Project Context

← Back to [README](../README.md)

This document reconstructs where Snowy came from, using evidence found in the repository. Every statement carries one of these labels:

- **Confirmed**: directly supported by a file in this repository.
- **Inferred**: a reasonable deduction from the available files, but not stated explicitly.
- **Unknown**: the repository does not provide enough information to determine this.

## Classification

**Project origin: Academic / University Project** (Confirmed)

Evidence: the cover page of `docs/original/ReporteRetoProyectoModularDIVEC.pdf` carries the Universidad de Guadalajara / CUCEI header. It states that the work is presented *"para acreditar los módulos"* (to earn credit for the modules) of three engineering degrees, and it names an academic advisor.

It was **not** ordinary coursework for a single class. It was an intensive, one-week **challenge** ("Reto") run inside the *DIVEC Innovación 2019* program.

## Summary of Known Facts

| Topic | Value | Status |
|---|---|---|
| University | Universidad de Guadalajara, Centro Universitario de Ciencias Exactas e Ingenierías (CUCEI) | Confirmed (report cover) |
| Division / Department | División de Electrónica y Computación / Departamento de Ciencias Computacionales | Confirmed |
| Degree programs | Ingeniería en Comunicaciones y Electrónica (INCE), Ingeniería Robótica (INRO), Ingeniería Fotónica (IGFO) | Confirmed |
| Academic framework | *Proyecto modular* (UdeG's modular project credit), via the "Reto de Proyectos Modulares" within **DIVEC Innovación 2019** | Confirmed (report introduction) |
| Team | Omar Baruch Morón López, Brenda Isabel Estrada Hernández, David Alejandro Rodríguez Preciado | Confirmed (cover) |
| Advisor | Juan Carlos Aldaz Rosas | Confirmed (cover) |
| Report date | Thursday, 5 December 2019, Guadalajara, Jalisco. PDF metadata: created 8 December 2019 with Microsoft Word for Office 365 | Confirmed |
| Duration | One week (six working days described in the methodology) | Confirmed (report) |
| GitHub upload | 20 February 2021, three commits by "Baruch Lopez" ("Initial commit", "Add files via upload" × 2) | Confirmed (git history) |
| Repository author | Baruch Lopez (MIT license holder, 2021) | Confirmed (`LICENSE`) |
| Which team member wrote the firmware | Not stated | Unknown |
| Which team member built the Android app | Not stated | Unknown |
| Whether the uploaded `control.ino` is earlier or later than the report annex listing | Not stated | Unknown (see [code-overview.md](code-overview.md#differences-between-the-repository-code-and-the-report-annex)) |
| Challenge results / grading | Not included | Unknown |

## Goal of the Project

As stated in the report (Confirmed):

> Build a Christmas-themed animatronic named "Snowy" that meets the DIVEC challenge requirements (sustainable energy, minimal circuitry, controlled lighting, ≥ 2 degrees of movement, community impact) and additionally serves **visually impaired people** by making all of its functions available through **voice commands** on a mobile phone.

The report presents Snowy as *sustainable* (solar powered) and *inclusive* (voice-first interaction).

## Scope

In scope, according to the report:

- Solar energy harvesting, a lead-acid battery charger with an over-voltage cutoff and LED indicator, and 5 V regulation for the ESP32.
- An ESP32 firmware acting as a Wi-Fi HTTP server that receives JSON commands.
- An Android app (MIT App Inventor) with speech recognition, text-to-speech, weather lookup, time, selfie, and calling a contact.
- Three SG90 servos for simple dances and head gestures.
- RGB LED "eyes" with light sequences.
- Local audio playback: WAV files converted to C arrays and played through the ESP32 DAC and an LM386 amplifier.

Out of scope or not present:

- Any LCD. The code has `//mostrar en lcd` ("show on LCD") placeholders, but no LCD appears in the report's hardware.
- Real security. The report calls JSON encoding a "security" measure; technically it is only a message format.

## Timeline (from the report's methodology)

| Day | Activity |
|---|---|
| 1 | Team formed; inventory of available materials and skills; "Snowy" chosen because two decorated polystyrene balls made the housing quick to build |
| 2 | Power-conversion circuits conceptualized; microcontroller functions defined; app development started |
| 3 | Solar cell, battery and servomotors obtained |
| 4–5 | Audio was the hardest part: an amplifier bought online, initial noise interference; servo tests; decorations and a base box bought; regulator and indicator circuits tested on a breadboard |
| 6 | Integration: pin assignment, wiring, decoration |

## What Exists in the Repository vs. What Was Built

| Artifact | In repo? |
|---|---|
| ESP32 firmware | Yes: `src/control/control.ino` (a version that differs from the report annex) |
| Audio data | Yes: `src/control/SoundData.h` (9 clips; the `cinco` / "five" clip referenced by the code is missing) |
| Arduino libraries | Yes: 3 ZIPs in `third_party/arduino-libraries/` |
| Project report | Yes: `docs/original/ReporteRetoProyectoModularDIVEC.pdf` |
| Android app source (`.aia`) or APK | **No**. Only screenshots in the report |
| Original WAV recordings | **No**. Only the converted byte arrays |
| Schematic source files | **No**. Only images in the report |
| Photos | Only those embedded in the report (page 37) |

## Contradictions Found

These are recorded as found. None has been resolved by assumption.

1. **Firmware versions:** the repository `control.ino` and the report annex listing differ substantially (LEDs, servo handling, command keys). The report's Figure 7 fragment matches the repository file (`hola` key), while the annex uses `saludo`.
2. **Number of servos / degrees of freedom:** the Actuators section says **3 servos** giving three rotation axes. The Conclusion says *"tres grados de movimiento por medio de dos servomotores"* (three degrees of movement using **two** servomotors).
3. **Number of RGB LEDs:** the Lighting section says "2 LEDs RGB" and then "los 3 leds RGB" in the next paragraph.
4. **ESP32 clock:** the report states a maximum frequency of "24 MHz". The ESP32's Xtensa LX6 is specified up to 240 MHz, so this is likely a typo (Inferred).
5. **Capacitor values:** the regulator table lists "10 mF" and "0.1 mF", but the regulator figure shows 0.33 µF and 0.1 µF. The amplifier table lists "250 mF" and "0.05 mF", but the schematic shows 250 µF and 0.05 µF. "mF" appears to be used for µF (Inferred).
6. **Static IP:** the report and app use `192.168.43.211`. The repository code declares `192.168.43.158` (with a comment `//http://192.168.43.211`) and never applies it (`WiFi.config` is commented out).
7. **Command payloads:** the app sends `{"hora":"<current time>"}` and `{"temperatura":"<value>"}`, but the firmware compares `hora == "hora"` and reads a `clima` key. The app sends `{"saludo":"saludo"}`, while the repository firmware reads `hola`. The app sends `"color":"2"` for both "color azul" and "color verde".

## Related Documents

- [assignment.md](assignment.md): challenge requirements
- [report.md](report.md): full technical summary of the report
- [sdlc/intent.md](sdlc/intent.md): reconstructed intent
