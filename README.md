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
SVM comes in a library and the binary. The binary is just a simple front end for the library. Any program that wishes may link against the library.
Documentation is provided, but you should also look at the reference binary.

You may find a full list of meson arguments [here](https://mesonbuild.com/Builtin-options.html), which may prove to be useful.

Those flags may be used to further fine tune your experience (recommended for anything beyond a toy project). Some comman arguments have been listed beliw for convience:

1. `buildtype`
    1. `debug` is the default, which is not want you want if you are not developing or debugging.
    2. `plain` will not include debug symbols, but won't do anything special.
    3. `debugoptimized` builds an optimized debug build. This can break debugging *very* easily.
    4. `release` does some optimizations, and doesn't include debug symbols.
    5. `minimize` makes the library as small as possible. Usefull for embedding.
2. `default_library`
    1. `both` is the default, and builds both a static and dynamic library.
    2. `static` builds a static library, which doesn't need to be present at runtime (baked into the application).
    3. `shared` will build a shared library. Must be shipped with the applications, and might not be a good choice.
3. `optimization`
    1. `O` is dependent on the buildtype (default on debug). Performs no optimizations.
    2. `1` optimizes a little for size and performance, without having a large impact on compile time.
    3. `2` optimizes for performance as much as possible without increasing size.
    4. `3` optimizes as much as possible for performance, and doesn't give a f\*ck about binary size.
    5. `s` enables all optimizations that have often have an effect on code size.
    6. `g` enhances your debugging experience.
4. werror
    1. `true` is the default. Errors on warnings.
    2. `false` doesn't error on warnings.
5. warning_level
    1. `0-3`, where 0 is the lowest, and 3 is the highest.


```bash
# Configuration
# You can substitute meson arguments for <arguments>, or none at all. Some common arguments have been listed for convience:
meson setup <arguments> builddir && cd builddir

# Building
# Nothing much to see here. Any flags and the like should have been specified in the configure stage.
ninja

# Installation
# Installs the library headers, the library itself, and the reference VM.
sudo ninja install
```

## Application development
While SVM does provide documentation, it is recommended you suplement this with the reference binary.

