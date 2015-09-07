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
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

enum class CfgTp_Status : std::int8_t
{
    Negative = -1,
    Off = 0,
    Positive = 1
};

enum class CfgTp_TimeRef : std::uint8_t
{
    Utc,
    Gps,
    Local,
    NumOfValues
};

enum
{
    CfgTpField_flags_syncMode,
    CfgTpField_flags_numOfValues
};

using CfgTpField_interval = field::common::U4T<field::common::Scaling_us2s>;
using CfgTpField_length = field::common::U4T<field::common::Scaling_us2s>;
using CfgTpField_status =
    comms::field::EnumValue<
        field::common::FieldBase,
        CfgTp_Status,
        comms::option::ValidNumValueRange<(int)CfgTp_Status::Negative, (int)CfgTp_Status::Positive>
    >;
using CfgTpField_timeRef =
    comms::field::EnumValue<
        field::common::FieldBase,
        CfgTp_TimeRef,
        comms::option::ValidNumValueRange<0, (int)CfgTp_TimeRef::NumOfValues - 1>
    >;
using CfgTpField_flags = field::common::X1T<comms::option::BitmaskReservedBits<0xfe, 0> >;
using CfgTpField_res = field::common::res1;
using CfgTpField_antennaCableDelay = field::common::I2T<field::common::Scaling_ns2s>;
using CfgTpField_rfGroupDelay = field::common::I2T<field::common::Scaling_ns2s>;
using CfgTpField_userDelay = field::common::I4T<field::common::Scaling_ns2s>;

using CfgTpFields = std::tuple<
    CfgTpField_interval,
    CfgTpField_length,
    CfgTpField_status,
    CfgTpField_timeRef,
    CfgTpField_flags,
    CfgTpField_res,
    CfgTpField_antennaCableDelay,
    CfgTpField_rfGroupDelay,
    ublox::field::cfg::user_delay
>;

template <typename TMsgBase = Message>
class CfgTp : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TP>,
        comms::option::FieldsImpl<CfgTpFields>,
        comms::option::DispatchImpl<CfgTp<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TP>,
        comms::option::FieldsImpl<CfgTpFields>,
        comms::option::DispatchImpl<CfgTp<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_interval,
        FieldIdx_length,
        FieldIdx_status,
        FieldIdx_timeRef,
        FieldIdx_flags,
        FieldIdx_res,
        FieldIdx_antannaCableDelay,
        FieldIdx_rfGroupDelay,
        FieldIdx_userDelay,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    CfgTp() = default;
    CfgTp(const CfgTp&) = default;
    CfgTp(CfgTp&& other) = default;
    virtual ~CfgTp() = default;

    CfgTp& operator=(const CfgTp&) = default;
    CfgTp& operator=(CfgTp&&) = default;
};


}  // namespace message

}  // namespace ublox

