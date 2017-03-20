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
/// @brief Contains definition of LOG-RETRIEVEPOSEXTRA message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/log.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the LOG-RETRIEVEPOSEXTRA message fields.
/// @see LogRetrieveposextra
struct LogRetrieveposextraFields
{
    /// @brief Definition of "entryIndex" field.
    using entryIndex  = field::common::U4;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "year" field.
    using year = field::log::year;

    /// @brief Definition of "month" field.
    using month = field::log::month;

    /// @brief Definition of "day" field.
    using day = field::log::day;

    /// @brief Definition of "hour" field.
    using hour = field::log::hour;

    /// @brief Definition of "minute" field.
    using minute = field::log::minute;

    /// @brief Definition of "second" field.
    using second = field::log::second;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res3;

    /// @brief Definition of "distance" field.
    using distance  = field::common::U4;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res4;

    /// @brief Definition of "reserved4" field.
    using reserved4 = field::common::res4;

    /// @brief Definition of "reserved5" field.
    using reserved5 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        entryIndex,
        version,
        reserved1,
        year,
        month,
        day,
        hour,
        minute,
        second,
        reserved2,
        distance,
        reserved3,
        reserved4,
        reserved5
    >;
};

/// @brief Definition of LOG-RETRIEVEPOSEXTRA message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref LogRetrieveposextraFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class LogRetrieveposextra : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_RETRIEVEPOSEXTRA>,
        comms::option::FieldsImpl<LogRetrieveposextraFields::All>,
        comms::option::MsgType<LogRetrieveposextra<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b entryIndex for @ref LogRetrieveposextraFields::entryIndex field
    ///     @li @b version for @ref LogRetrieveposextraFields::version field
    ///     @li @b reserved1 for @ref LogRetrieveposextraFields::reserved1 field
    ///     @li @b year for @ref LogRetrieveposextraFields::year field
    ///     @li @b month for @ref LogRetrieveposextraFields::month field
    ///     @li @b day for @ref LogRetrieveposextraFields::day field
    ///     @li @b hour for @ref LogRetrieveposextraFields::hour field
    ///     @li @b minute for @ref LogRetrieveposextraFields::minute field
    ///     @li @b second for @ref LogRetrieveposextraFields::second field
    ///     @li @b reserved2 for @ref LogRetrieveposextraFields::reserved2 field
    ///     @li @b distance for @ref LogRetrieveposextraFields::distance field
    ///     @li @b reserved3 for @ref LogRetrieveposextraFields::reserved3 field
    ///     @li @b reserved4 for @ref LogRetrieveposextraFields::reserved4 field
    ///     @li @b reserved5 for @ref LogRetrieveposextraFields::reserved5 field
    COMMS_MSG_FIELDS_ACCESS(
        entryIndex,
        version,
        reserved1,
        year,
        month,
        day,
        hour,
        minute,
        second,
        reserved2,
        distance,
        reserved3,
        reserved4,
        reserved5
    );

    /// @brief Default constructor
    LogRetrieveposextra() = default;

    /// @brief Copy constructor
    LogRetrieveposextra(const LogRetrieveposextra&) = default;

    /// @brief Move constructor
    LogRetrieveposextra(LogRetrieveposextra&& other) = default;

    /// @brief Destructor
    ~LogRetrieveposextra() = default;

    /// @brief Copy assignment
    LogRetrieveposextra& operator=(const LogRetrieveposextra&) = default;

    /// @brief Move assignment
    LogRetrieveposextra& operator=(LogRetrieveposextra&&) = default;
};

}  // namespace message

}  // namespace ublox

