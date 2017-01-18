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
/// @brief Contains definition of LOG-CREATE message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the LOG-CREATE message fields.
/// @see LogCreate
struct LogCreateFields
{
    /// @brief Value enumeration for @ref logSize field
    enum class LogSize : std::uint8_t
    {
        Max, ///< maximum
        Min, ///< minimum
        UserDefined, ///< user defined
        NumOfValues ///< number of values
    };

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "logCfg" field.
    struct logCfg : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xfe, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(circular);
    };

    /// @brief Definition of "reserved" field.
    using reserved = field::common::res1;

    /// @brief Definition of "logSize" field.
    using logSize  =
        field::common::EnumT<
            LogSize,
            comms::option::ValidNumValueRange<0, (int)LogSize::NumOfValues - 1>
        >;

    /// @brief Definition of "userDefinedSize" field.
    using userDefinedSize = field::common::U4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        logCfg,
        reserved,
        logSize,
        userDefinedSize
    >;
};

/// @brief Definition of LOG-CREATE message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref LogCreateFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class LogCreate : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_CREATE>,
        comms::option::FieldsImpl<LogCreateFields::All>,
        comms::option::MsgType<LogCreate<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_CREATE>,
        comms::option::FieldsImpl<LogCreateFields::All>,
        comms::option::MsgType<LogCreate<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref LogCreateFields::version field
    ///     @li @b logCfg for @ref LogCreateFields::logCfg field
    ///     @li @b reserved for @ref LogCreateFields::reserved field
    ///     @li @b logSize for @ref LogCreateFields::logSize field
    ///     @li @b userDefinedSize for @ref LogCreateFields::userDefinedSize field
    COMMS_MSG_FIELDS_ACCESS(Base, version, logCfg, reserved, logSize, userDefinedSize);

    /// @brief Default constructor
    LogCreate() = default;

    /// @brief Copy constructor
    LogCreate(const LogCreate&) = default;

    /// @brief Move constructor
    LogCreate(LogCreate&& other) = default;

    /// @brief Destructor
    virtual ~LogCreate() = default;

    /// @brief Copy assignment
    LogCreate& operator=(const LogCreate&) = default;

    /// @brief Move assignment
    LogCreate& operator=(LogCreate&&) = default;
};


}  // namespace message

}  // namespace ublox

