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

#include <iterator>

#include "comms/Message.h"
#include "ublox/Message.h"

#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

using CfgPrtPollFields = std::tuple<
    field::cfg::PortID
>;

template <typename TMsgBase = Message>
class CfgPrtPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtPollFields>,
        comms::option::DispatchImpl<CfgPrtPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtPollFields>,
        comms::option::DispatchImpl<CfgPrtPoll<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_PortId,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    CfgPrtPoll() = default;
    CfgPrtPoll(const CfgPrtPoll&) = default;
    CfgPrtPoll(CfgPrtPoll&& other) = default;
    virtual ~CfgPrtPoll() = default;

    CfgPrtPoll& operator=(const CfgPrtPoll&) = default;
    CfgPrtPoll& operator=(CfgPrtPoll&&) = default;

};


}  // namespace message

}  // namespace ublox





