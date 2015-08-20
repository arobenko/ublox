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

enum class CfgTmIntId : std::uint32_t
{
    EXTINT2 = 29,
    EXTINT1,
    EXTINT0
};

using CfgTmIntIdField =
    comms::field::EnumValue<
        field::common::FieldBase,
        CfgTmIntId,
        comms::option::ValidNumValueRange<(int)CfgTmIntId::EXTINT2, (int)CfgTmIntId::EXTINT0>
    >;

using CfgTmRateField = field::common::U4;

enum class CfgTmEdge : std::uint8_t
{
    Rising,
    Falling,
    NumOfValues
};

enum class CfgTmTimebase : std::uint8_t
{
    GPS,
    UTC,
    NumOfValues
};

enum CfgTmFlagsFieldMemberIdx
{
    CfgTmFlagsFieldMemberIdx_Enabled,
    CfgTmFlagsFieldMemberIdx_Edge,
    CfgTmFlagsFieldMemberIdx_Timebase,
    CfgTmFlagsFieldMemberIdx_Reserved,
    CfgTmFlagsFieldMemberIdx_NumOfValues
};

using CfgTmFlagsField =
    comms::field::Bitfield<
        field::common::FieldBase,
        std::tuple<
            comms::field::BitmaskValue<
                field::common::FieldBase,
                comms::option::FixedBitLength<1U>
            >,
            comms::field::EnumValue<
                field::common::FieldBase,
                CfgTmEdge,
                comms::option::FixedBitLength<1U>,
                comms::option::ValidNumValueRange<0, (int)CfgTmEdge::NumOfValues - 1>
            >,
            comms::field::EnumValue<
                field::common::FieldBase,
                CfgTmTimebase,
                comms::option::FixedBitLength<1U>,
                comms::option::ValidNumValueRange<0, (int)CfgTmTimebase::NumOfValues - 1>
            >,
            comms::field::IntValue<
                field::common::FieldBase,
                unsigned,
                comms::option::FixedBitLength<29>
            >
        >
    >;

using CfgTmFields = std::tuple<
    CfgTmIntIdField,
    CfgTmRateField,
    CfgTmFlagsField
>;

template <typename TMsgBase = Message>
class CfgTm : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TM>,
        comms::option::FieldsImpl<CfgTmFields>,
        comms::option::DispatchImpl<CfgTm<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TM>,
        comms::option::FieldsImpl<CfgTmFields>,
        comms::option::DispatchImpl<CfgTm<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_IntId,
        FieldIdx_Rage,
        FieldIdx_Flags,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    CfgTm() = default;
    CfgTm(const CfgTm&) = default;
    CfgTm(CfgTm&& other) = default;
    virtual ~CfgTm() = default;

    CfgTm& operator=(const CfgTm&) = default;
    CfgTm& operator=(CfgTm&&) = default;
};


}  // namespace message

}  // namespace ublox

