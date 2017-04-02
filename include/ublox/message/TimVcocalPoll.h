//
// Copyright 2017 (C). Alex Robenko. All rights reserved.
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
/// @brief Contains definition of TIM-VCOCAL (poll) message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the TIM-VCOCAL (poll) message fields.
/// @see TimVcocalPoll
struct TimVcocalPollFields
{
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<>;
};

/// @brief Definition of TIM-VCOCAL (poll) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref TimVcocalPollFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class TimVcocalPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_VCOCAL>,
        comms::option::FieldsImpl<TimVcocalPollFields::All>,
        comms::option::MsgType<TimVcocalPoll<TMsgBase> >
    >
{
public:

    /// @brief Default constructor
    TimVcocalPoll() = default;

    /// @brief Copy constructor
    TimVcocalPoll(const TimVcocalPoll&) = default;

    /// @brief Move constructor
    TimVcocalPoll(TimVcocalPoll&& other) = default;

    /// @brief Destructor
    ~TimVcocalPoll() = default;

    /// @brief Copy assignment
    TimVcocalPoll& operator=(const TimVcocalPoll&) = default;

    /// @brief Move assignment
    TimVcocalPoll& operator=(TimVcocalPoll&&) = default;
};


}  // namespace message

}  // namespace ublox

