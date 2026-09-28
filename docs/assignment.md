# Assignment: DIVEC Innovación 2019 Modular-Project Challenge

← Back to [README](../README.md)

Source: introduction and conclusion of the original report ([`original/ReporteRetoProyectoModularDIVEC.pdf`](original/ReporteRetoProyectoModularDIVEC.pdf), pp. 5 and 26). The challenge brief itself is **not** in the repository. The requirements below are the ones the team restated in their report.

## Framework

- **Program:** *DIVEC Innovación 2019*, described as a program to develop innovative thinking, teamwork, multidisciplinary development and new technology frontiers for teachers and students.
- **Activity:** *Reto de Proyectos Modulares* (modular-projects challenge).
- **Academic purpose:** earn credit for the *proyectos modulares* of INCE, INRO and IGFO at CUCEI, Universidad de Guadalajara.
- **Format:** multidisciplinary teams, **one-week** time limit.

## Requirements (as restated in the report)

| # | Requirement |
|---|---|
| R1 | Must be an **animatronic** |
| R2 | Powered by a **sustainable energy source** |
| R3 | **Energy efficient**, with **minimal circuitry** |
| R4 | Promote values, attitudes and healthy practices, with **community reach** |
| R5 | Include **controlled lighting** applications |
| R6 | At least **two degrees of freedom** of movement |
| R7 | Completed within **one week** |

## How Snowy Addresses Them (as claimed by the report)

| Req. | Team's solution | Evidence in this repository |
|---|---|---|
| R1 | Snowman figure with scripted movements and sounds (the report explicitly classifies it as an animatronic, not a robot) | Firmware: servo + audio handling |
| R2 | Monocrystalline solar panel charging a 12 V 7 Ah lead-acid battery | Report only (schematic images) |
| R3 | LM317 charger with TIP122 cut-off and LED indicator; LM7805 regulator; circuits compared on a breadboard for fewest parts and lowest consumption | Report only |
| R4 | Voice-controlled operation aimed at blind and visually impaired users | App described in the report; app source not in repository |
| R5 | RGB LED "eyes" with PWM sequences and color commands | **Report annex only**. The repository `control.ino` has no LED PWM code (only an unused `ledVerde` pin) |
| R6 | 3 × SG90 servos (report says 3 axes; conclusion says 3 DoF with 2 servos) | Firmware attaches 3 servos; the `baila` routine moves servo index 1 |
| R7 | Six-day schedule described in the methodology | Report only |

## Extra Features Beyond the Requirements

The report states that Snowy *"cumple todos los requerimientos… pero también cuenta con funciones extras"* ("meets all the requirements… but also has extra functions"):

- Android app with speech recognition and text-to-speech.
- Weather from OpenWeatherMap based on phone GPS.
- Time announcement, a selfie with the front camera, and calling a contact.
- Local playback of a Christmas song and spoken phrases ("faltan … semanas para navidad", meaning "… weeks until Christmas").

## Learning Context (Inferred)

The project combines embedded systems (ESP32, PWM, DAC), power electronics (solar charging, regulation), analog audio (LM386), networking (HTTP over Wi-Fi, JSON) and mobile development (App Inventor). It spans the three degree programs involved, which matches the challenge's multidisciplinary goal.
