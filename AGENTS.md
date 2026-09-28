# AGENTS.md

Guidance for any automated coding agent or assistant working in this repository.

## What this repository is

A **historical archive** of *Snowy*, a voice-controlled Christmas animatronic built in December 2019 for the DIVEC Innovación 2019 modular-project challenge (Universidad de Guadalajara, CUCEI). Start with [README.md](README.md), then read [docs/sdlc/intent.md](docs/sdlc/intent.md), [spec.md](docs/sdlc/spec.md) and [plan.md](docs/sdlc/plan.md).

## Hard rules

1. **Do not modify anything under `src/`.** `control.ino` and `SoundData.h` are preserved byte-for-byte, including their bugs, CRLF line endings and Spanish comments. Their SHA-256 hashes are recorded in [docs/sdlc/plan.md](docs/sdlc/plan.md#integrity-reference); keep them matching.
2. **Do not modify or delete** `docs/original/` or `third_party/arduino-libraries/`.
3. **Do not "fix" the code**, even though it does not compile. Document issues in [docs/possible-improvements.md](docs/possible-improvements.md) instead.
4. **Do not add infrastructure** (CI, Docker, build systems, linters, test frameworks) that the original project never had.
5. **Do not invent facts.** Label claims as *Confirmed*, *Inferred* or *Unknown*, and record contradictions in [docs/project-context.md](docs/project-context.md#contradictions-found).
6. Documentation is written in **English**. Keep original Spanish identifiers and quotes verbatim, with translations beside them.

## Allowed changes

- Improving or correcting Markdown documentation in `docs/` and `README.md`.
- Adding recovered historical material (e.g. the MIT App Inventor `.aia`, original WAV files) under `docs/original/` or a new clearly named folder, with an entry in the docs.
- Any **new** implementation must live outside `src/` (e.g. a separate `rewrite/` folder or repository) and be clearly labeled as not original.

## Verifying you did not touch the code

```sh
sha256sum src/control/control.ino src/control/SoundData.h
# compare with docs/sdlc/plan.md → "Integrity reference"
```
