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

using NavClockPollFields = std::tuple<>;

template <typename TMsgBase = Message>
class NavClockPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_CLOCK>,
        comms::option::FieldsImpl<NavClockPollFields>,
        comms::option::DispatchImpl<NavClockPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_CLOCK>,
        comms::option::FieldsImpl<NavClockPollFields>,
        comms::option::DispatchImpl<NavClockPoll<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == 0U,
        "Number of fields is incorrect");

    /// @brief Default constructor
    NavClockPoll() = default;

    /// @brief Copy constructor
    NavClockPoll(const NavClockPoll&) = default;

    /// @brief Move constructor
    NavClockPoll(NavClockPoll&& other) = default;

    /// @brief Destructor
    virtual ~NavClockPoll() = default;

    /// @brief Copy assignment
    NavClockPoll& operator=(const NavClockPoll&) = default;

    /// @brief Move assignment
    NavClockPoll& operator=(NavClockPoll&&) = default;
};


}  // namespace message

}  // namespace ublox





