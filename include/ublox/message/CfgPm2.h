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

#include "comms/Message.h"
#include "ublox/Message.h"
#include "ublox/field/MsgId.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

enum class CfgPm2_ExtintSelect : std::uint8_t
{
    EXTINT0,
    EXTINT1,
    NumOfValues
};

enum class CfgPm2_DisabledEnabled : std::uint8_t
{
    Disabled,
    Enabled,
    NumOfValues
};

using CfgPm2_ExtintWake = CfgPm2_DisabledEnabled;
using CfgPm2_ExtintBackup = CfgPm2_DisabledEnabled;
using CfgPm2_LimitPeakCurr = CfgPm2_DisabledEnabled;

enum class CfgPm2_Mode : std::uint8_t
{
    OnOff,
    CyclicTracking,
    NumOfValues
};

enum
{
    CfgPm2Field_flags_reserved,
    CfgPm2Field_flags_extintSelect,
    CfgPm2Field_flags_extintWake,
    CfgPm2Field_flags_extintBackup,
    CfgPm2Field_flags_reserved2,
    CfgPm2Field_flags_limitPeakCurr,
    CfgPm2Field_flags_flags,
    CfgPm2Field_flags_mode,
    CfgPm2Field_flags_reserved3,
    CfgPm2Field_flags_numOfValues,
};

enum
{
    CfgPm2Field_flags_flags_waitTimeFix,
    CfgPm2Field_flags_flags_updateRTC,
    CfgPm2Field_flags_flags_updateEPH,
    CfgPm2Field_flags_flags_doNotEnterOff = CfgPm2Field_flags_flags_updateEPH + 4,
    CfgPm2Field_flags_flags_numOfValues
};

using CfgPm2Field_version =
    field::common::U1T<
        comms::option::DefaultNumValue<1>,
        comms::option::ValidNumValueRange<1, 1>
    >;
using CfgPm2Field_reserved1 = field::common::res1;
using CfgPm2Field_reserved2 = field::common::res1;
using CfgPm2Field_reserved3 = field::common::res1;
using CfgPm2Field_flags =
    comms::field::Bitfield<
        field::common::FieldBase,
        std::tuple<
            field::common::res1T<
                comms::option::FixedBitLength<4>
            >,
            comms::field::EnumValue<
                field::common::FieldBase,
                CfgPm2_ExtintSelect,
                comms::option::ValidNumValueRange<0, (int)CfgPm2_ExtintSelect::NumOfValues - 1>,
                comms::option::FixedBitLength<1>
            >,
            comms::field::EnumValue<
                field::common::FieldBase,
                CfgPm2_ExtintWake,
                comms::option::ValidNumValueRange<0, (int)CfgPm2_ExtintWake::NumOfValues - 1>,
                comms::option::FixedBitLength<1>
            >,
            comms::field::EnumValue<
                field::common::FieldBase,
                CfgPm2_ExtintBackup,
                comms::option::ValidNumValueRange<0, (int)CfgPm2_ExtintBackup::NumOfValues - 1>,
                comms::option::FixedBitLength<1>
            >,
            field::common::res1T<
                comms::option::FixedBitLength<1>
            >,
            comms::field::EnumValue<
                field::common::FieldBase,
                CfgPm2_LimitPeakCurr,
                comms::option::ValidNumValueRange<0, (int)CfgPm2_LimitPeakCurr::NumOfValues - 1>,
                comms::option::FixedBitLength<2>
            >,
            field::common::X1T<
                comms::option::FixedBitLength<6>,
                comms::option::BitmaskReservedBits<0xb8, 0>
            >,
            comms::field::EnumValue<
                field::common::FieldBase,
                CfgPm2_Mode,
                comms::option::ValidNumValueRange<0, (int)CfgPm2_Mode::NumOfValues - 1>,
                comms::option::FixedBitLength<2>
            >,
            field::common::res2T<
                comms::option::FixedBitLength<14>
            >
        >
    >;
using CfgPm2Field_updatePeriod = field::common::U4T<field::common::Scaling_ms2s>;
using CfgPm2Field_searchPeriod = field::common::U4T<field::common::Scaling_ms2s>;
using CfgPm2Field_gridOffset = field::common::U4T<field::common::Scaling_ms2s>;
using CfgPm2Field_onTime = field::common::U2;
using CfgPm2Field_minAcqTime = field::common::U2;
using CfgPm2Field_reserved4 = field::common::res2;
using CfgPm2Field_reserved5 = field::common::res2;
using CfgPm2Field_reserved6 = field::common::res4;
using CfgPm2Field_reserved7 = field::common::res4;
using CfgPm2Field_reserved8 = field::common::res1;
using CfgPm2Field_reserved9 = field::common::res1;
using CfgPm2Field_reserved10 = field::common::res2;
using CfgPm2Field_reserved11 = field::common::res4;

using CfgPm2Fields = std::tuple<
    CfgPm2Field_version,
    CfgPm2Field_reserved1,
    CfgPm2Field_reserved2,
    CfgPm2Field_reserved3,
    CfgPm2Field_flags,
    CfgPm2Field_updatePeriod,
    CfgPm2Field_searchPeriod,
    CfgPm2Field_gridOffset,
    CfgPm2Field_onTime,
    CfgPm2Field_minAcqTime,
    CfgPm2Field_reserved4,
    CfgPm2Field_reserved5,
    CfgPm2Field_reserved6,
    CfgPm2Field_reserved7,
    CfgPm2Field_reserved8,
    CfgPm2Field_reserved9,
    CfgPm2Field_reserved10,
    CfgPm2Field_reserved11
>;

template <typename TMsgBase = Message>
class CfgPm2 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PM2>,
        comms::option::FieldsImpl<CfgPm2Fields>,
        comms::option::DispatchImpl<CfgPm2<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PM2>,
        comms::option::FieldsImpl<CfgPm2Fields>,
        comms::option::DispatchImpl<CfgPm2<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_version,
        FieldIdx_reserved1,
        FieldIdx_reserved2,
        FieldIdx_reserved3,
        FieldIdx_flags,
        FieldIdx_updatePeriod,
        FieldIdx_searchPeriod,
        FieldIdx_gridOffset,
        FieldIdx_onTime,
        FieldIdx_minAcqTime,
        FieldIdx_reserved4,
        FieldIdx_reserved5,
        FieldIdx_reserved6,
        FieldIdx_reserved7,
        FieldIdx_reserved8,
        FieldIdx_reserved9,
        FieldIdx_reserved10,
        FieldIdx_reserved11,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    CfgPm2() = default;
    CfgPm2(const CfgPm2&) = default;
    CfgPm2(CfgPm2&& other) = default;
    virtual ~CfgPm2() = default;

    CfgPm2& operator=(const CfgPm2&) = default;
    CfgPm2& operator=(CfgPm2&&) = default;
};


}  // namespace message

}  // namespace ublox

