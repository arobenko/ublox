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

using ITOW = common::U4;

using ECEF = common::I4;

using ECEF_X = ECEF;
using ECEF_Y = ECEF;
using ECEF_Z = ECEF;

using Pacc = common::U4;
using Hacc = common::U4;
using Vacc = common::U4;

using LON = common::I4;
using LAT = common::I4;
using HEIGHT = common::I4;
using HMSL = common::I4;

using EAST = common::I4;
using NORTH = common::I4;
using ALT = common::I4;

using ZONE = common::I1;

enum class HemIndicator : std::int8_t
{
    North,
    South
};

using HEM =
    comms::field::EnumValue<
        common::FieldBase,
        HemIndicator,
        comms::option::ValidNumValueRange<(int)HemIndicator::North, (int)HemIndicator::South>
    >;

using GDOP = common::U2;
using PDOP = common::U2;
using TDOP = common::U2;
using VDOP = common::U2;
using HDOP = common::U2;
using NDOP = common::U2;
using EDOP = common::U2;

}  // namespace nav

}  // namespace field

}  // namespace ublox




