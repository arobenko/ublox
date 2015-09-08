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

#include <algorithm>

#include "common.h"

namespace ublox
{

namespace field
{

namespace cfg
{

enum class Polarity : std::uint8_t
{
    HighActive,
    LowActive,
    NumOfValues
};

using txReady =
    comms::field::Bitfield<
        common::FieldBase,
        std::tuple<
            common::X1T<comms::option::FixedBitLength<1> >,
            comms::field::EnumValue<
                common::FieldBase,
                Polarity,
                comms::option::FixedBitLength<1>,
                comms::option::ValidNumValueRange<0, (int)Polarity::NumOfValues - 1>
            >,
            common::U1T<
                comms::option::FixedBitLength<5>,
                comms::option::ValidNumValueRange<0, 31>
            >,
            common::U2T<
                comms::option::FixedBitLength<9>,
                comms::option::ValidNumValueRange<0, 0x1ff>
            >
        >
    >;

using inProtoMask =
    common::X2T<comms::option::BitmaskReservedBits<0xfff8, 0> >;

using outProtoMask =
    common::X2T<comms::option::BitmaskReservedBits<0xfffc, 0> >;

using prtFlags =
    common::X2T<comms::option::BitmaskReservedBits<0xfffd, 0> >;

using rate = common::U1;

enum class PortId : std::uint8_t
{
    DDC = 0,
    UART = 1,
    UART2 = 2,
    USB = 3,
    SPI = 4
};

enum class ProtocolId : std::uint8_t
{
    UBX,
    NMEA,
    NumOfValues
};

using protocolID =
    comms::field::EnumValue<
        field::common::FieldBase,
        ProtocolId,
        comms::option::ValidNumValueRange<0, (int)ProtocolId::NumOfValues - 1>
    >;

using datumNum = field::common::U2;
using datumName =
    comms::field::String<
        common::FieldBase,
        comms::option::SequenceFixedSize<5>,
        comms::option::SequenceTrailingFieldSuffix<
            common::U1T<
                comms::option::ValidNumValueRange<0, 0>
            >
        >
    >;
using datMajA = common::R8;
using datFlat = common::R8;
using datDX = common::R4;
using datDY = common::R4;
using datDZ = common::R4;
using datRotX = common::R4;
using datRotY = common::R4;
using datRotZ = common::R4;
using datScale = common::R4;

}  // namespace cfg

}  // namespace field

}  // namespace ublox


