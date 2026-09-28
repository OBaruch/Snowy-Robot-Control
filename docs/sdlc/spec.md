# Specification: Snowy (as built, reconstructed)

← [intent.md](intent.md) · Next: [plan.md](plan.md) · Back to [README](../../README.md)

> **Reconstructed artifact.** These requirements were derived from the original report and code. It records **what was specified and what was implemented**, including gaps. Nothing here asks for the original code to change.

**Implementation status legend**

- ✅ **Implemented in repository code** (`src/control/control.ino`)
- 📄 **Implemented only in the report annex firmware** (not in this repository's code)
- 📱 **Implemented in the Android app** (per report screenshots; app source not in repository)
- 🔌 **Hardware only** (per report)
- ⚠️ **Placeholder / incomplete**: the key is parsed but the handler is empty or broken
- ❓ **Unknown**

## 1. Functional requirements

### 1.1 Command channel

| ID | Requirement | Status |
|---|---|---|
| FR-01 | The ESP32 joins a Wi-Fi network and exposes an HTTP server on port 80 | ✅ |
| FR-02 | Commands arrive as `GET /<json>`, where `<json>` is a one-key JSON object | ✅ (server) · 📱 (client) |
| FR-03 | The firmware URL-decodes `"`, `{` and `}` and parses the JSON | ✅ |
| FR-04 | Invalid JSON is logged: `El comando no tiene el formato JSON` ("the command is not in JSON format") | ✅ |
| FR-05 | Every request is answered with `HTTP/1.1 200 OK` and body `OK` | ✅ |
| FR-06 | The ESP32 is reachable at the fixed address `192.168.43.211` | ⚠️ Static IP declared but not applied; the repo value is `.158` |

### 1.2 Commands (animatronic side)

| ID | JSON key (firmware) | Sent by app | Expected behavior | Repository code | Report annex |
|---|---|---|---|---|---|
| FR-10 | `musica` | `{"musica":"musica"}` | Play the Christmas song | ✅ `PlayNumber("b")` | 📄 same |
| FR-11 | `baila` | `{"baila":"baila"}` | Dance | ⚠️ Servo sweep with syntax errors | ⚠️ empty |
| FR-12 | `hola` / `saludo` | `{"saludo":"saludo"}` | Greet (wave) | ⚠️ reads `hola`, empty | 📄 servo1→0°, servo2→90° |
| FR-13 | `si` | `{"si":"si"}` | Nod | ⚠️ empty | 📄 servo1 0°→120° |
| FR-14 | `no` | `{"no":"no"}` | Shake head | ⚠️ empty | 📄 servo2 0°→120° |
| FR-15 | `luces` | `{"luces":"luces"}` | RGB light sequence | ⚠️ empty | 📄 9-step sequence |
| FR-16 | `color` | `{"color":"1"\|"2"}` | Set eye color (1 red, 2 green, 3 blue) | — not read | 📄 implemented |
| FR-17 | `cuantofaltaparanavidad` | `{"cuantofaltaparanavidad":…}` | Say "N weeks until Christmas" | ⚠️ commented LED write | 📄 hard-coded "4 weeks" |
| FR-18 | `hora` | `{"hora":"<time>"}` | Show the time ("on LCD") | ⚠️ empty; compares to `"hora"` | ⚠️ empty |
| FR-19 | `clima` / `temperatura` | `{"temperatura":"<v>"}` | Show the weather ("on LCD") | ⚠️ reads `clima`, empty | ⚠️ empty |
| FR-20 | `selfie` | `{"selfie":"selfie"}` | Rotate 360° | ⚠️ empty | ⚠️ empty |

### 1.3 Phone-side functions

| ID | Requirement | Status |
|---|---|---|
| FR-30 | Greet the user by voice on launch ("Hola soy snowy") | 📱 |
| FR-31 | Start speech recognition from one large button | 📱 |
| FR-32 | Speak and display the current time | 📱 |
| FR-33 | Fetch the weather from OpenWeatherMap by GPS and display it | 📱 |
| FR-34 | Take a selfie with the front camera | 📱 |
| FR-35 | Pick a contact and call them ("Llama a familia") | 📱 |

### 1.4 Audio

| ID | Requirement | Status |
|---|---|---|
| FR-40 | Store clips in flash as 8 kHz / mono / unsigned 8-bit PCM WAV arrays | ✅ (`SoundData.h`, verified from headers) |
| FR-41 | Compose phrases by queuing clips from one-character codes (`b n f p s 1–5`) | ✅ (`PlayNumber`, `AddNumberToSequence`) · ⚠️ `5` has no clip |
| FR-42 | Output through DAC GPIO 25 → LM386 → 3 W speaker | ✅ (DAC) · 🔌 (amp/speaker) |

### 1.5 Time

| ID | Requirement | Status |
|---|---|---|
| FR-50 | Sync the clock from `pool.ntp.org` at boot and log it | ✅ (timezone offset incorrect for Guadalajara) |

## 2. Hardware requirements

| ID | Requirement | Status |
|---|---|---|
| HW-01 | ESP32 dev board, 5 V over USB | 🔌 |
| HW-02 | 3 × SG90 servos on GPIO 18/19/21 | ✅ (pins) · 🔌 |
| HW-03 | 2 RGB LEDs in series on GPIO 13/12/14 (PWM 5 kHz, 8-bit) | 📄 · 🔌 |
| HW-04 | Solar panel (18 V max) → LM317/TIP122 charger with Zener cutoff and LED → 12 V 7 Ah lead-acid battery | 🔌 |
| HW-05 | LM7805 regulator, 12 V → 5 V | 🔌 |
| HW-06 | LM386 amplifier powered from 12 V, 10 µF coupling from the DAC | 🔌 |

## 3. Non-functional requirements

| ID | Requirement | Assessment |
|---|---|---|
| NFR-01 | Sustainable power (solar) | 🔌 Claimed and photographed |
| NFR-02 | Minimal, energy-efficient circuitry | 🔌 Circuits chosen on a breadboard for fewest parts; linear regulation is not the most efficient option |
| NFR-03 | Accessible: usable without sight | 📱 Voice in, speech out |
| NFR-04 | "Secure" control channel | ⚠️ The report treats the JSON format as security; there is no authentication |
| NFR-05 | Delivered within one week | Report timeline |

## 4. Interfaces

**HTTP request** (client → ESP32)

```
GET /{"<key>":"<value>"} HTTP/1.1        (quotes/braces may arrive as %22 %7B %7D)
```

**HTTP response** (ESP32 → client)

```
HTTP/1.1 200 OK
Content-Type: text/html


OK
```

**Serial log:** 115200 baud. Logs the connection progress, time, IP, each raw request, the decoded JSON, the `musica` value, and servo positions.

## 5. Acceptance (historical)

The report's conclusion states that all challenge requirements were verified on the physical prototype. The **repository firmware alone does not satisfy FR-11 through FR-20**, because it does not compile and most handlers are empty. That is the state in which it was archived.
