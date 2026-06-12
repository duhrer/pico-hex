# Pico Neopixel Hex

This project provides an library to control a [M5stack Hex
Unit](https://docs.m5stack.com/en/unit/hex) with a Raspberry Pi Pico, and
examples of how it can be used. I use this in my own projects, but it's very
much not supported and is mainly provided as a reference for you to learn to
make something better.

## Prerequisites

### Hardware

To use this library, you need a few pieces of hardware:

1. An M5Stack Hex Unit.
2. M5 Grove Cable(s).
3. A Raspberry Pi Pico or compatible (the instructions here assume you have a
   unit that exposes the 5V VSYS pin).  I tested this with a Pimoroni Pico Plus 2W.

### Software

To build/install a project that uses this library, you will need:

1. Git
2. CMake
3. Docker and/or the Pi Pico SDK toolchain

For more details, check out [the examples in this repository](./examples/) as
well as [the template project from which this project was
created](https://github.com/lichen-community-systems/pi-pico-project-template).

## Using This Library in Your Own Project

The suggested way to include this project in your own work is to add it as a
submodule, as in:

```
mkdir -p lib
git submodule add https://github.com/duhrer/pico-hex.git lib/pico_hex
```

You'll then need to add it to your `CMakeLists.txt` file.  First, you need to
add the library source to your project as shown here:

```
# Bring in the pico_hex library source
add_subdirectory(lib/pico_hex build)
```

You then need to add the library to your binary's linked libraries, as in:

```
target_link_libraries(${NAME}
    pico_stdlib
    pico_hex
    pico_time
    pico_rand
    pico_bootsel_via_double_reset
)
```


With all that done, you need to actually use the code. Check out the [examples
directory](./examples/) for ideas.

## License

This repository is distributed under the BSD-3 license.
