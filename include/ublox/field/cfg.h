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

/// @file
/// @brief Contains definition of common fields used in CFG class messages.

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
    common::BitfieldT<
        std::tuple<
            common::X1T<comms::option::FixedBitLength<1> >,
            common::EnumT<
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

enum class PortId : std::uint8_t
{
    DDC = 0,
    UART = 1,
    UART2 = 2,
    USB = 3,
    SPI = 4
};

/// @brief Common enumeration for protocol ID value
enum class ProtocolId : std::uint8_t
{
    UBX, ///< UBX protocol being used/configured
    NMEA, ///< NMEA protocol being used/configured
    NumOfValues ///< number of available values
};

/// @brief Definition of common "protocolID" field.
using protocolID =
    common::EnumT<
        ProtocolId,
        comms::option::ValidNumValueRange<0, (int)ProtocolId::NumOfValues - 1>
    >;

/// @brief Definition of common "datumNum" field.
using datumNum = common::U2;

/// @brief Definition of common "datumName" field.
using datumName = common::ZString<6>;

/// @brief Definition of common "majA" field used CFG-DAT messages.
using datMajA = common::R8;

/// @brief Definition of common "flat" field used CFG-DAT messages.
using datFlat = common::R8;

/// @brief Definition of common "dX" field used CFG-DAT messages.
using datDX = common::R4;

/// @brief Definition of common "dY" field used CFG-DAT messages.
using datDY = common::R4;

/// @brief Definition of common "dZ" field used CFG-DAT messages.
using datDZ = common::R4;

/// @brief Definition of common "rotX" field used CFG-DAT messages.
using datRotX = common::R4;

/// @brief Definition of common "rotY" field used CFG-DAT messages.
using datRotY = common::R4;

/// @brief Definition of common "rotZ" field used CFG-DAT messages.
using datRotZ = common::R4;

/// @brief Definition of common "scale" field used CFG-DAT messages.
using datScale = common::R4;

enum class TpIdx : std::uint8_t
{
    TIMEPULSE,
    TIMEPULSE2,
    NumOfValues
};

using tpIdx =
    common::EnumT<
        TpIdx,
        comms::option::ValidNumValueRange<0, (int)TpIdx::NumOfValues - 1>
    >;



}  // namespace cfg

}  // namespace field

}  // namespace ublox


