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
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

using TimVrfyPollFields = std::tuple<>;

template <typename TMsgBase = Message>
class TimVrfyPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_VRFY>,
        comms::option::FieldsImpl<TimVrfyPollFields>,
        comms::option::DispatchImpl<TimVrfyPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_VRFY>,
        comms::option::FieldsImpl<TimVrfyPollFields>,
        comms::option::DispatchImpl<TimVrfyPoll<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    TimVrfyPoll() = default;
    TimVrfyPoll(const TimVrfyPoll&) = default;
    TimVrfyPoll(TimVrfyPoll&& other) = default;
    virtual ~TimVrfyPoll() = default;

    TimVrfyPoll& operator=(const TimVrfyPoll&) = default;
    TimVrfyPoll& operator=(TimVrfyPoll&&) = default;
};


}  // namespace message

}  // namespace ublox

