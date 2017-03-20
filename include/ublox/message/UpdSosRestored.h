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
/// @brief Contains definition of UPD-SOS (@b restored) message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the UPD-SOS (@b restored) message fields.
/// @see UpdSosRestored
struct UpdSosRestoredFields
{
    /// @brief Definition of "cmd" field.
    using cmd =
        field::common::U1T<
        comms::option::ValidNumValueRange<3, 3>,
        comms::option::DefaultNumValue<3>,
        comms::option::FailOnInvalid
    >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res3;

    /// @brief Enumeration value for @ref response field
    enum class Response : std::uint8_t
    {
        Unknown, ///< Unknown
        Failed, ///< Failed restoring from backup file
        Restored, ///< Restored from backup file
        NoBackup, ///< Not restored (no backup)
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "response" field.
    using response =
        field::common::EnumT<
            Response,
            comms::option::ValidNumValueRange<0, (int)Response::NumOfValues - 1>
        >;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res3;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        cmd,
        reserved1,
        response,
        reserved2
    >;
};

/// @brief Definition of UPD-SOS (@b restored) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref UpdSosRestoredFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class UpdSosRestored : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_UPD_SOS>,
        comms::option::FieldsImpl<UpdSosRestoredFields::All>,
        comms::option::MsgType<UpdSosRestored<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b cmd for @ref UpdSosRestoredFields::cmd field
    ///     @li @b reserved1 for @ref UpdSosRestoredFields::reserved1 field
    COMMS_MSG_FIELDS_ACCESS(cmd, reserved1, response, reserved2);

    /// @brief Default constructor
    UpdSosRestored() = default;

    /// @brief Copy constructor
    UpdSosRestored(const UpdSosRestored&) = default;

    /// @brief Move constructor
    UpdSosRestored(UpdSosRestored&& other) = default;

    /// @brief Destructor
    ~UpdSosRestored() = default;

    /// @brief Copy assignment
    UpdSosRestored& operator=(const UpdSosRestored&) = default;

    /// @brief Move assignment
    UpdSosRestored& operator=(UpdSosRestored&&) = default;
};


}  // namespace message

}  // namespace ublox

