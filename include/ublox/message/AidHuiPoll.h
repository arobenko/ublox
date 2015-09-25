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

using AidHuiPollFields = std::tuple<>;


template <typename TMsgBase = Message>
class AidHuiPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_HUI>,
        comms::option::FieldsImpl<AidHuiPollFields>,
        comms::option::DispatchImpl<AidHuiPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_HUI>,
        comms::option::FieldsImpl<AidHuiPollFields>,
        comms::option::DispatchImpl<AidHuiPoll<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    AidHuiPoll() = default;
    AidHuiPoll(const AidHuiPoll&) = default;
    AidHuiPoll(AidHuiPoll&& other) = default;
    virtual ~AidHuiPoll() = default;

    AidHuiPoll& operator=(const AidHuiPoll&) = default;
    AidHuiPoll& operator=(AidHuiPoll&&) = default;
};


}  // namespace message

}  // namespace ublox

