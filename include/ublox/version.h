//
// Copyright 2018 (C). Alex Robenko. All rights reserved.
//

// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

/// @file
/// @brief Contains version of th elibrary.

#pragma once


#include "comms/version.h"

/// @brief Major verion of the library
#define UBLOX_MAJOR_VERSION 0U

/// @brief Minor verion of the library
#define UBLOX_MINOR_VERSION 9U

/// @brief Patch level of the library
#define UBLOX_PATCH_VERSION 2U

/// @brief Version of the UBLOX library as single numeric value
#define UBLOX_VERSION \
    COMMS_MAKE_VERSION(UBLOX_MAJOR_VERSION, UBLOX_MINOR_VERSION, UBLOX_PATCH_VERSION)


namespace ublox
{

/// @brief Major verion of the library
inline
constexpr unsigned versionMajor()
{
    return UBLOX_MAJOR_VERSION;
}

/// @brief Minor verion of the library
inline
constexpr unsigned versionMinor()
{
    return UBLOX_MINOR_VERSION;
}

/// @brief Patch level of the library
inline
constexpr unsigned versionPatch()
{
    return UBLOX_PATCH_VERSION;
}

/// @brief Version of the COMMS library as single numeric value
inline
constexpr unsigned version()
{
    return UBLOX_VERSION;
}

static_assert(comms::versionCreate(0U, 24U, 0U) <= comms::version(),
        "COMMS library needs to be updgraded");

}  // namespace ublox


