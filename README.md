<h1 align="center"><code>SVM</code></h1>
<h2 align="center"><s>Shitty</s> Simple Virtual Machine</h2>

## Capabilities
Currently, this "JVM" is capable of running *very* simple Java 8 class files. The only functionality this thing supports is located in the example directory.

This is no longer a school project. This aims to have a lighter footprint than some JVMs, in both memory and size. This will *no doubt* haunt me. This won't ever actually turn into something, but hey, it's educational :D

## Platforms
SVM uses only C99 standard headers and platform independent code, so it should work wherever you might find a C compiler that supports C9<li> If not, please support an issue.

### Tested platforms

<li> Linux (Arch Linux)
<li> Mac OS (Catalina)

## Building
SVM comes in a library and the binary. The binary is just a simple front end for the library. Any program that wishes may link against the library.
Documentation is provided, but you should also look at the reference binary.

You may find a full list of meson arguments [here](https://mesonbuild.com/Builtin-options.html), which may prove to be useful.

Those flags may be used to further fine tune your experience (recommended for anything beyond a toy project). Some comman arguments have been listed below for convience:

<details open>
<summary>Flags</summary>
<br>
<ol>
<li>`buildtype`
    <ol>
    <li> `debug` is the default, which is not want you want if you are not developing or debugging.</li>
    <li> `plain` will not include debug symbols, but won't do anything special.</li>
    <li> `debugoptimized` builds an optimized debug build. This can break debugging *very* easily.</li>
    <li> `release` does some optimizations, and doesn't include debug symbols.</li>
    <li> `minimize` makes the library as small as possible. Usefull for embedding.</li>
    </ol>
</li>
<li>`default_library`
    <ol>
    <li> `both` is the default, and builds both a static and dynamic library.</li>
    <li> `static` builds a static library, which doesn't need to be present at runtime (baked into the application).</li>
    <li> `shared` will build a shared library. Must be shipped with the applications, and might not be a good choice.</li>
    </ol>
</li>
<li> `optimization`
    <ol>
    <li> `O` is dependent on the buildtype (default on debug). Performs no optimizations.</li>
    <li> `1` optimizes a little for size and performance, without having a large impact on compile time.</i>
    <li> `2` optimizes for performance as much as possible without increasing size.</li>
    <li> `3` optimizes as much as possible for performance, and doesn't give a f\*ck about binary size.</li>
    <li> `s` enables all optimizations that have often have an effect on code size.</li>
    <li> `g` enhances your debugging experience.</li>
    </ol>
</li>
<li> `werror`
    <ol>
    <li> `true` is the default. Errors on warnings.</li>
    <li> `false` doesn't error on warnings. </li>
    </ol>
</li>
<li> `warning_level`
    <ol>
    <li> `0-3`, where 0 is the lowest, and 3 is the highest. </li>
    </ol
</li>
</ol>
</pre>
</details>

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

