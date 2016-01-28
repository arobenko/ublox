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
/// @brief Contains common definitions of CFG-PRT message fields.

#pragma once

#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Common fields for CFG-PRT messages.
/// @see CfgPrtDdc
/// @see CfgPrtSpi
/// @see CfgPrtUart
/// @see CfgPrtUsb
struct CfgPrtFields
{
    /// @brief Value enumeration for "portID" fields (see @ref CfgPrtDdcFields::portID,
    ///     @ref CfgPrtSpiFields::portID, @ref CfgPrtUartFields::portID, and
    ///     @ref CfgPrtUsbFields::portID).
    enum class PortId : std::uint8_t
    {
        DDC = 0, ///< DDC
        UART = 1, ///< UART
        UART2 = 2, ///< UART2
        USB = 3, ///< USB
        SPI = 4, ///< SPI
    };

    /// @brief Value enumeration for @ref pol member field of @ref txReady bitfield.
    enum class Polarity : std::uint8_t
    {
        HighActive, ///< high-active
        LowActive, ///< low-active
        NumOfValues ///< number of available values
    };

    /// @brief Use this enumeration to access member fields of @ref txReady bitfield.
    enum
    {
        txReady_en, ///< index of @ref en member field
        txReady_pol, ///< index of @ref pol member field
        txReady_pin, ///< index of @ref pin member field
        txReady_thres, ///< index of @ref thres member field
        txReady_numOfValues ///< number of available member fields
    };

    /// @brief Bits access enumeration for single bit @ref en bitmask member
    ///     field of @ref txReady bitfield.
    enum
    {
        en_bit, ///< index of available bit
        en_numOfValues ///< number of available bits
    };

    /// @brief Bits access enumeration for @ref inProtoMask bitmask field.
    enum
    {
        inProtoMask_inUbx, ///< @b inUbx bit index
        inProtoMask_inNmea, ///< @b inNmea bit index
        inProtoMask_inRtcm, ///< @b inRtcm bit index
        inProtoMask_numOfValues ///< number of available bits
    };

    /// @brief Bits access enumeration for @ref outProtoMask bitmask field.
    enum
    {
        outProtoMask_outUbx, ///< @b outUbx bit index
        outProtoMask_outNmea, ///< @b outNmea bit index
        outProtoMask_numOfValues ///< number of available bits
    };

    /// @brief Bits access enumeration for @ref flags bitmask field.
    enum
    {
        flags_extendedTxTimeout = 1, ///< @b extendedTxTimeout bit index
        flags_numOfValues ///< upper limit for available bits
    };

    /// @brief Definition of "reserved0" field.
    using reserved0 = field::common::res1;

    /// @brief Definition of "en" single bit bitmask member field in @ref txReady bitfield.
    using en = field::common::X1T<comms::option::FixedBitLength<1> >;

    /// @brief Definition of "pol" member field in @ref txReady bitfield
    using pol =
        field::common::EnumT<
            Polarity,
            comms::option::FixedBitLength<1>,
            comms::option::ValidNumValueRange<0, (int)Polarity::NumOfValues - 1>
        >;

    /// @brief Definition of "pin" member field in @ref txReady bitfield
    using pin =
        field::common::U1T<
            comms::option::FixedBitLength<5>,
            comms::option::ValidNumValueRange<0, 31>
        >;

    /// @brief Definition of "thres" member field in @ref txReady bitfield
    using thres =
        field::common::U2T<
            comms::option::FixedBitLength<9>,
            comms::option::ValidNumValueRange<0, 0x1ff>
        >;


    /// @brief Definition of "txReady" field.
    using txReady =
        field::common::BitfieldT<
            std::tuple<
                en,
                pol,
                pin,
                thres
            >
        >;

    /// @brief Definition of "reserved3" field
    using reserved3 = field::common::res4;

    /// @brief Definition of "inProtoMask" field.
    using inProtoMask =
        field::common::X2T<comms::option::BitmaskReservedBits<0xfff8, 0> >;

    /// @brief Definition of "outProtoMask" field.
    using outProtoMask =
        field::common::X2T<comms::option::BitmaskReservedBits<0xfffc, 0> >;

    /// @brief Definition of "flags" field.
    using flags =
        field::common::X2T<comms::option::BitmaskReservedBits<0xfffd, 0> >;

    /// @brief Definition of "reserved5" field
    using reserved5 = field::common::res2;
};


}  // namespace message

}  // namespace ublox





