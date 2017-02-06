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
/// @brief Contains definition of ACK-NAK message and its fields.

#pragma once

#include "comms/Message.h"
#include "ublox/Message.h"
#include "ublox/field/MsgId.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the ACK-NAK message fields.
/// @see AckNak
struct AckNakFields
{
    /// @brief Definition of "id" field (combining class ID and message ID).
    using id = ublox::field::MsgId;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<id>;
};

/// @brief Definition of ACK-NAK message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref AckNakFields for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AckNak : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_ACK_NAK>,
        comms::option::FieldsImpl<AckNakFields::All>,
        comms::option::MsgType<AckNak<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_ACK_NAK>,
        comms::option::FieldsImpl<AckNakFields::All>,
        comms::option::MsgType<AckNak<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b id for @ref AckNakFields::id field
    COMMS_MSG_FIELDS_ACCESS(id);

    /// @brief Default constructor
    AckNak() = default;

    /// @brief Copy constructor
    AckNak(const AckNak&) = default;

    /// @brief Move constructor
    AckNak(AckNak&& other) = default;

    /// @brief Destructor
    virtual ~AckNak() = default;

    /// @brief Copy assignment
    AckNak& operator=(const AckNak&) = default;

    /// @brief Move assignment
    AckNak& operator=(AckNak&&) = default;
};


}  // namespace message

}  // namespace ublox

