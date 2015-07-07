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

#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

using NavStatusPollFields = std::tuple<>;


template <typename TMsgBase = Message>
class NavStatusPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_STATUS>,
        comms::option::FieldsImpl<NavStatusPollFields>,
        comms::option::DispatchImpl<NavStatusPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_STATUS>,
        comms::option::FieldsImpl<NavStatusPollFields>,
        comms::option::DispatchImpl<NavStatusPoll<TMsgBase> >
    > Base;
public:

    static_assert(std::tuple_size<typename Base::AllFields>::value == 0U,
        "Number of fields is incorrect");

    NavStatusPoll() = default;
    NavStatusPoll(const NavStatusPoll&) = default;
    NavStatusPoll(NavStatusPoll&& other)
    {
    }
    virtual ~NavStatusPoll() = default;

    NavStatusPoll& operator=(const NavStatusPoll&) = default;
    NavStatusPoll& operator=(NavStatusPoll&&) = default;
};


}  // namespace message

}  // namespace ublox





