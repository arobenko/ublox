<span style="color:red">**DEPRECATION NOTICE:**</span> This project contains
manual implementation of **UBX** protocol and has been deprecated.
It is no longer maintained. Please use
[cc.ublox.commsdsl](https://github.com/arobenko/cc.ublox.commsdsl) instead,
which defines the protocol using [CommsDSL](https://github.com/arobenko/CommsDSL-Specification) 
schema files. The generated outcome of protocol definition is hosted as
[cc.ublox.generated](https://github.com/arobenko/cc.ublox.generated).

-----------------------------------------------------------------------

# Overview
[u-blox GPS receivers](https://www.u-blox.com/en/position-time)
use a UBX binary protocol to transmit GPS data to a host computer using
asynchronous serial ports. This project provides a **headers only**, **platform independent**,
and **bare-metal friendly** library implemented in C++(11), which implements all 
the messages as well as wrapping 
transport protocol supported by **u-blox 4/5/6/7/8** devices.

# UBLOX Library
The library uses [COMMS library](https://github.com/arobenko/comms_champion#comms-library)
from [comms_champion](https://github.com/arobenko/comms_champion) project 
to specify **all** of the existing messages resulting in clear, concise,
and very efficient code.

The ublox binary protocol is **HUGE** and it is unlikely that any product
will require support for all the messages the protocol defines. This library
allows cherry-picking limited number of the selected messages the product requires,
which provides a great flexibility in terms of the final code size.

Full [doxygen](www.doxygen.org) generated documentation with the full tutorial inside can be
downloaded as **doc_ublox** zip archive 
from [release artefacts](https://github.com/arobenko/ublox/releases).

The "example" folder contains simple example application showing how to use the [UBLOX Library](#ublox-library). 
It is implemented using QT5 framework to drive the discovery 
and handling of asynchronous events. It configures the USB interface to be used
for UBX communication using **CFG-PRT** message and polls for **NAV-POSSLLH** 
message every second.

# CommsChampion Plugin
In addition to the library described above, this project provides a protocol
plugin for the [CommsChampion Tools](https://github.com/arobenko/comms_champion#commschampion-tools)
from the same [comms_champion](https://github.com/arobenko/comms_champion) project,
which will allow visual analysis of the u-blox binary protocol traffic.

Please refer to 
[How to Use CommsChampion with UBLOX Protocol](https://github.com/arobenko/ublox/wiki/How-to-Use-CommsChampion-with-UBLOX-Protocol) 
wiki page for instructions on how to analyse the UBX binary protocol using the
[CommsChampion Tools](https://github.com/arobenko/comms_champion#commschampion-tools).

# Licence
The [UBLOX Library](#ublox-library) as well as [CommsChampion Plugin](#commschampion-plugin) 
from this repository are licensed under
the classic **GPLv3 / Commercial** dual licensing scheme in the same way as 
[CommsChampion](https://github.com/arobenko/comms_champion) project
(see [LICENSE.md](https://github.com/arobenko/comms_champion/blob/master/LICENSE.md) for details). The
source code is available for anyone to use as long as the derivative work
remains open source with compatible licence. **Download** and **try** it! If it works
as expected and commercial closed source licence is required for the final
product, please send me an e-mail (see [Contact Information](#contact-information) below).

# How to Build
Detailed instructions on how to build and install all the components can be
found in [BUILD.md](BUILD.md) file.

# Branching Model
This repository will follow the 
[Successful Git Branching Model](http://nvie.com/posts/a-successful-git-branching-model/).

The **master** branch will always point to the latest release, the
development is performed on **develop** branch. As the result it is safe
to just clone the sources of this repository and use it without
any extra manipulations of looking for the latest stable version among the tags and
checking it out.

# Contact Information
For bug reports, feature requests, or any other question you may open an issue
here in **github** or e-mail me directly to: **arobenko@gmail.com**

