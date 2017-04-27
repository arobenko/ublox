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
/// @brief Contains definition of MON-HW (@b poll) message and its fields.

#pragma once

#include "ublox/Message.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MON-HW (@b poll) message fields.
/// @see MonHwPoll
struct MonHwPollFields
{
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<>;
};

/// @brief Definition of MON-HW (@b poll) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MonHwPollFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MonHwPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_HW>,
        comms::option::FieldsImpl<MonHwPollFields::All>,
        comms::option::MsgType<MonHwPoll<TMsgBase> >
    >
{
public:

    /// @brief Default constructor
    MonHwPoll() = default;

    /// @brief Copy constructor
    MonHwPoll(const MonHwPoll&) = default;

    /// @brief Move constructor
    MonHwPoll(MonHwPoll&& other) = default;

    /// @brief Destructor
    ~MonHwPoll() = default;

    /// @brief Copy assignment
    MonHwPoll& operator=(const MonHwPoll&) = default;

    /// @brief Move assignment
    MonHwPoll& operator=(MonHwPoll&&) = default;
};


}  // namespace message

}  // namespace ublox

