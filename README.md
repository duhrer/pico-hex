# Pico Neopixel Hex

This project provides an example of using the [M5stack Hex
Unit](https://docs.m5stack.com/en/unit/hex) with a Raspberry Pi Pico.

## Prerequisites

### Hardware

To run this code, you need a few pieces of hardware:

1. An M5Stack Hex Unit.
2. M5 Grove Cable(s).
3. A Raspberry Pi Pico or compatible (the instructions here assume you have a
   unit that exposes the 5V VSYS pin).  I tested this with a Pimoroni Pico Plus 2W.

### Software

To build/install this project, you will need:

1. Git
2. CMake
3. Docker and/or the Pi Pico SDK toolchain

For full details, check out [the template project from which this project was
created](https://github.com/lichen-community-systems/pi-pico-project-template).

## Build the Binary

The easiest way to build the binary is to run one of the included build scripts.
If you run `./compile.sh`, binaries should be created in the `build` directory.
If you run `./docker-compile.sh`, binaries should be created in `build-docker`.

## Install the Binary

The simplest way to install the binary is to connet your microcontroller to your
computer and put it in "bootsel" mode.  This can be done by holding the
"bootsel" buton and either power cycling or hitting the "reset" button.  If
you've already installed the binary from this repository, you can hit "reset"
twice in quick succession to enter "bootsel" mode.

Once your microcontroller is in "bootsel" mode, drag the `pico-hex.uf2` binary
to the USB drive that appears.

## License

This repository is distributed under the BSD-3 license.
