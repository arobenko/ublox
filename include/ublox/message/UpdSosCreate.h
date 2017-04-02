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
/// @brief Contains definition of UPD-SOS (<b>create command</b>) message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the UPD-SOS (<b>create command</b>) message fields.
/// @see UpdSosCreate
struct UpdSosCreateFields
{
    /// @brief Definition of "cmd" field.
    using cmd =
        field::common::U1T<
        comms::option::ValidNumValueRange<0, 0>,
        comms::option::FailOnInvalid<>
    >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res3;


    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        cmd,
        reserved1
    >;
};

/// @brief Definition of UPD-SOS (<b>create command</b>) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref UpdSosCreateFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class UpdSosCreate : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_UPD_SOS>,
        comms::option::FieldsImpl<UpdSosCreateFields::All>,
        comms::option::MsgType<UpdSosCreate<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b cmd for @ref UpdSosCreateFields::cmd field
    ///     @li @b reserved1 for @ref UpdSosCreateFields::reserved1 field
    COMMS_MSG_FIELDS_ACCESS(cmd, reserved1);

    /// @brief Default constructor
    UpdSosCreate() = default;

    /// @brief Copy constructor
    UpdSosCreate(const UpdSosCreate&) = default;

    /// @brief Move constructor
    UpdSosCreate(UpdSosCreate&& other) = default;

    /// @brief Destructor
    ~UpdSosCreate() = default;

    /// @brief Copy assignment
    UpdSosCreate& operator=(const UpdSosCreate&) = default;

    /// @brief Move assignment
    UpdSosCreate& operator=(UpdSosCreate&&) = default;
};


}  // namespace message

}  // namespace ublox

