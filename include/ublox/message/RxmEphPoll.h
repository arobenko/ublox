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

#include "ublox/field/rxm.h"

namespace ublox
{

namespace message
{

using RxmEphPollFields =
    std::tuple<
        comms::field::Optional<field::rxm::SVID>
    >;


template <typename TMsgBase = Message>
class RxmEphPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_EPH>,
        comms::option::FieldsImpl<RxmEphPollFields>,
        comms::option::DispatchImpl<RxmEphPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_EPH>,
        comms::option::FieldsImpl<RxmEphPollFields>,
        comms::option::DispatchImpl<RxmEphPoll<TMsgBase> >
    > Base;
public:

    enum FieldIdx
    {
        FieldIdx_Svid,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");


    RxmEphPoll() = default;
    RxmEphPoll(const RxmEphPoll&) = default;
    RxmEphPoll(RxmEphPoll&& other) = default;
    virtual ~RxmEphPoll() = default;

    RxmEphPoll& operator=(const RxmEphPoll&) = default;
    RxmEphPoll& operator=(RxmEphPoll&&) = default;
};


}  // namespace message

}  // namespace ublox





