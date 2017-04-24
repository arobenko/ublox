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
/// @brief Contains definition of ACK-ACK message and its fields.

#pragma once

#include "comms/Message.h"
#include "ublox/Message.h"
#include "ublox/field/MsgId.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the ACK-ACK message fields.
/// @see AckAck
struct AckAckFields
{
    /// @brief Definition of "id" field (combining class ID and message ID).
    using id = ublox::field::MsgId;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<id>;
};

/// @brief Definition of ACK-ACK message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref AckAckFields for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AckAck : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_ACK_ACK>,
        comms::option::FieldsImpl<AckAckFields::All>,
        comms::option::MsgType<AckAck<TMsgBase> >
    >
{
public:
    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b id for @ref AckAckFields::id field
    COMMS_MSG_FIELDS_ACCESS(id);

    /// @brief Default constructor
    AckAck() = default;

    /// @brief Copy constructor
    AckAck(const AckAck&) = default;

    /// @brief Move constructor
    AckAck(AckAck&& other) = default;

    /// @brief Destructor
    ~AckAck() = default;

    /// @brief Copy assignment
    AckAck& operator=(const AckAck&) = default;

    /// @brief Move assignment
    AckAck& operator=(AckAck&&) = default;
};


}  // namespace message

}  // namespace ublox

