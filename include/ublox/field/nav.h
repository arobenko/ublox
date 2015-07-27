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

using ITOW = common::ITOW;

using ECEF = common::I4;

using ECEF_X = ECEF;
using ECEF_Y = ECEF;
using ECEF_Z = ECEF;
using ECEFVX = ECEF;
using ECEFVY = ECEF;
using ECEFVZ = ECEF;

using Pacc = common::U4;
using Hacc = common::U4;
using Vacc = common::U4;
using Sacc = common::U4;
using Cacc = common::U4;
using Tacc = common::U4;
using Facc = common::U4;

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

enum class GPSFixType : std::uint8_t
{
    NoFix,
    DeadReckoningOnly,
    Fix_2D,
    Fix_3D,
    GPS_DeadReckoning,
    TimeOnlyFix,
    NumOfValues
};

using GPSfix =
    comms::field::EnumValue<
        common::FieldBase,
        GPSFixType,
        comms::option::ValidNumValueRange<(int)GPSFixType::NoFix, (int)GPSFixType::NumOfValues - 1>
    >;

using Flags =
    comms::field::BitmaskValue<
        common::FieldBase,
        comms::option::FixedLength<1>,
        comms::option::BitmaskReservedBits<0xf0, 0>
    >;

enum class DiffStatus : std::uint8_t
{
    None,
    PR_PRR,
    PR_PRR_CP,
    HighAcc_PR_PRR_CP,
    NumOfValues
};

using DiffS =
    comms::field::EnumValue<
        common::FieldBase,
        DiffStatus,
        comms::option::ValidNumValueRange<(int)DiffStatus::None, (int)DiffStatus::NumOfValues - 1>
    >;

using TTFF = common::U4;
using MSSS = common::U4;

using Frac =
    common::I4T<
        comms::option::ValidNumValueRange<-500000, 500000>
    >;

using Nano =
    common::I4T<
        comms::option::ValidNumValueRange<-500000000, 500000000>
    >;


using week = common::Week;
using numSV = common::U1;

using VEL = common::I4;
using VEL_N = VEL;
using VEL_E = VEL;
using VEL_D = VEL;

using Speed = common::U4;
using GSpeed = common::U4;
using Heading = common::I4;

using LeapS = common::I1;
using TimeValid =
    comms::field::BitmaskValue<
        common::FieldBase,
        comms::option::FixedLength<1>,
        comms::option::BitmaskReservedBits<0xf8, 0>
    >;

using Year =
    common::U2T<
        comms::option::ValidNumValueRange<1999, 2099>
    >;

using Month =
    common::U1T<
        comms::option::ValidNumValueRange<1, 12>
    >;

using Day =
    common::U1T<
        comms::option::ValidNumValueRange<1, 31>
    >;

using Hour =
    common::U1T<
        comms::option::ValidNumValueRange<0, 23>
    >;

using Min =
    common::U1T<
        comms::option::ValidNumValueRange<0, 59>
    >;

using Sec = Min;

using CLKB = common::I4;
using CLKD = common::I4;

template <typename... TOptions>
using NCHT = common::U1T<comms::option::ValidNumValueRange<0, 16>, TOptions...>;
using NCH = NCHT<>;

template <typename... TOptions>
using chnT = NCHT<TOptions...>;
using chn = NCH;

using SVID = common::SVID;

using InfoFlags =
    comms::field::BitmaskValue<
        common::FieldBase,
        comms::option::FixedLength<1>,
        comms::option::BitmaskReservedBits<0xe0, 0>
    >;

enum class SigQuality : std::uint8_t
{
    Idle,
    Searching,
    Searching2,
    DetectedUnusable,
    CodeLock,
    CodeCarrierLock,
    CodeCarrierLock2,
    CodeCarrierLock_50bpsData,
    NumOfValues
};

using QI =
    comms::field::EnumValue<
        common::FieldBase,
        SigQuality,
        comms::option::ValidNumValueRange<(int)SigQuality::Idle, (int)SigQuality::NumOfValues - 1>
    >;

using CNO = common::U1;
using Elev = common::Elev;
using Azim = common::Azim;
using PRRes = common::I4;

using AGE = common::I4;
using BASEID = common::I2;
using BASEHLTH = common::I2;
using STATUS = DiffS;

template <typename... TOptions>
using DgpsFlagsT =
    comms::field::BitmaskValue<
        common::FieldBase,
        comms::option::FixedLength<1>,
        comms::option::BitmaskReservedBits<0xfe, 0>,
        TOptions...
    >;

using DgpsFlags = DgpsFlagsT<>;

using AGECH = common::U2;
using PRC = common::R4;
using PRRC = common::R4;

using GEO = common::U1;

enum class SbasMode : std::uint8_t
{
    Disabled,
    EnabledIntegrity,
    EnabledTestmode = 3,
    NumOfValues
};

using MODE =
    comms::field::EnumValue<
        common::FieldBase,
        SbasMode,
        comms::option::ValidNumValueRange<(int)SbasMode::Disabled, (int)SbasMode::NumOfValues - 1>
    >;

enum SbasSys : std::int8_t
{
    Unknown = -1,
    WAAS = 0,
    EGNOS = 1,
    MSAS = 2,
    GPS = 16
};

struct SbasSysValidator
{
    template <typename TField>
    bool operator()(const TField& field) const
    {
        auto val = field.value();
        return ((SbasSys::Unknown <= val) && (val <= SbasSys::MSAS)) ||
               (val == SbasSys::GPS);
    }
};

using SYS =
    comms::field::EnumValue<
        common::FieldBase,
        SbasSys,
        comms::option::ContentsValidator<SbasSysValidator>
    >;

using SERVICE =
    comms::field::BitmaskValue<
        common::FieldBase,
        comms::option::FixedLength<1>,
        comms::option::BitmaskReservedBits<0xf0, 0>
    >;

using PRCcm = common::I2;

using CNT = common::U1;
using UDRE = common::U1;
using IC = common::I2;

using pulses = common::I4;
using period = common::I4;
using gyromean = common::U4;
using temperature = common::I2;
using direction = common::I1;

enum class CalibStatus : std::uint8_t
{
    NoCalibration,
    Calibrating,
    CoarseCalibration,
    FineCalibration,
    NumOfValues
};

using CalibStatusField =
    comms::field::EnumValue<
        common::FieldBase,
        CalibStatus,
        comms::option::FixedBitLength<2>,
        comms::option::ValidNumValueRange<(int)CalibStatus::NoCalibration, (int)CalibStatus::NumOfValues - 1>
    >;

using calib_status =
    comms::field::Bitfield<
        common::FieldBase,
        std::tuple<
            CalibStatusField,
            CalibStatusField,
            CalibStatusField,
            common::U1T<comms::option::FixedBitLength<2>>
        >
    >;

using pulse_scale = common::I4;
using gyro_bias = common::I4;
using gyro_scale = common::I4;
using acc_pulse_scale = common::I2;
using acc_gyro_bias = common::I2;
using acc_gyro_scale = common::I2;
using meas_used =
    comms::field::BitmaskValue<
        common::FieldBase,
        comms::option::FixedLength<1>
    >;

}  // namespace nav

}  // namespace field

}  // namespace ublox




