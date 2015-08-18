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

using CfgTpFields = std::tuple<
    ublox::field::cfg::interval,
    ublox::field::cfg::length,
    ublox::field::cfg::status,
    ublox::field::cfg::time_ref,
    ublox::field::common::res2,
    ublox::field::cfg::antenna_cable_delay,
    ublox::field::cfg::RF_group_delay,
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
        FieldIdx_Interval,
        FieldIdx_Length,
        FieldIdx_Status,
        FieldIdx_TimeRef,
        FieldIdx_Res,
        FieldIdx_AntannaCableDelay,
        FieldIdx_RfGroupDelay,
        FieldIdx_UserDelay,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
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

