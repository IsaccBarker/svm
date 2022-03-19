[![Meson Build (Linux)](https://github.com/IsaccBarker/svm/actions/workflows/meson-linux.yml/badge.svg)](https://github.com/IsaccBarker/svm/actions/workflows/meson-linux.yml)
[![Meson Build (MacOS)](https://github.com/IsaccBarker/svm/actions/workflows/meson-macos.yml/badge.svg)](https://github.com/IsaccBarker/svm/actions/workflows/meson-macos.yml)
[![Meson Build (Windows)](https://github.com/IsaccBarker/svm/actions/workflows/meson-windows.yml/badge.svg)](https://github.com/IsaccBarker/svm/actions/workflows/meson-windows.yml)
![CodeQL](https://github.com/IsaccBarker/svm/actions/workflows/codeql.yml/badge.svg)](https://github.com/IsaccBarker/svm/actions/workflows/codeql.yml)

> <img src="https://media4.giphy.com/media/LZElUsjl1Bu6c/giphy.gif?cid=ecf05e474dzue7v5980rnrz669yo460hgq0dggb7ad0sqyqq&rid=giphy.gif&ct=g"></img>
> 
> **Jarrot** the Java Perrot. Our mascot ;)

# SVM: Simple (language) Virtual Machine

# About
SVM aims to be a compact language virtual machine (compatable Java SE 17) for you to embed within your application. Before using this, check out Lua or another language in that same vein, as they are actually ment to be embedded.

## Reference
This project uses the [Oracle's Java SE 17 JVM Specification](https://docs.oracle.com/javase/specs/jvms/se17/jvms17.pdf) as reference.

## Building
SVM comes in a library and the binary. The binary is just a simple front end for the library. Any program that wishes may link against the library.
Documentation is provided, but you should also look at the reference binary.

```bash
# Configuration
meson builddir && cd builddir

# Once in the builddir directory, you can change any configure settings with `meson configure`
# See `meson_options.txt` for more information.

# Building
# Nothing much to see here. Any flags and the like should have been specified in the configure stage.
ninja

# Installation
# Installs the library headers, the library itself, and the reference VM.
sudo ninja install
```

## Application development
While SVM does provide documentation, it is recommended you suplement this with the reference binary.

## Platforms
SVM uses only C99 standard headers and platform independent code, so it should work wherever you might find a C compiler that supports C99. If not, please support an issue.

## Tested platforms

* Linux (Arch Linux)
* Mac OS (Catalina)

## Credits
1. rxi's [log.c](https://github.com/rxi/log.c)

