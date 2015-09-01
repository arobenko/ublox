//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
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


#pragma once

#include "common.h"

namespace ublox
{

namespace field
{

namespace nav
{

using iTOW = common::iTOW;
using fTOW =
    common::I4T<
        common::Scaling_ns2s,
        comms::option::ValidNumValueRange<-500000, 500000>
    >;
;

using ecef = common::I4T<common::Scaling_cm2m>;
using ecefX = ecef;
using ecefY = ecef;
using ecefZ = ecef;
using ecefVX = ecef;
using ecefVY = ecef;
using ecefVZ = ecef;

using lat = common::I4T<comms::option::ScalingRatio<1, 10000000L> >;
using lon = common::I4T<comms::option::ScalingRatio<1, 10000000L> >;
using height = common::I4T<common::Scaling_mm2m>;

using pAcc = common::U4T<common::Scaling_cm2m>;
using sAcc = common::U4T<common::Scaling_cm2m>;

using hMSL = common::I4T<common::Scaling_mm2m>;
using hAcc = common::U4T<common::Scaling_mm2m>;
using vAcc = common::U4T<common::Scaling_mm2m>;

enum class GpsFix : std::uint8_t
{
    NoFix,
    DeadReckoningOnly,
    Fix_2D,
    Fix_3D,
    GPS_DeadReckoning,
    TimeOnlyFix,
    NumOfValues
};

using gpsFix =
    comms::field::EnumValue<
        common::FieldBase,
        GpsFix,
        comms::option::ValidNumValueRange<0, (int)GpsFix::NumOfValues - 1>
    >;

using week = common::week;

using xDOP = field::common::U2T<comms::option::ScalingRatio<1, 100> >;
using pDOP = xDOP;

using numSV = common::numSV;

using year =
    common::U2T<
        comms::option::ValidNumValueRange<1999, 2099>
    >;

using month =
    common::U1T<
        comms::option::ValidNumValueRange<1, 12>
    >;

using day =
    common::U1T<
        comms::option::ValidNumValueRange<1, 31>
    >;

using hour =
    common::U1T<
        comms::option::ValidNumValueRange<0, 23>
    >;

using min =
    common::U1T<
        comms::option::ValidNumValueRange<0, 59>
    >;

using sec =
    common::U1T<
        comms::option::ValidNumValueRange<0, 60>
    >;

using tAcc = common::U4T<common::Scaling_ns2s>;

using nano =
    common::I4T<
        common::Scaling_ns2s,
        comms::option::ValidNumValueRange<-1000000000L, 1000000000>
    >;

using heading =
    common::I4T<
        comms::option::ScalingRatio<1, 100000> >;

using numCh = common::U1;

using svid = common::svid;

}  // namespace nav

}  // namespace field

}  // namespace ublox




