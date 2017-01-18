//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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
/// @brief Contains definition of MON-RXR message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MON-RXR message fields.
/// @see MonRxr
struct MonRxrFields
{
    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xfe, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(awake);
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        flags
    >;
};

/// @brief Definition of MON-RXR message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MonRxrFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MonRxr : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_RXR>,
        comms::option::FieldsImpl<MonRxrFields::All>,
        comms::option::MsgType<MonRxr<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_RXR>,
        comms::option::FieldsImpl<MonRxrFields::All>,
        comms::option::MsgType<MonRxr<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b flags for @ref MonRxrFields::flags field
    COMMS_MSG_FIELDS_ACCESS(Base, flags);

    /// @brief Default constructor
    MonRxr() = default;

    /// @brief Copy constructor
    MonRxr(const MonRxr&) = default;

    /// @brief Move constructor
    MonRxr(MonRxr&& other) = default;

    /// @brief Destructor
    virtual ~MonRxr() = default;

    /// @brief Copy assignment
    MonRxr& operator=(const MonRxr&) = default;

    /// @brief Move assignment
    MonRxr& operator=(MonRxr&&) = default;
};


}  // namespace message

}  // namespace ublox

