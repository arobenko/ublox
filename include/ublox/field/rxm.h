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

namespace rxm
{

using ITOW = common::ITOW;
using Week = common::Week;
using NSV = common::U1;

using CPMes = common::R8;
using PRMes = common::R8;
using DOMes = common::R4;
using SV = common::U1;
using MesQI = common::I1;
using CNO = common::I1;
using LLI = common::U1;

using NumVis = common::U1;
using NumSv = common::U1;
using SVID = common::SVID;

using URA =
    common::U1T<
        comms::option::ValidNumValueRange<0, 15>,
        comms::option::FixedBitLength<4>
    >;

using StatusInfoFlags =
    comms::field::BitmaskValue<
        common::FieldBase,
        comms::option::FixedBitLength<4>
    >;

using StatusInfoSvFlag =
    comms::field::Bitfield<
        common::FieldBase,
        std::tuple<
            URA,
            StatusInfoFlags
        >
    >;

using Azim = common::Azim;
using Elev = common::Elev;

using AlmAge =
    common::U1T<
        comms::option::ValidNumValueRange<0, 15>,
        comms::option::FixedBitLength<4>
    >;

using EphAge = AlmAge;

using Age =
    comms::field::Bitfield<
        common::FieldBase,
        std::tuple<
            AlmAge,
            EphAge
        >
    >;

using CHN = common::U1;
using DWORD = common::I4;

using SVID_Ext = common::U4T<comms::option::ValidNumValueRange<1, 32> >;
using WEEK_Ext = common::U4;

using HOW = common::U4;
using SFxDx = common::U4;

}  // namespace rxm

}  // namespace field

}  // namespace ublox


