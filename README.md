<h1 align="center"><code>SVM</code></h1>
<h2 align="center"><s>Shitty</s> Simple Virtual Machine</h2>

#### Legal
<sub>There's a lot of Oracle shady business that happens. If I'm carful here, I should keep the rights to this software, keeping it free and open, and, most importantly, away from Oracle's slimy grasp. This is why things might be phrased weird.</sub>

# About
SVM aims to be a compact and efficient language virtual machine for you to embed within your application. Before using this, check out Lua or another language in that same vein, as they are actually ment to be embedded.

## Building
SVM comes in a library and the binary. The binary is just a simple front end for the library. Any program that wishes may link against the library.
Documentation is provided, but you should also look at the reference binary.

You may find a full list of meson arguments [here](https://mesonbuild.com/Builtin-options.html), which may prove to be useful.

Those flags may be used to further fine tune your experience (recommended for anything beyond a toy project). Some comman arguments have been listed below for convience:

<details>
<summary>Flags</summary>
<br>
<ol>
<li><i>buildtype</i>
    <ol>
    <li> <i>debug</i> is the default, which is not want you want if you are not developing or debugging.</li>
    <li> <i>plain</i> will not include debug symbols, but won't do anything special.</li>
    <li> <i>debugoptimized</i> builds an optimized debug build. This can break debugging *very* easily.</li>
    <li> <i>release</i> does some optimizations, and doesn't include debug symbols.</li>
    <li> <i>minimize</i> makes the library as small as possible. Usefull for embedding.</li>
    </ol>
</li>
<li><i>default_library</i>
    <ol>
    <li> <i>both</i> is the default, and builds both a static and dynamic library.</li>
    <li> <i>static</i> builds a static library, which doesn't need to be present at runtime (baked into the application).</li>
    <li> <i>shared</i> will build a shared library. Must be shipped with the applications, and might not be a good choice.</li>
    </ol>
</li>
<li> <i>optimization</i>
    <ol>
    <li> <i>O</i> is dependent on the buildtype (default on debug). Performs no optimizations.</li>
    <li> <i>1</i> optimizes a little for size and performance, without having a large impact on compile time.</i>
    <li> <i>2</i> optimizes for performance as much as possible without increasing size.</li>
    <li> <i>3</i> optimizes as much as possible for performance, and doesn't give a f\*ck about binary size.</li>
    <li> <i>s</i> enables all optimizations that have often have an effect on code size.</li>
    <li> <i>g</i> enhances your debugging experience.</li>
    </ol>
</li>
<li> <i>werror</i>
    <ol>
    <li> <i>true</i> is the default. Errors on warnings.</li>
    <li> <i>false</i> doesn't error on warnings. </li>
    </ol>
</li>
<li> <i>warning_level</i>
    <ol>
    <li> <i>0-3</i>, where 0 is the lowest, and 3 is the highest.</li>
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

## Platforms
SVM uses only C99 standard headers and platform independent code, so it should work wherever you might find a C compiler that supports C9<li> If not, please support an issue.

### Tested platforms

<li> Linux (Arch Linux)
<li> Mac OS (Catalina)



