# Overview
[u-blox GPS receivers](https://www.u-blox.com/en/position-time)
use a UBX binary protocol to transmit GPS data to a host computer using
asynchronous serial ports. This project provides a **headers only** library
implemented in C++(11), which implements all the messages as well as wrapping 
transport protocol used in **u-blox 4/5/6/7** devices.

# UBLOX Library
The library uses [COMMS library](https://github.com/arobenko/comms_champion#comms-library)
from [comms_champion](https://github.com/arobenko/comms_champion) project 
to specify all the messages resulting in clear, concise,
and very efficient code.

The ublox binary protocol is huge and it is unlikely that any embedded product
will require support for all the messages the protocol defines. This library
allows cherry-picking limited number of the selected messages the product requires,
which provides a great flexibility in terms of the final code size.

Full [doxygen](www.doxygen.org) generated documentation with the full tutorial inside can be
downloaded as zip archive from [here](https://dl.dropboxusercontent.com/u/46999418/ublox/doc_ublox.zip).

# CommsChampion Plugin
In addition to the library described above, this project provides a protocol
plugin for the [CommsChampion Tools](https://github.com/arobenko/comms_champion#commschampion-tools)
from the same [comms_champion](https://github.com/arobenko/comms_champion) project,
which will allow visual analysis of the u-blox binary protocol traffic.

# Licence
The source code of [UBLOX Library](#ublox-library) as well as [CommsChampion Plugin](#commschampion-plugin) 
from this repository is licensed under GPLv3. 
It can be used in any product as long as its sources remain open and
have the same or other compatible license. As the author and full copyright
owner of this product I can provide a commercial license as well, please refer
to [Contact Information](#contact-information) below and get in touch with
me if you need one.

# How to Build
This project uses [CMake](https://cmake.org) cross-platform build system to
generate required build files native to the platform.

- Build and install all the necessary components from the 
[comms_champion](https://github.com/arobenko/comms_champion) project following
[instructions](https://github.com/arobenko/comms_champion#how-to-build).

- Create a separate build directory for this project somewhere and navigate there.

>$> mkdir /some/build/dir && cd /some/build/dir

- Generate Makefiles (or any other build environment) choosing the same build type
as when building the [comms_champion](https://github.com/arobenko/comms_champion)
sources. The build depends on the installed contents of the 
[comms_champion](https://github.com/arobenko/comms_champion) project
and requires knowledge about the location of the latter. It is recommended to
install the produced headers/binaries of this project into the same directory
as with [comms_champion](https://github.com/arobenko/comms_champion), it will cause
all the required dependencies to be found automatically. The installation
directory can be specified using **CC_UBLOX_INSTALL_DIR** variable.

>$> cmake -DCMAKE_BUILD_TYPE=Release -DCC_UBLOX_INSTALL_DIR=/path/to/comms_champion/build/install /path/to/ublox/sources

If the produced headers/finaries are not desired to be mixed, the location
of the [comms_champion](https://github.com/arobenko/comms_champion)
installation path can be provided using **CC_MAIN_INSTALL_DIR** variable.

>$> cmake -DCMAKE_BUILD_TYPE=Release -DCC_MAIN_INSTALL_DIR=/path/to/comms_champion/build/install /path/to/ublox/sources

- Build and install.

>$> make install

After the build is complete, all the binaries, headers, libraries will reside
in the chosen install directory (See description of **CC_UBLOX_INTALL_DIR** variable below) .

In addition to built-in options/variables of CMake, such as **CMAKE_BUILD_TYPE** or
**CMAKE_TOOLCHAIN_FILE**, the following ones can be used:

- **CC_UBLOX_LIB_ONLY**=ON/OFF - Exclude compilation of all the sources, install only
**UBLOX** protocol library. Default value is **OFF**, i.e. the plugin to CommsChampion gets built.

- **CC_UBLOX_AND_COMMS_LIBS_ONLY**=ON/OFF - Exclude compilation of all the sources, install only
**UBLOX** protocol library as well as check out and install **COMMS** library headers
as well. Default value is **OFF**, i.e. the plugin to CommsChampion gets built.

- **CC_UBLOX_INSTALL_DIR**=dir - Custom installation directory. If not provided defaults to
**install** subdirectory of the directory chosen for build (**${CMAKE_BINARY_DIR}/install**). 

- **CC_MAIN_INSTALL_DIR**=dir - Directory where headers and libraries of 
[comms_champion](https://github.com/arobenko/comms_champion) project. It must
be used if value of **CC_UBLOX_INSTALL_DIR** doesn't specify the same location.

- **CC_UBLOX_QT_DIR**=/path/to/qt - Path to custom build of **QT5** if it cannot be
found in standard system directories.

- **CC_UBLOX_FULL_SOLUTION**=ON/OFF - This option allows to build both
[comms_champion](https://github.com/arobenko/comms_champion) and this projects
in one go. When enabled, it will checkout and build the 
[comms_champion](https://github.com/arobenko/comms_champion) prior to building
anything from this repository. All the headers, binaries, and libraries will
be installed in the directory specified with **CC_UBLOX_INSTALL_DIR** variable. 
Default value of this option is **OFF**.

## Build Example 1 
Discard all other tools, just install the **UBLOX** library:

>$> cd /path/to/ublox/sources

>$> mkdir build && cd build

>$> cmake -DCC_UBLOX_LIB_ONLY=ON ..

>$> make install 

The example above will skip build of any tool available, it will just install 
the **UBLOX** library headers in **install/include** directory

## Build Example 2
Discard all other tools, just install both **UBLOX** and **COMMS** libraries in one go:

>$> cd /path/to/ublox/sources

>$> mkdir build && cd build

>$> cmake -DCC_UBLOX_AND_COMMS_LIBS_ONLY=ON ..

>$> make install 

The example above will skip build of any tool available, it will just install 
the **UBLOX** and **COMMS** libraries headers in **install/include** directory

## Build Example 3
Install **UBLOX** library and compile (and install) the plugin for [comms_champion](https://github.com/arobenko/comms_champion)

>$> cd /path/to/ublox/sources

>$> mkdir build && cd build

>$> cmake -DCC_MAIN_INSTALL_DIR=/path/to/comms_championg/install ..

>$> make install 

## Building Documentation
The documentation is not created during normal build process. The documentation of
the [UBLOX Library](#ublox-library) can be generated by building **doc_ublox**
target:
 
>$> make doc_ublox

The HTML documentation will reside in **${CC_UBLOX_INSTALL_DIR}/doc/ublox/html** 
directory.

**NOTE**, that you must have 
[Doxygen](www.doxygen.org) 
and [Dia](https://wiki.gnome.org/Apps/Dia) 
being installed on your system in order to be able to properly generate the 
documentation.

# Contact Information
For bug reports, feature requests, or any other question you may open an issue
here in **github** or e-mail me directly to: **arobenko@gmail.com**

