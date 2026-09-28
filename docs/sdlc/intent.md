# Intent: Snowy

← Back to [README](../../README.md) · Next: [spec.md](spec.md) → [plan.md](plan.md)

> **Reconstructed artifact.** This intent was written in retrospect, from the original 2019 report and the code in this repository, following an intent → spec → plan structure. It describes what the team set out to do. It is not a new design. Items are marked **Confirmed**, **Inferred** or **Unknown**, as in [project-context.md](../project-context.md).

## Why (problem)

Christmas animatronics are almost always purely visual entertainment, which excludes people who cannot see them. At the same time, the DIVEC Innovación 2019 challenge asked university teams to build, **in one week**, an animatronic that is **sustainably powered**, **energy efficient**, has **controlled lighting**, **≥ 2 degrees of freedom**, and **community impact**. *(Confirmed: report pp. 5–6.)*

## Who (users and stakeholders)

| Stakeholder | Interest | Status |
|---|---|---|
| Blind and visually impaired people | Enjoy and control a Christmas decoration by voice, from their phone | Confirmed (primary audience in the report) |
| General public / household members | Interact with Snowy from anywhere on the home Wi-Fi | Confirmed |
| Challenge evaluators (DIVEC / CUCEI) | Verify compliance with the challenge requirements | Confirmed |
| Student team (INCE, INRO, IGFO) | Earn modular-project credit; integrate the three disciplines | Confirmed |

## What (desired outcome)

A snowman animatronic that:

1. Runs on **solar energy** stored in a battery.
2. Is controlled by **Spanish voice commands** on an Android phone.
3. Responds with **movement**, **sound** (songs and spoken phrases) and **light**.
4. Offers helpful phone-side functions for visually impaired users: time, weather, selfie, calling family.

## Success criteria

| # | Criterion | Evidence of outcome |
|---|---|---|
| SC1 | Meets every DIVEC requirement (R1–R7 in [assignment.md](../assignment.md)) | Claimed in the report's conclusion |
| SC2 | Voice command → visible or audible reaction on Snowy over Wi-Fi | Described in the report; partially present in the repository firmware (`musica`, `baila`) |
| SC3 | Operates from the solar panel and battery | Described and photographed in the report |
| SC4 | Built within one week | Methodology timeline in the report |

## Constraints

- **Time:** one week *(Confirmed)*.
- **Budget and materials:** use what the team already owned (battery, polystyrene balls) and cheap parts (SG90, LM386) *(Confirmed)*.
- **Platform:** ESP32 with the Arduino IDE; Android through MIT App Inventor *(Confirmed)*.
- **Skills:** a multidisciplinary team, much of it self-taught during the challenge *(Confirmed)*.

## Non-goals

- Real autonomy or AI. The report explicitly positions Snowy as an animatronic, not a robot *(Confirmed)*.
- Production-grade security, multi-user handling, or OTA updates *(Inferred from the implementation)*.
- An on-device display. The `//mostrar en lcd` placeholders were never backed by hardware in the report *(Inferred)*.

## Open questions (Unknown)

- Who authored each part (firmware, app, circuits)?
- Is the repository `control.ino` earlier or later than the report annex version?
- What was the challenge's evaluation result?
