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

namespace cfg
{

using PortID = common::U1;

enum CharLength : std::uint8_t
{
    CharLength_5,
    CharLength_6,
    CharLength_7,
    CharLength_8,
    NumOfValues
};

enum class Parity : std::uint8_t
{
    Even,
    Odd,
    NoParity = 4,
    NoParity2
};

struct ParityValidityCheck
{
    template <typename TField>
    bool operator()(const TField& field) const
    {
        auto value = field.value();
        return
            (value == Parity::Even) ||
            (value == Parity::Odd) ||
            (value == Parity::NoParity) ||
            (value == Parity::NoParity2);
    }
};

enum class StopBit : std::uint8_t
{
    One,
    OneAndHalf,
    Two,
    NumOfValues
};

enum class BitOrder : std::uint8_t
{
    LsbFirst,
    MsbFirst,
    NumOfValues
};

enum class Oversampling : std::uint8_t
{
    x16,
    x8,
    NumOfValues
};

using Mode =
    comms::field::Bitfield<
        common::FieldBase,
        std::tuple<
            comms::field::IntValue<
                common::FieldBase,
                std::uint8_t,
                comms::option::FixedBitLength<6>,
                comms::option::ValidNumValueRange<0, 0>
            >,
            comms::field::EnumValue<
                common::FieldBase,
                CharLength,
                comms::option::ValidNumValueRange<(int)CharLength::CharLength_5, (int)CharLength::NumOfValues - 1>,
                comms::option::FixedBitLength<2>
            >,
            comms::field::IntValue<
                common::FieldBase,
                std::uint8_t,
                comms::option::FixedBitLength<1>,
                comms::option::ValidNumValueRange<0, 0>
            >,
            comms::field::EnumValue<
                common::FieldBase,
                Parity,
                comms::option::ContentsValidator<ParityValidityCheck>,
                comms::option::FixedBitLength<3>
            >,
            comms::field::EnumValue<
                common::FieldBase,
                StopBit,
                comms::option::ValidNumValueRange<(int)StopBit::One, (int)StopBit::NumOfValues - 1>,
                comms::option::FixedBitLength<2>
            >,
            comms::field::IntValue<
                common::FieldBase,
                std::uint8_t,
                comms::option::FixedBitLength<2>,
                comms::option::ValidNumValueRange<0, 0>
            >,
            comms::field::EnumValue<
                common::FieldBase,
                BitOrder,
                comms::option::ValidNumValueRange<(int)BitOrder::LsbFirst, (int)BitOrder::NumOfValues - 1>,
                comms::option::FixedBitLength<1>
            >,
            comms::field::IntValue<
                common::FieldBase,
                std::uint8_t,
                comms::option::FixedBitLength<2>,
                comms::option::ValidNumValueRange<0, 0>
            >,
            comms::field::EnumValue<
                common::FieldBase,
                Oversampling,
                comms::option::ValidNumValueRange<(int)Oversampling::x16, (int)Oversampling::NumOfValues - 1>,
                comms::option::FixedBitLength<1>
            >,
            comms::field::IntValue<
                common::FieldBase,
                std::uint16_t,
                comms::option::FixedBitLength<12>,
                comms::option::ValidNumValueRange<0, 0>
            >
        >
    >;

using Baudrate = common::U4;

using ProtoMask =
    comms::field::BitmaskValue<
        common::FieldBase,
        comms::option::FixedLength<2>,
        comms::option::BitmaskReservedBits<0x0ff8, 0>
    >;

using PrtFlags =
    comms::field::BitmaskValue<
        common::FieldBase,
        comms::option::FixedLength<2>,
        comms::option::BitmaskReservedBits<0xfffe, 0>
    >;

using Rate = common::U1;

enum class ProtocolIdVal : std::uint8_t
{
    Ubx,
    Nmea,
    Rtcm,
    Raw,
    User0 = 12,
    User1,
    User2,
    User3
};

struct ProtocolIdValidator
{
    template <typename TField>
    bool operator()(const TField& field) const
    {
        auto value = field.value();
        return
            ((ProtocolIdVal::Ubx <= value) && (value <= ProtocolIdVal::Raw)) ||
            ((ProtocolIdVal::User0 <= value) && (value <= ProtocolIdVal::User3));
    }
};

using ProtocolID =
    comms::field::EnumValue<
        common::FieldBase,
        ProtocolIdVal,
        comms::option::ContentsValidator<ProtocolIdValidator>
    >;

using INFMSG_mask =
    comms::field::BitmaskValue<
        common::FieldBase,
        comms::option::FixedLength<1U>,
        comms::option::BitmaskReservedBits<0x60, 0>
    >;

using INFMSG_mask_res =
    comms::field::BitmaskValue<
        common::FieldBase,
        comms::option::FixedLength<1U>,
        comms::option::BitmaskReservedBits<0xff, 0>
    >;

using nav_bbr =
    comms::field::BitmaskValue<
        common::FieldBase,
        comms::option::FixedLength<2U>,
        comms::option::BitmaskReservedBits<0xfe00, 0>
    >;

enum class ResetType : std::uint8_t
{
    Hardware,
    Software,
    GpsOnly,
    GpsStop = 8,
    GpsStart
};

struct ResetTypeValidator
{
    template <typename TField>
    bool operator()(const TField& field) const
    {
        auto value = field.value();
        return
            ((ResetType::Hardware <= value) && (value <= ResetType::GpsOnly)) ||
            ((ResetType::GpsStop <= value) && (value <= ResetType::GpsStart));
    }
};

using Reset =
    comms::field::EnumValue<
        common::FieldBase,
        ResetType,
        comms::option::ContentsValidator<ResetTypeValidator>
    >;

using DatumNum = common::U2;

using Datum =
    comms::field::String<
        common::FieldBase,
        comms::option::SequenceFixedSize<5>,
        comms::option::SequenceTrailingFieldSuffix<
            comms::field::IntValue<
                common::FieldBase,
                std::uint8_t,
                comms::option::ValidNumValueRange<0, 0>
            >
        >
    >;

using majA = common::R8T<comms::option::ValidNumValueRange<6300000, 6500000> >;
using flat = common::R8T<comms::option::ValidNumValueRange<0, 500> >;
using dX = common::R4T<comms::option::ValidNumValueRange<-5000, 5000> >;
using dY = common::R4T<comms::option::ValidNumValueRange<-5000, 5000> >;
using dZ = common::R4T<comms::option::ValidNumValueRange<-5000, 5000> >;
using rotX = common::R4T<comms::option::ValidNumValueRange<-20, 20> >;
using rotY = common::R4T<comms::option::ValidNumValueRange<-20, 20> >;
using rotZ = common::R4T<comms::option::ValidNumValueRange<-20, 20> >;
using scale = common::R4T<comms::option::ValidNumValueRange<0, 50> >;

using interval = common::U4;
using length = common::U4;
using status = common::I1;
using Time = common::U1;
using antenna_cable_delay = common::I2;
using RF_group_delay = common::I2;
using user_delay = common::I4;

using Meas = common::U2;
using Nav = common::U2;

using Cfg_mask =
    comms::field::BitmaskValue<
        common::FieldBase,
        comms::option::FixedLength<4U>,
        comms::option::BitmaskReservedBits<0xffff0800, 0>
    >;

using fxn_flags =
    comms::field::BitmaskValue<
        common::FieldBase,
        comms::option::FixedLength<4U>,
        comms::option::BitmaskReservedBits<0xffffffe4, 0>
    >;

using t_reacq = common::U4;
using t_acq = common::U4;
using t_reacq_off = common::U4;
using t_acq_off = common::U4;
using t_on = common::U4;
using t_off = common::U4;
using base_tow = common::U4;

}  // namespace cfg

}  // namespace field

}  // namespace ublox


