# Code Overview

← Back to [README](../README.md)

> The files described here are the **original implementation** and are intentionally left unmodified. This document explains them. It does not change them. Line numbers refer to `src/control/control.ino` as stored in this repository.

## Files

| File | Size | Role |
|---|---|---|
| [`src/control/control.ino`](../src/control/control.ino) | 294 lines (CRLF line endings) | ESP32 Arduino sketch: Wi-Fi HTTP server, JSON command parsing, servo motion, audio playback |
| [`src/control/SoundData.h`](../src/control/SoundData.h) | ~620 KB | WAV clips embedded as `const unsigned char` arrays (generated with `xxd -i`) |
| [`third_party/arduino-libraries/*.zip`](../third_party/arduino-libraries/) | — | Unmodified third-party Arduino libraries used by the sketch |

## `control.ino`

### Includes and dependencies

| Include | Provided by |
|---|---|
| `Servo.h` | ServoESP32 1.0.1 (`ESP32-Arduino-Servo-Library-master.zip`) |
| `WiFi.h`, `time.h` | ESP32 Arduino core (version **Unknown**) |
| `ArduinoJson.h` | ArduinoJson **5.7.1** (`ArduinoJson.zip`); uses the v5-only `StaticJsonBuffer` / `JsonObject&` API |
| `SoundData.h` | Local audio data |
| `XT_DAC_Audio.h` | XT_DAC_Audio 4.2.1 (`XT_DAC_Audio-4_2_1.zip`) |

### Global state (lines 1–62)

- `#define ledVerde 23`: a "green LED" pin, set as output in `setup()` and never written (the only use is commented out).
- `ClientRequest`, `mensajeJSON`, `myresultat`: strings for the HTTP request line.
- **Audio objects:** `DacAudio(25,0)` on DAC GPIO 25; ten `XT_Wav_Class` objects, each tied to a one-character code used by `AddNumberToSequence()`:

  | Code | Object | Array | Meaning (Spanish → English) |
  |---|---|---|---|
  | `b` | `bellsD` | `bells_wav` | Christmas song ("bells", about 6 s) |
  | `n` | `navidadD` | `navidad_wav` | "Navidad" (Christmas) |
  | `f` | `faltanD` | `faltan_wav` | "faltan" ("there are … left") |
  | `p` | `paraD` | `para_wav` | "para" ("until") |
  | `s` | `semanasD` | `semanas_wav` | "semanas" ("weeks") |
  | `1`–`4` | `unaD`…`cuatroD` | `una_wav`…`cuatro_wav` | "one" … "four" |
  | `5` | `cincoD` | `cinco_wav` | "five": **not defined in `SoundData.h`** |

- **Time:** `ntpServer = "pool.ntp.org"`, `gmtOffset_sec = 3600`, `daylightOffset_sec = 3600`.
- **Network:** `staticIP 192.168.43.158` (comment says `.211`), gateway `192.168.3.255`, subnet `/24`. These are declared but not applied, because `WiFi.config` is commented out. `WiFiServer server(80)`.
- **Servos:** `servosPins[3] = {18, 19, 21}`, `Servo servos[3]`.

### Functions

| Function | Lines | What it does |
|---|---|---|
| `printLocalTime()` | 38–51 | Gets the local time via `getLocalTime` and prints it to serial. Contains a commented-out attempt to shift the hour by −7. |
| `setServos(int degrees, int s)` | 65–67 | Writes `(degrees + 35*s) % 180` to servo `s`, so each servo gets a fixed 35° offset per index. |
| `ReadIncomingRequest()` | 70–79 | Reads the client line by line (`\r`-terminated) and keeps the last line containing `HTTP/1.1` (the request line). |
| `PlayNumber(const char*)` | 84–92 | Clears the sequence, queues one clip per character, and starts playback. |
| `AddNumberToSequence(char)` | 94–109 | Maps a character code to its `XT_Wav_Class` object. |
| `setup()` | 114–154 | Serial at 115200 (called twice). Connects to Wi-Fi with hard-coded credentials; the SSID printed in the log differs from the SSID actually used. Configures NTP and prints the time and the IP, starts the server, and attaches the 3 servos, logging attach errors. |
| `loop()` | 161–294 | See below. |

### `loop()` flow

```
FillBuffer()                                   // keep audio streaming
client = server.available(); if none → return
while (!client.available()) delay(1)           // busy-wait for data
req = ReadIncomingRequest()
req.remove(0,5); req.remove(len-9, 9)          // strip "GET /" and " HTTP/1.1"
local mensajeJSON = req; replace %22→"  %7D→}  %7B→{
StaticJsonBuffer<100>; parseObject
if success:
    read keys hora, clima(float), hola, luces, baila, no, si, musica, cuantofaltaparanavidad, selfie
    hora / selfie / clima / hola / no / si / luces / cuantofaltaparanavidad → empty bodies (comments only)
    musica  → PlayNumber("b")
    baila   → sweep servo 1 from 0 to 180 and back in 20° steps (see bugs)
else:
    Serial.print("El comando no tiene el formato JSON")   // "The command is not in JSON format"
send "HTTP/1.1 200 OK" … "OK"; flush; stop; delay(50)
```

### Comments in the code (Spanish → English)

| Original | Meaning |
|---|---|
| `Audio Objetos` | Audio objects |
| `Imprimir la hora local` | Print local time |
| `ESTABLECER IP` | Set IP |
| `VARIABLES DE SERVOS` / `FUNCIONES` | Servo variables / Functions |
| `CONECTAR A WIFI` / `INICIALIZAR SERVIDOR` / `CONEXION DE SERVOS` | Connect to Wi-Fi / Start server / Attach servos |
| `BUSCAR CLIENTE EN EL SERVIDOR` / `LEER URL` | Look for a client / Read URL |
| `obtém cliente` | "get client" (Portuguese; Inferred to come from a reference example) |
| `mostrar en lcd` | Show on LCD |
| `girar360` | Rotate 360° |
| `saludar` | Wave / greet |
| `mover la cabeza` | Move the head |
| `secuencias` | (Light) sequences |
| `Averiguar si el objeto JSON es valido` | Check whether the JSON object is valid |

## `SoundData.h`

Nine arrays produced by `xxd -i` from WAV files. The header bytes of each one were checked: all are **RIFF/WAVE, PCM, 1 channel, 8000 Hz, 8-bit**, matching the report's Audacity settings.

| Array | Bytes | ≈ Duration |
|---|---|---|
| `navidad_wav` | 4,684 | 0.58 s |
| `bells_wav` | 48,242 | 6.0 s |
| `faltan_wav` | 11,033 | 1.4 s |
| `para_wav` | 4,439 | 0.55 s |
| `semanas_wav` | 8,591 | 1.1 s |
| `tres_wav` | 3,951 | 0.49 s |
| `dos_wav` | 3,463 | 0.43 s |
| `una_wav` | 3,463 | 0.43 s |
| `cuatro_wav` | 5,416 | 0.67 s |

`cinco_wav` is referenced by `control.ino` (line 26) but **does not exist** in this file.

## Build Status of the Original Code

As stored, `control.ino` **will not compile**. These are the reasons (documented, not fixed):

1. `cinco_wav` is undeclared (missing from `SoundData.h`).
2. Line 256: `while (int pos <= 180)` is a declaration inside a `while` condition, which is invalid syntax here.
3. Lines 261 and 270: `break` is missing its terminating `;`.
4. `AddNumberToSequence` is called in `PlayNumber` before it is defined. The Arduino IDE's automatic prototype generation normally handles this, so it is likely **not** an error in the Arduino IDE (Inferred).

This suggests the uploaded file was a **work-in-progress** snapshot (Inferred), for example while the `baila` dance was being written.

## Differences Between the Repository Code and the Report Annex

The report (pages 29–36) prints a different firmware listing. Which one is newer is **Unknown**. The report's own Figure 7 fragment uses the `hola` key, which matches the repository file, while its annex uses `saludo`.

| Aspect | Repository `control.ino` | Report annex listing |
|---|---|---|
| RGB LEDs | Absent | `ledcSetup`/`ledcAttachPin` on GPIO 13/12/14, 5 kHz, 8-bit; white at every loop start |
| Servo declaration | Array `servos[3]` + `setServos()` with a 35° offset per index; checks attach errors | Three separate `servo1..3`, plain `attach` |
| Static IP | `192.168.43.158` (not applied) | `192.168.43.211` (not applied) |
| Greeting key | `hola` (empty body) | `saludo` → servo1 to 0°, servo2 to 90° |
| `no` / `si` | Empty bodies | Head movements with servo2 / servo1 (0° → 120°) |
| `luces` | Empty body | 9-step RGB blink and color sequence |
| `color` | Not read | `int color`: 1 = red, 2 = green, 3 = blue, then back to white |
| `cuantofaltaparanavidad` | Commented `digitalWrite(ledVerde,HIGH)` | `PlayNumber` called for `f`, `4`, `s`, `p`, `n` (always "4 weeks") |
| `baila` | Servo sweep (does not compile) | Empty body |
| `musica` | `PlayNumber("b")` + `Serial.println(musica)` | `PlayNumber("b")` |
| Compiles? | No (see above) | Would still fail on the missing `cinco_wav` if paired with this `SoundData.h` (Inferred) |
