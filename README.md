# SVM: Simple (language) Virtual Machine

# About
SVM aims to be a compact language virtual machine (JVM 17) for you to embed within your application. Before using this, check out Lua or another language in that same vein, as they are actually ment to be embedded.

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
SVM uses only C99 standard headers and platform independent code, so it should work wherever you might find a C compiler that supports C9<li> If not, please support an issue.

## Tested platforms

<li> Linux (Arch Linux)
<li> Mac OS (Catalina)



