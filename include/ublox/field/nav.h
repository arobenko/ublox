//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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
/// @brief Contains definition of common fields used in NAV class messages.

#pragma once

#include "common.h"

namespace ublox
{

namespace field
{

namespace nav
{

/// @brief Definition of common "iTOW" field.
using iTOW = common::iTOW;

/// @brief Definition of common "fTOW" field.
using fTOW =
    common::I4T<
        comms::option::UnitsNanoseconds,
        comms::option::ValidNumValueRange<-500000, 500000>
    >;
;

/// @brief Definition of common "ecef" field.
using ecef = common::I4T<comms::option::UnitsCentimeters>;

/// @brief Definition of common "ecefX" field.
using ecefX = ecef;

/// @brief Definition of common "ecefY" field.
using ecefY = ecef;

/// @brief Definition of common "ecefZ" field.
using ecefZ = ecef;

/// @brief Definition of common "ecefVX" field.
using ecefVX = common::I4T<comms::option::UnitsCentimetersPerSecond>;

/// @brief Definition of common "ecefVY" field.
using ecefVY = ecefVX;

/// @brief Definition of common "ecefVZ" field.
using ecefVZ = ecefVX;

/// @brief Definition of common "lat" field.
using lat =
    common::I4T<
        comms::option::ScalingRatio<1, 10000000L>,
        comms::option::UnitsDegrees
    >;

/// @brief Definition of common "lon" field.
using lon =
    common::I4T<
        comms::option::ScalingRatio<1, 10000000L>,
        comms::option::UnitsDegrees
    >;

/// @brief Definition of common "height" field.
using height = common::I4T<comms::option::UnitsMillimeters>;

/// @brief Definition of common "pAcc" field.
using pAcc = common::U4T<comms::option::UnitsCentimeters>;

/// @brief Definition of common "sAcc" field.
using sAcc = common::U4T<comms::option::UnitsCentimetersPerSecond>;

/// @brief Definition of common "hMSL" field.
using hMSL = common::I4T<comms::option::UnitsMillimeters>;

/// @brief Definition of common "hAcc" field.
using hAcc = common::U4T<comms::option::UnitsMillimeters>;

/// @brief Definition of common "vAcc" field.
using vAcc = common::U4T<comms::option::UnitsMillimeters>;

/// @brief Value enumeration for @ref ublox::field::nav::gpsFix field.
enum class GpsFix : std::uint8_t
{
    NoFix, ///< No fix
    DeadReckoningOnly, ///< dead reckoning only
    Fix_2D, ///< 2D fix
    Fix_3D, ///< 3D fix
    GPS_DeadReckoning, ///< GPS + dead reckoning
    TimeOnlyFix, ///< time only fix
    NumOfValues ///< number of available values
};

/// @brief Definition of common "gpsFix" field.
using gpsFix =
    common::EnumT<
        GpsFix,
        comms::option::ValidNumValueRange<0, (int)GpsFix::NumOfValues - 1>
    >;

/// @brief Definition of common "week" field.
using week = common::week;

/// @brief Definition of common "pDOP" field.
using pDOP = field::common::U2T<comms::option::ScalingRatio<1, 100> >;

/// @brief Definition of common "numSV" field.
using numSV = common::numSV;

/// @brief Definition of common "year" field.
using year =
    common::U2T<
        comms::option::ValidNumValueRange<1999, 2099>
    >;

/// @brief Definition of common "month" field.
using month =
    common::U1T<
        comms::option::ValidNumValueRange<1, 12>
    >;

/// @brief Definition of common "day" field.
using day =
    common::U1T<
        comms::option::ValidNumValueRange<1, 31>,
        comms::option::UnitsDays
    >;


/// @brief Definition of common "hour" field.
using hour =
    common::U1T<
        comms::option::ValidNumValueRange<0, 23>,
        comms::option::UnitsHours
    >;


/// @brief Definition of common "min" field.
using min =
    common::U1T<
        comms::option::ValidNumValueRange<0, 59>,
        comms::option::UnitsMinutes
    >;


/// @brief Definition of common "sec" field.
using sec =
    common::U1T<
        comms::option::ValidNumValueRange<0, 60>,
        comms::option::UnitsSeconds
    >;

/// @brief Definition of common "tAcc" field.
using tAcc = common::U4T<comms::option::UnitsNanoseconds>;

/// @brief Definition of common "nano" field.
using nano =
    common::I4T<
        comms::option::UnitsNanoseconds,
        comms::option::ValidNumValueRange<-1000000000L, 1000000000>
    >;


/// @brief Definition of common "heading" field.
using heading =
    common::I4T<
        comms::option::ScalingRatio<1, 100000>,
        comms::option::UnitsDegrees
    >;

/// @brief Definition of common "numCh" field.
using numCh = common::U1;

/// @brief Definition of common "svid" field.
using svid = common::svid;

/// @brief Value enumeration for @ref carrSoln field.
enum class CarrSoln : std::uint8_t
{
    NoCarrier, ///< no carrier phase range solution
    Float, /// float solution,
    Fixed, /// fixed solution
    NumOfValues
};

/// @brief Definition of "carrSoln" field.
template <typename... TOpts>
using carrSoln =
    common::EnumT<
        CarrSoln,
        comms::option::ValidNumValueRange<0, (int)CarrSoln::NumOfValues - 1>,
        TOpts...
    >;


}  // namespace nav

}  // namespace field

}  // namespace ublox




