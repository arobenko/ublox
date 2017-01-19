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
/// @brief Contains definition of LOG-STRING message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{
/// @brief Accumulates details of all the LOG-STRING message fields.
/// @see LogString
struct LogStringFields
{
    /// @brief Definition of "bytes" field.
    using bytes = field::common::String;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        bytes
    >;
};

/// @brief Definition of LOG-STRING message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref LogStringFields and for definition of the fields this message contains.
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class LogString : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_STRING>,
        comms::option::FieldsImpl<LogStringFields::All>,
        comms::option::MsgType<LogString<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_STRING>,
        comms::option::FieldsImpl<LogStringFields::All>,
        comms::option::MsgType<LogString<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b bytes for @ref LogStringFields::bytes field
    COMMS_MSG_FIELDS_ACCESS(Base, bytes);

    /// @brief Default constructor
    LogString() = default;

    /// @brief Copy constructor
    LogString(const LogString&) = default;

    /// @brief Move constructor
    LogString(LogString&& other) = default;

    /// @brief Destructor
    virtual ~LogString() = default;

    /// @brief Copy assignment
    LogString& operator=(const LogString&) = default;

    /// @brief Move assignment
    LogString& operator=(LogString&&) = default;
};


}  // namespace message

}  // namespace ublox

