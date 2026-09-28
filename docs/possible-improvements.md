# Possible Improvements

← Back to [README](../README.md)

> **None of the items below have been applied.** The source code in `src/control/` is deliberately preserved exactly as it was originally written, to keep the historical record of the project intact. This list is for readers who want to understand the code's limitations, or who might build a new version separately.

Each item cites where the issue can be seen. Severity is a rough guide: **Build** (prevents compilation), **Bug** (wrong behavior), **Risk** (security or robustness), **Style** (maintainability).

## Build blockers

| # | Severity | Where | Issue | Possible fix |
|---|---|---|---|---|
| 1 | Build | `control.ino:26`, `SoundData.h` | `cinco_wav` is referenced but not defined | Add the "cinco" clip to `SoundData.h`, or drop the `5` code |
| 2 | Build | `control.ino:256` | `while (int pos <= 180)`: declaration inside the condition | `while (pos <= 180)` |
| 3 | Build | `control.ino:261, 270` | `break` without `;` | `break;` |

## Behavioral bugs

| # | Severity | Where | Issue |
|---|---|---|---|
| 4 | Bug | `control.ino:269` | The return sweep tests `pos==0` instead of `posD==0`. It only ends because `posD >= 0` eventually fails |
| 5 | Bug | `control.ino:223` | `clima >= 0 \|\| clima <= 0` is always true (except NaN), so the block runs on every command |
| 6 | Bug | App vs. firmware | The app sends `{"hora":"<time>"}`, but the firmware checks `hora == "hora"`. The app sends `temperatura`, but the firmware reads `clima`. The app sends `saludo`, but the firmware reads `hola`. "color azul" and "color verde" both send `"2"` |
| 7 | Bug | `control.ino:35–36` | `gmtOffset_sec = 3600` (UTC+1) with an extra hour of DST. Guadalajara was UTC−6 in 2019. The commented `hora - 7` hints at this mismatch |
| 8 | Bug | `control.ino:126–127` | The log prints SSID `ATT_Internet_En_Casa_1937`, but the code connects to `virus` |
| 9 | Bug | `control.ino:54, 141` | The static IP is declared but never applied (`WiFi.config` is commented out), and its value (`.158`) differs from the comment and the app (`.211`). The app's hard-coded IP only works if DHCP assigns `.211` |
| 10 | Bug | `control.ino:177–182` | Request parsing assumes an exact `GET /… HTTP/1.1` shape and decodes only `%22`, `%7B` and `%7D`. Spaces or accented characters (`%20`, `%C3%AD`) would break the JSON |
| 11 | Bug | `control.ino:70–79` | `ReadIncomingRequest` returns the previous request (`myresultat` is global) if the new one has no `HTTP/1.1` line |
| 12 | Bug | `control.ino:163–170` | Audio `FillBuffer()` is not called while the loop busy-waits for data or runs blocking `delay()` sequences, so audio can stutter or stop |
| 13 | Bug | Report annex | `cuantofaltaparanavidad` always says "4 weeks": the value is hard-coded rather than computed from the date |

## Security and robustness

| # | Severity | Issue |
|---|---|---|
| 14 | Risk | Wi-Fi SSID and password are hard-coded in the source (and published). Move them to an untracked config header |
| 15 | Risk | "Security via JSON" is not security: anyone on the LAN can send commands. Real protection would need a shared token, or at minimum restricting to known clients |
| 16 | Risk | `StaticJsonBuffer<100>` is small, and inputs are not length-checked |
| 17 | Risk | Only one client is handled at a time, and a slow client blocks everything (busy-wait with no timeout) |

## Maintainability and modernization

| # | Severity | Suggestion |
|---|---|---|
| 18 | Style | `Serial.begin(115200)` is called twice. The global `mensajeJSON` is shadowed by a local one. `ledVerde` is never used |
| 19 | Style | Replace the chain of `if` blocks with a table of `{key, handler}` |
| 20 | Style | Replace blocking `delay()` choreography with a non-blocking state machine (`millis()`) |
| 21 | Modernization | ArduinoJson v5 is obsolete. v6/v7 use `JsonDocument` / `deserializeJson` |
| 22 | Modernization | The ESP32 Arduino core 3.x replaced `ledcSetup`/`ledcAttachPin` (used in the report version) with `ledcAttach` |
| 23 | Modernization | Use the ESP32 `WebServer` library with proper routes and query parameters (`/cmd?c=musica`) instead of JSON in the path |
| 24 | Modernization | Reconcile the repository firmware with the report annex so that one complete version exists |
| 25 | Preservation | Recover the MIT App Inventor project (`.aia`), if it still exists, and archive it alongside the firmware |

## Hardware notes (from the report)

- The report expresses µF values as "mF" in its component tables.
- Lead-acid charging relies on Zener thresholds and an LM317. A dedicated solar charge controller would give proper bulk, absorption and float stages.
- The LM7805 dissipates (12 − 5) V × I as heat. A buck converter would be more efficient, which matters for an energy-efficiency challenge.
