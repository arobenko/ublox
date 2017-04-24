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
/// @brief Contains definition of ESF-STATUS (@b poll) message and its fields.

#pragma once

#include "ublox/Message.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the ESF-STATUS (@b poll) message fields.
/// @see EsfStatusPoll
struct EsfStatusPollFields
{
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<>;
};

/// @brief Definition of ESF-STATUS (@b poll) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref EsfStatusPollFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class EsfStatusPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_ESF_STATUS>,
        comms::option::FieldsImpl<EsfStatusPollFields::All>,
        comms::option::MsgType<EsfStatusPoll<TMsgBase> >
    >
{
public:

    /// @brief Default constructor
    EsfStatusPoll() = default;

    /// @brief Copy constructor
    EsfStatusPoll(const EsfStatusPoll&) = default;

    /// @brief Move constructor
    EsfStatusPoll(EsfStatusPoll&& other) = default;

    /// @brief Destructor
    ~EsfStatusPoll() = default;

    /// @brief Copy assignment
    EsfStatusPoll& operator=(const EsfStatusPoll&) = default;

    /// @brief Move assignment
    EsfStatusPoll& operator=(EsfStatusPoll&&) = default;
};


}  // namespace message

}  // namespace ublox





