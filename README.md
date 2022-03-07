<h1 align="center"><code>SVM</code></h1>
<h2 align="center"><s>Shitty</s> Simple Virtual Machine</h2>

## Capabilities
Currently, this "JVM" is capable of running *very* simple Java 8 class files. The only functionality this thing supports is located in the example directory.

This is no longer a school project. This aims to have a lighter footprint than some JVMs, in both memory and size. This will *no doubt* haunt me. This won't ever actually turn into something, but hey, it's educational :D

## Platforms
SVM uses only C99 standard headers and platform independent code, so it should work wherever you might find a C compiler that supports C99. If not, please support an issue.

### Tested platforms

1. Linux (Arch Linux)
2. Mac OS (Catalina)

## Building
SVM comes in a library and the binary. The binary is just a simple front end for the library. Any program that wishes may link against the library. Documentation is provided, but you should also look at the reference binary.

By default, `meson` (SVM's build system) will spit out a dynamic library. You may find a full list of meson arguments [here](https://mesonbuild.com/Builtin-options.html), which may prove to be useful.
```bash
# Configuration
# You can substitute meson arguments for <arguments>, or none at all. Some common arguments have been listed for convience:
#   buildtype
#       `debug` is the default, which is not want you want if you are not developing or debugging.
#       `plain` will not include debug symbols, but won't do anything special.
#       `debugoptimized` builds an optimized debug build. This can break debugging *very* easily.
#       `release` does some optimizations, and doesn't include debug symbols.
#       `minimize` makes the library as small as possible. Usefull for embedding.
#   default_library
#       `both` is the default, and builds both a static and dynamic library.
#       `static` builds a static library, which doesn't need to be present at runtime (baked into the application).
#       `shared` will build a shared library. Must be shipped with the applications, and might not be a good choice.
#   optimization
#       `O` is dependent on the buildtype (default on debug). Performs no optimizations.
#       `1` optimizes a little for size and performance, without having a large impact on compile time.
#       `2` optimizes for performance as much as possible without increasing size.
#       `3` optimizes as much as possible for performance, and doesn't give a f*ck about binary size.
#       `s` enables all optimizations that have often have an effect on code size.
#       `g` enhances your debugging experience.
#   werror
#       `true` is the default. Errors on warnings.
#       `false` doesn't error on warnings.
#   warning_level
#       `0-3`, where 0 is the lowest, and 3 is the highest.
#
#   Other flags may be used to further fine tune your experience (recommended for anything beyond a toy project).
meson setup <arguments> builddir && cd builddir

# Building
# Nothing much to see here. Any flags and the like should have been specified in the configure stage.
ninja

# Installation
# Installs the library headers, the library itself, and the reference VM.
sudo ninja install
```

