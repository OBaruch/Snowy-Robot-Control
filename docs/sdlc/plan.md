# Plan: Snowy

← [spec.md](spec.md) · Back to [README](../../README.md)

> **Reconstructed artifact.** Part A reconstructs the plan the team followed in 2019, from the report's methodology. Part B records the plan used in the later **repository modernization**, which reorganized and documented the project without touching the code.

---

## Part A: Original build plan (2019, reconstructed)

| Phase | Day | Work items | Outputs | Spec coverage |
|---|---|---|---|---|
| A1: Kick-off | 1 | Form the multidisciplinary team; inventory materials and skills; choose the snowman concept (two polystyrene balls give a fast housing) | Concept | Intent |
| A2: Design | 2 | Size the power budget; design the charging, regulation and indicator circuits; split functions between the ESP32 and the app; start the App Inventor app | Circuit drafts, app skeleton | HW-04, HW-05, FR-30–35 |
| A3: Procurement | 3 | Obtain the solar cell, battery and servos | Parts | HW-02, HW-04 |
| A4: Audio and actuators | 4–5 | Get an LM386 amplifier and fight noise; record and convert clips (Audacity → `xxd -i` → `SoundData.h`); integrate XT_DAC_Audio; test servos; breadboard-test the regulators and indicators; buy decorations and a base box | Working audio, servo tests, `SoundData.h` | FR-40–42, HW-06, FR-11–14 |
| A5: Integration | 6 | Assign pins; wire everything; decorate; implement JSON commands in the firmware and matching URLs in the app | Final prototype | FR-01–20 |
| A6: Report | ~Dec 5–8 | Write the report (Word → PDF) with an annex of the app and firmware code | `ReporteRetoProyectoModularDIVEC.pdf` | — |
| A7: Archive | 20 Feb 2021 | Upload the firmware, audio header, library ZIPs and report to GitHub under the MIT license | This repository (original commits) | — |

### Firmware tasks (derived from the code and report)

1. Wi-Fi connect + HTTP server (`setup`, `ReadIncomingRequest`).
2. URL decoding and ArduinoJson v5 parsing (`loop`).
3. Audio: WAV arrays, `XT_Wav_Class` objects, `PlayNumber` / `AddNumberToSequence`.
4. Servos: attach on 18/19/21; movement routines (`setServos`, and gestures in the annex).
5. RGB LEDs: LEDC PWM set-up and sequences (annex only).
6. NTP time (`printLocalTime`).
7. *Left incomplete in the archived file:* `hora`, `clima`, `selfie`, the `cinco` clip, and the syntax of the `baila` routine.

---

## Part B: Repository modernization plan (documentation only)

**Principle:** modernize the repository, not the project. The source code must stay byte-for-byte identical.

| Step | Task | Result |
|---|---|---|
| B1 | Inventory every file, inspect the code, the library ZIPs (versions from `library.properties`), the PDF text, and **every PDF page visually** (schematics, screenshots, block code, photos) | Context recovered; project classified as an Academic / University Project |
| B2 | Cross-check the sources and record contradictions instead of resolving them by assumption | [project-context.md § Contradictions](../project-context.md#contradictions-found) |
| B3 | Restructure with `git mv` (history preserved): `control.ino` + `SoundData.h` → `src/control/` (Arduino sketch-folder rule); PDF → `docs/original/` (the browser-download suffix " (1)" was dropped from the name); `LibreriasNesesarias/*.zip` → `third_party/arduino-libraries/` | Clean top level |
| B4 | Extract key figures from the PDF into `docs/images/` (unmodified image streams) | Visuals for the docs |
| B5 | Write docs: README, project-context, assignment, report summary, architecture, code-overview, possible-improvements | Navigable documentation |
| B6 | Write the SDLC artifacts: intent, spec, plan (this file) | Traceable requirements with implementation status |
| B7 | Add `AGENTS.md` (guardrails for automated contributors: code is frozen) and a minimal `.gitignore` | Safe future maintenance |
| B8 | Verify that the SHA-256 hashes of `control.ino` and `SoundData.h` match the pre-refactor files; verify that all relative links resolve | Integrity check |
| B9 | Open a pull request from a dedicated branch | Reviewable change |

### Explicitly not done

- No code edits, formatting, renames inside files, dependency upgrades or bug fixes.
- No build system, CI, Docker, linters or test framework (none existed originally).
- No deletion of any original file.

### Integrity reference

SHA-256 of the preserved source files (identical before and after the reorganization):

```
cd52ed47e8f1529fe64af2a879b0ec4c751d1b8bae00aa4ff243e8ba1555450c  src/control/control.ino
386e238712e222402ea385686429ef645aa65efd44a40e20c4a9cab1fde4cff5  src/control/SoundData.h
```
