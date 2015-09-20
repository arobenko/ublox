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

namespace ublox
{

namespace message
{

using MonMsgppPollFields = std::tuple<>;


template <typename TMsgBase = Message>
class MonMsgppPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_MSGPP>,
        comms::option::FieldsImpl<MonMsgppPollFields>,
        comms::option::DispatchImpl<MonMsgppPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_MSGPP>,
        comms::option::FieldsImpl<MonMsgppPollFields>,
        comms::option::DispatchImpl<MonMsgppPoll<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    MonMsgppPoll() = default;
    MonMsgppPoll(const MonMsgppPoll&) = default;
    MonMsgppPoll(MonMsgppPoll&& other) = default;
    virtual ~MonMsgppPoll() = default;

    MonMsgppPoll& operator=(const MonMsgppPoll&) = default;
    MonMsgppPoll& operator=(MonMsgppPoll&&) = default;
};


}  // namespace message

}  // namespace ublox

