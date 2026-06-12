# Pico Hex Examples

This directory contains examples that demonstrate each of the available drawing
methods, and which also demonstrate the animation classes provided by this
library.

|| Subdirectory         || Description                       ||
|| -------------------- || --------------------------------- ||
| `cubic-cycle`         | Break the hex down into cubic tiles drawn in perspective. |
| `italic-fill-row`     | Demonstrate using the hex array as a slanted grid by drawing straight rainbow lines. |
| `italic-sine-rainbow` | Draw a rainbow sine wave using the "italic" (slanted grid) methods. |
| `polar-flame`         | Simulate a circular flame, including various colour schemes. |
| `polar-mixing`        | Demonstrate the polar colour-mixing strategies. |
| `ring-rainbow`        | Demonstrate the "ring" drawing functions by cycling through a rainbow of rings. |
| `ring-spin`           | Demonstrate pixel-addressing within the "ring" drawing functions by drawing a spiral. |
| `rollup-eye`          | Demonstrate the polar fill functions by displaying an animated eye. |
| `rollup-all`          | A randomised rollup of all of the above that cycles indefinitely. |


## Build the Binaries

I currently run builds in a docker container created using the `Dockerfile`
found in the root of this repository, which itself comes from [the template
repository from which this project was
created](https://github.com/lichen-community-systems/pi-pico-project-template).

From the root of the repository, build the container using a command like:

```
podman build --tag pico-sdk .
```

You can then use commands like the following:

```
cd examples
mkdir -p build
cd build
distrobox enter pico-sdk
cmake ..
make -j16
```

That will create a series of output directories with binaries for each example.

## Install the Binary

The simplest way to install the binary is to connect your microcontroller to
your computer and put it in "bootsel" mode.  This can be done by holding the
"bootsel" buton and either power cycling or hitting the "reset" button.  All of
the binaries built in this directory support hitting "reset" twice quickly to
enter "bootsel" mode.

Once your microcontroller is in "bootsel" mode, drag the desired `.uf2` binary
to the USB drive that appears.  It should reboot and run the selected code, if
it doesn't, make sure you're building for the right board and platform.