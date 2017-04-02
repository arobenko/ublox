# How to Build

This project uses [CMake](https://cmake.org) cross-platform build system to
generate required build files native to the platform.

## Available CMake Options

In addition to built-in options/variables of CMake, such as **CMAKE_BUILD_TYPE** or
**CMAKE_TOOLCHAIN_FILE**, the following ones can be used:

- **CC_UBLOX_LIB_ONLY**=ON/OFF - Exclude compilation of all the sources, install only
**UBLOX** protocol headers-only library. Default value is **OFF**, i.e. the plugin to CommsChampion gets built.

- **CC_UBLOX_AND_COMMS_LIBS_ONLY**=ON/OFF - Exclude compilation of all the sources, install only
**UBLOX** protocol library as well as check out and install **COMMS** library headers
as well. Default value is **OFF**, i.e. the plugin to CommsChampion gets built.

- **CC_UBLOX_FULL_SOLUTION**=ON/OFF - This option allows to build both
[comms_champion](https://github.com/arobenko/comms_champion) and this projects
in one go. When enabled, it will checkout and build the 
[comms_champion](https://github.com/arobenko/comms_champion) prior to building
anything from this repository. All the headers, binaries, and libraries will
be installed in the directory specified with **CC_UBLOX_INSTALL_DIR** variable. 
Default value of this option is **OFF**.

- **CC_UBLOX_INSTALL_DIR**=dir - Custom installation directory. If not provided defaults to
**install** subdirectory of the directory chosen for build (**${CMAKE_BINARY_DIR}/install**). 

- **CC_MAIN_INSTALL_DIR**=dir - The provided **UBLOX** library depends on 
artefacts created and installed by 
[comms_champion](https://github.com/arobenko/comms_champion) project. If
the latter is already built separately, the path to it needs to be provided using
this variable. If this project and 
[comms_champion](https://github.com/arobenko/comms_champion) share the same
installation directory (provided by **CC_UBLOX_INSTALL_DIR**), the usage of
this variable is not necessary.

- **CC_UBLOX_QT_DIR**=/path/to/qt - Path to custom build of **QT5** if it cannot be
found in standard system directories. The **QT5** is used by the
[comms_champion](https://github.com/arobenko/comms_champion) tools and it is
required to build the protocol plugin for them.

- **CC_UBLOX_NO_WARN_AS_ERR**=ON/OFF - By default, all warnings are treated as
errors. Enable this option in case the compiler generates warning and fails the
compilation. Please open the issue when such scenario occurs. Default value is 
**OFF**.

## Build and Install Examples

The examples below are Linux/Unix system oriented, i.e. they use **make** utility
to build the "install" target after configuration with **cmake**. 

On Windows
systems with Visual Studio compiler, the CMake utility generates Visual Studio
solution files by default. Build "install" project. It is also possible to 
generate Makefile-s on Windows by providing additional **-G "NMake Makefiles"** option
to **cmake**. In this case use **nmake** utility instead of **make**.

Please review the examples below and use appropriate option that suites your
needs. Remember to add **-DCMAKE_BUILD_TYPE=Release** option for release
builds.

Also **note**, that compilation process of the protocol plugin for 
[CommsChampion Tools](https://github.com/arobenko/comms_champion#commschampion-tools)
requires a lot of memory and your compilation may fail due to heap memory allocation
failure. It is recommended to use 64 bit OS with at least 8GB of RAM. 

### Full Solution
If you are not familiar with [comms_champion](https://github.com/arobenko/comms_champion) 
project and its tools, it is recommended to use **CC_UBLOX_FULL_SOLUTION**
option to force full build with all the provided libraries, tools and plugins to
them. The "full solution" build is intended to be built and used on the 
development PC with QT5 libraries installed. It will build all the tools and
relevant plugins to be able to connect to your u-blox device over serial connection
and exchange any UBX messages with it.

```
$> cd /path/to/ublox/sources
$> mkdir build && cd build
$> cmake -DCMAKE_BUILD_TYPE=Release -DCC_UBLOX_FULL_SOLUTION=ON ..
$> make install 
```

### Libraries Only
If the UBLOX library needs to be used to develop some embedded application and
neither [comms_champion](https://github.com/arobenko/comms_champion) tools nor
relevant protocol plugin need to be build, use **CC_UBLOX_AND_COMMS_LIBS_ONLY**
option to install only headers of the UBLOX and 
[COMMS](https://github.com/arobenko/comms_champion#comms-library) libraries.

```
$> cd /path/to/ublox/sources
$> mkdir build && cd build
$> cmake -DCC_UBLOX_AND_COMMS_LIBS_ONLY=ON ..
$> make install 
```

### UBLOX Library Only
If the [COMMS](https://github.com/arobenko/comms_champion#comms-library) library
already installed and used to define some other protocols, there is no need to
install it again. Use **CC_UBLOX_LIB_ONLY** option to install only headers of
the UBLOX library.
```
$> cd /path/to/ublox/sources
$> mkdir build && cd build
$> cmake -CC_UBLOX_LIB_ONLY=ON ..
$> make install 
```

### Building Protocol Plugin
If the [comms_champion](https://github.com/arobenko/comms_champion) tools are
built and installed separately, use **CC_MAIN_INSTALL_DIR** option to specify
its installation directory.

```
$> cd /path/to/ublox/sources
$> mkdir build && cd build
$> cmake -DCMAKE_BUILD_TYPE=Release -CC_MAIN_INSTALL_DIR=/path/to/comms_champion/build/install ..
$> make install 
```

Note, that the example above will not install the plugin to the relevant directory
searched by [comms_champion](https://github.com/arobenko/comms_champion) tools.
The created plugin needs to be copied manually. 

It is possible to make the built plugin to be installed into the right place by
installing the artefacts to the same directory as **comms_champion** by 
using **CC_UBLOX_INSTALL_DIR** variable instead.

```
$> cd /path/to/ublox/sources
$> mkdir build && cd build
$> cmake -DCMAKE_BUILD_TYPE=Release -CC_UBLOX_INSTALL_DIR=/path/to/comms_champion/build/install ..
$> make install 
```

## Building Documentation
The documentation is not created during normal build process. The documentation of
the [UBLOX Library](#ublox-library) can be generated by building **doc_ublox**
target:
 
```
$> make doc_ublox
```

The HTML documentation will reside in **${CC_UBLOX_INSTALL_DIR}/doc/ublox/html** 
directory.

**NOTE**, that you must have 
[Doxygen](www.doxygen.org) 
installed on your system in order to be able to properly generate the 
documentation.
