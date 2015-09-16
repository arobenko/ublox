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

enum class CfgPm_ExtintSelect : std::uint8_t
{
    EXTINT0,
    EXTINT1,
    NumOfValues
};

enum class CfgPm_DisabledEnabled : std::uint8_t
{
    Disabled,
    Enabled,
    NumOfValues
};

using CfgPm_ExtintWake = CfgPm_DisabledEnabled;
using CfgPm_ExtintBackup = CfgPm_DisabledEnabled;
using CfgPm_LimitPeakCurr = CfgPm_DisabledEnabled;

enum
{
    CfgPmField_flags_reserved,
    CfgPmField_flags_internal,
    CfgPmField_flags_extintSelect,
    CfgPmField_flags_extintWake,
    CfgPmField_flags_extintBackup,
    CfgPmField_flags_reserved2,
    CfgPmField_flags_limitPeakCurr,
    CfgPmField_flags_flags,
    CfgPmField_flags_numOfValues,
};

enum
{
    CfgPmField_flags_flags_waitTimeFix,
    CfgPmField_flags_flags_updateRTC,
    CfgPmField_flags_flags_updateEPH,
    CfgPmField_flags_flags_numOfValues
};

using CfgPmField_version =
    field::common::U1T<
        comms::option::ValidNumValueRange<0, 0>
    >;
using CfgPmField_reserved1 = field::common::res1;
using CfgPmField_reserved2 = field::common::res1;
using CfgPmField_reserved3 = field::common::res1;
using CfgPmField_flags =
    comms::field::Bitfield<
        field::common::FieldBase,
        std::tuple<
            field::common::res1T<
                comms::option::FixedBitLength<2>
            >,
            field::common::U1T<
                comms::option::FixedBitLength<2>,
                comms::option::DefaultNumValue<1>,
                comms::option::ValidNumValueRange<1, 1>
            >,
            comms::field::EnumValue<
                field::common::FieldBase,
                CfgPm_ExtintSelect,
                comms::option::ValidNumValueRange<0, (int)CfgPm_ExtintSelect::NumOfValues - 1>,
                comms::option::FixedBitLength<1>
            >,
            comms::field::EnumValue<
                field::common::FieldBase,
                CfgPm_ExtintWake,
                comms::option::ValidNumValueRange<0, (int)CfgPm_ExtintWake::NumOfValues - 1>,
                comms::option::FixedBitLength<1>
            >,
            comms::field::EnumValue<
                field::common::FieldBase,
                CfgPm_ExtintBackup,
                comms::option::ValidNumValueRange<0, (int)CfgPm_ExtintBackup::NumOfValues - 1>,
                comms::option::FixedBitLength<1>
            >,
            field::common::res1T<
                comms::option::FixedBitLength<1>
            >,
            comms::field::EnumValue<
                field::common::FieldBase,
                CfgPm_LimitPeakCurr,
                comms::option::ValidNumValueRange<0, (int)CfgPm_LimitPeakCurr::NumOfValues - 1>,
                comms::option::FixedBitLength<2>
            >,
            field::common::X4T<
                comms::option::FixedBitLength<22>,
                comms::option::BitmaskReservedBits<0xfffffff8, 0>
            >
        >
    >;
using CfgPmField_updatePeriod = field::common::U4T<field::common::Scaling_ms2s>;
using CfgPmField_searchPeriod = field::common::U4T<field::common::Scaling_ms2s>;
using CfgPmField_gridOffset = field::common::U4T<field::common::Scaling_ms2s>;
using CfgPmField_onTime = field::common::U2;
using CfgPmField_minAcqTime = field::common::U2;

using CfgPmFields = std::tuple<
    CfgPmField_version,
    CfgPmField_reserved1,
    CfgPmField_reserved2,
    CfgPmField_reserved3,
    CfgPmField_flags,
    CfgPmField_updatePeriod,
    CfgPmField_searchPeriod,
    CfgPmField_gridOffset,
    CfgPmField_onTime,
    CfgPmField_minAcqTime
>;

template <typename TMsgBase = Message>
class CfgPm : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PM>,
        comms::option::FieldsImpl<CfgPmFields>,
        comms::option::DispatchImpl<CfgPm<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PM>,
        comms::option::FieldsImpl<CfgPmFields>,
        comms::option::DispatchImpl<CfgPm<TMsgBase> >
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
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    CfgPm() = default;
    CfgPm(const CfgPm&) = default;
    CfgPm(CfgPm&& other) = default;
    virtual ~CfgPm() = default;

    CfgPm& operator=(const CfgPm&) = default;
    CfgPm& operator=(CfgPm&&) = default;
};


}  // namespace message

}  // namespace ublox

