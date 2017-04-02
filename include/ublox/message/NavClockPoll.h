//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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

/// @file
/// @brief Contains definition of NAV-CLOCK (@b poll) message and its fields.

#pragma once

#include "ublox/Message.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-CLOCK (@b poll) message fields.
/// @see NavClockPoll
struct NavClockPollFields
{
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<>;
};

/// @brief Definition of NAV-CLOCK (@b poll) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavClockPollFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavClockPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_CLOCK>,
        comms::option::FieldsImpl<NavClockPollFields::All>,
        comms::option::MsgType<NavClockPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_CLOCK>,
        comms::option::FieldsImpl<NavClockPollFields::All>,
        comms::option::MsgType<NavClockPoll<TMsgBase> >
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
    ~NavClockPoll() = default;

    /// @brief Copy assignment
    NavClockPoll& operator=(const NavClockPoll&) = default;

    /// @brief Move assignment
    NavClockPoll& operator=(NavClockPoll&&) = default;
};


}  // namespace message

}  // namespace ublox





