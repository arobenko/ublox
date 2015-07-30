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

using RxmAlmPollFields =
    std::tuple<
        comms::field::Optional<field::rxm::SVID>
    >;


template <typename TMsgBase = Message>
class RxmAlmPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_ALM>,
        comms::option::FieldsImpl<RxmAlmPollFields>,
        comms::option::DispatchImpl<RxmAlmPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_ALM>,
        comms::option::FieldsImpl<RxmAlmPollFields>,
        comms::option::DispatchImpl<RxmAlmPoll<TMsgBase> >
    > Base;
public:

    enum FieldIdx
    {
        FieldIdx_Svid,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");


    RxmAlmPoll() = default;
    RxmAlmPoll(const RxmAlmPoll&) = default;
    RxmAlmPoll(RxmAlmPoll&& other) = default;
    virtual ~RxmAlmPoll() = default;

    RxmAlmPoll& operator=(const RxmAlmPoll&) = default;
    RxmAlmPoll& operator=(RxmAlmPoll&&) = default;
};


}  // namespace message

}  // namespace ublox





