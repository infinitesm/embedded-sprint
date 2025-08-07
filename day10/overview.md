# Embedded Sprint – Day 10 (Aug 20) Overview

## Summary
Master Git workflows, Linux CLI productivity, Makefiles/CMake, and cross-compilation toolchains.

## Topics
- **Git branching, merging, rebasing**
- **Bash scripting and CLI utilities**
- **Makefile rules and variables**
- **Cross-compiling with arm-none-eabi-gcc**

## Tasks
- Practise feature branch workflow and interactive rebase
- Write build_and_flash.sh script with options for debug/release
- Write log_parser.sh to extract metrics from logs
- Document usage in README

## Deliverables
### Git exercise
Sample repo with two branches merged via rebase or merge. Document commands and rationale.

### Build script
build_and_flash.sh: builds firmware, flashes via st-flash/CubeIDE CLI, supports args.

### Log parser
log_parser.sh or Python: parses UART logs for transitions, ADC stats, FAILs.

## Learning Resources
- [Atlassian Git Tutorials](https://www.atlassian.com/git/tutorials)
- [Linux CLI Full Course](https://www.youtube.com/watch?v=IVquJh3DXUA)
- [Makefile Tutorial](https://www.youtube.com/watch?v=_r7iNg6Bm_A)
- [Cross Compiling STM32](https://www.youtube.com/watch?v=4C2fuHqzQDY)
