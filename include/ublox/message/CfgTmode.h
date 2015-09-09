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

enum class CfgTmode_TimeMode : std::uint32_t
{
    Disabled,
    SurveyIn,
    FixedMode,
    NumOfValues
};

using CfgTmodeField_timeMode =
    comms::field::EnumValue<
        field::common::FieldBase,
        CfgTmode_TimeMode,
        comms::option::ValidNumValueRange<0, (int)CfgTmode_TimeMode::NumOfValues - 1>
    >;
using CfgTmodeField_fixedPosX = field::common::I4T<field::common::Scaling_cm2m>;
using CfgTmodeField_fixedPosY = CfgTmodeField_fixedPosX;
using CfgTmodeField_fixedPosZ = CfgTmodeField_fixedPosX;
using CfgTmodeField_fixedPosVar =
    field::common::U4T<
        comms::option::ScalingRatio<1, 1000000L>
    >;
using CfgTmodeField_svinMinDur = field::common::U4;
using CfgTmodeField_svinVarLimit =
    field::common::U4T<
        comms::option::ScalingRatio<1, 1000000L>
    >;


using CfgTmodeFields = std::tuple<
    CfgTmodeField_timeMode,
    CfgTmodeField_fixedPosX,
    CfgTmodeField_fixedPosY,
    CfgTmodeField_fixedPosZ,
    CfgTmodeField_fixedPosVar,
    CfgTmodeField_svinMinDur,
    CfgTmodeField_svinVarLimit
>;

template <typename TMsgBase = Message>
class CfgTmode : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TMODE>,
        comms::option::FieldsImpl<CfgTmodeFields>,
        comms::option::DispatchImpl<CfgTmode<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TMODE>,
        comms::option::FieldsImpl<CfgTmodeFields>,
        comms::option::DispatchImpl<CfgTmode<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_timeMode,
        FieldIdx_fixedPosX,
        FieldIdx_fixedPosY,
        FieldIdx_fixedPosZ,
        FieldIdx_fixedPosVar,
        FieldIdx_svinMinDur,
        FieldIdx_svinVarLimit,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    CfgTmode() = default;
    CfgTmode(const CfgTmode&) = default;
    CfgTmode(CfgTmode&& other) = default;
    virtual ~CfgTmode() = default;

    CfgTmode& operator=(const CfgTmode&) = default;
    CfgTmode& operator=(CfgTmode&&) = default;
};


}  // namespace message

}  // namespace ublox

