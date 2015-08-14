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

#include "ublox/Message.h"
#include "ublox/field/MsgId.h"
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

using CfgMsgCurrentFields =
    std::tuple<
        ublox::field::MsgId,
        ublox::field::cfg::Rate
    >;


template <typename TMsgBase = Message>
class CfgMsgCurrent : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_MSG>,
        comms::option::FieldsImpl<CfgMsgCurrentFields>,
        comms::option::DispatchImpl<CfgMsgCurrent<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_MSG>,
        comms::option::FieldsImpl<CfgMsgCurrentFields>,
        comms::option::DispatchImpl<CfgMsgCurrent<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_Id,
        FieldIdx_Rate,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    CfgMsgCurrent() = default;
    CfgMsgCurrent(const CfgMsgCurrent&) = default;
    CfgMsgCurrent(CfgMsgCurrent&& other) = default;
    virtual ~CfgMsgCurrent() = default;

    CfgMsgCurrent& operator=(const CfgMsgCurrent&) = default;
    CfgMsgCurrent& operator=(CfgMsgCurrent&&) = default;
};


}  // namespace message

}  // namespace ublox

