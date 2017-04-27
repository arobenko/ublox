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
/// @brief Contains definition of RXM-RAWX (@b poll) message and its fields.

#pragma once

#include "ublox/Message.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the RXM-RAWX (@b poll) message fields.
/// @see RxmRawxPoll
struct RxmRawxPollFields
{
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<>;
};

/// @brief Definition of RXM-RAWX (@b poll) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref RxmRawxPollFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class RxmRawxPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_RAWX>,
        comms::option::FieldsImpl<RxmRawxPollFields::All>,
        comms::option::MsgType<RxmRawxPoll<TMsgBase> >
    >
{
public:

    /// @brief Default constructor
    RxmRawxPoll() = default;

    /// @brief Copy constructor
    RxmRawxPoll(const RxmRawxPoll&) = default;

    /// @brief Move constructor
    RxmRawxPoll(RxmRawxPoll&& other) = default;

    /// @brief Destructor
    ~RxmRawxPoll() = default;

    /// @brief Copy assignment
    RxmRawxPoll& operator=(const RxmRawxPoll&) = default;

    /// @brief Move assignment
    RxmRawxPoll& operator=(RxmRawxPoll&&) = default;
};


}  // namespace message

}  // namespace ublox





