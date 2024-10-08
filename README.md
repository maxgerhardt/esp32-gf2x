# ESP32 + GF2x library

## Description

This project demonstrates how to use a precompiled GF2x library (https://gitlab.inria.fr/gf2x/gf2x) inside an ESP32 Arduino project.

## How to compile GF2x for ESP32

This assumes running a Linux system (e.g.: Ubuntu 22 inside WSL or a virtual machine):

```bash
# one time prerequisites
sudo apt install libtool autoconf autoconf-archive
pio pkg install -g -t "espressif/toolchain-xtensa-esp32@8.4.0+2021r2-patch5"
export PATH=$PATH:/home/max/.platformio/packages/toolchain-xtensa-esp32/bin/

git clone https://gitlab.inria.fr/gf2x/gf2x.git
cd gf2x

libtoolize --force
aclocal
autoheader
automake --force-missing --add-missing
autoconf

mkdir installed
CFLAGS="-mlongcalls" ./configure --host=xtensa-esp32-elf --prefix=$(pwd)/installed
make clean
make -j8
make install
ls -R installed
```

## How to integrate with a PlatformIO project

After the library files were generated in `installed/`, we can just copy them into a PlatformIO project as such:
* create a new folder `lib/gf2x`
* copy over `installed/include` in `lib/gf2x/include`
* copy over `installed/lib/libgf2x.a` into `lib/gf2x/libgf2x.a`
* add a `lib/gf2x/library.json` with minimal content
```json
{
    "name": "gfx2",
    "version": "1.3.99",
    "build": {
        "flags": [
            "-L.",
            "-lgf2x"
        ]
    }
}
```
* include the library in the main sketch with
```cpp
#include <gf2x.h>
```
and use the library.