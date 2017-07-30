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
/// @brief Contains definition of LOG-INFO message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/log.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the LOG-INFO message fields.
/// @see LogInfo
struct LogInfoFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::DefaultNumValue<1>,
            comms::option::ValidNumValueRange<1, 1>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res3;

    /// @brief Definition of "filestoreCapacity" field.
    using filestoreCapacity  = field::common::U4;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res4;

    /// @brief Definition of "currentMaxLogSize" field.
    using currentMaxLogSize = field::common::U4;

    /// @brief Definition of "currentLogSize" field.
    using currentLogSize = field::common::U4;

    /// @brief Definition of "entryCount" field.
    using entryCount = field::common::U4;

    /// @brief Definition of "oldestYear" field.
    using oldestYear = field::log::year;

    /// @brief Definition of "oldestMonth" field.
    using oldestMonth = field::log::month;

    /// @brief Definition of "oldestDay" field.
    using oldestDay = field::log::day;

    /// @brief Definition of "oldestHour" field.
    using oldestHour = field::log::hour;

    /// @brief Definition of "oldestMinute" field.
    using oldestMinute = field::log::minute;

    /// @brief Definition of "oldestSecond" field.
    using oldestSecond = field::log::second;

    /// @brief Definition of "reserved4" field.
    using reserved4  = field::common::res1;

    /// @brief Definition of "newestYear" field.
    using newestYear = field::log::year;

    /// @brief Definition of "newestMonth" field.
    using newestMonth = field::log::month;

    /// @brief Definition of "newestDay" field.
    using newestDay = field::log::day;

    /// @brief Definition of "newestHour" field.
    using newestHour = field::log::hour;

    /// @brief Definition of "newestMinute" field.
    using newestMinute = field::log::minute;

    /// @brief Definition of "newestSecond" field.
    using newestSecond = field::log::second;

    /// @brief Definition of "reserved5" field.
    using reserved5  = field::common::res1;

    /// @brief Definition of "status" field.
    struct status : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xc7, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(recording=3, inactive, circular);

        /// @brief Provide convenience access functions for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_ACCESS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_ACCESS(recording, inactive, circular);
    };

    /// @brief Definition of "reserved6" field.
    using reserved6  = field::common::res3;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        reserved1,
        filestoreCapacity,
        reserved2,
        reserved3,
        currentMaxLogSize,
        currentLogSize,
        entryCount,
        oldestYear,
        oldestMonth,
        oldestDay,
        oldestHour,
        oldestMinute,
        oldestSecond,
        reserved4,
        newestYear,
        newestMonth,
        newestDay,
        newestHour,
        newestMinute,
        newestSecond,
        reserved5,
        status,
        reserved6
    >;
};

/// @brief Definition of LOG-INFO message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref LogInfoFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class LogInfo : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_INFO>,
        comms::option::FieldsImpl<LogInfoFields::All>,
        comms::option::MsgType<LogInfo<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref LogInfoFields::version field
    ///     @li @b reserved1 for @ref LogInfoFields::reserved1 field
    ///     @li @b filestoreCapacity for @ref LogInfoFields::filestoreCapacity field
    ///     @li @b reserved2 for @ref LogInfoFields::reserved2 field
    ///     @li @b reserved3 for @ref LogInfoFields::reserved3 field
    ///     @li @b currentMaxLogSize for @ref LogInfoFields::currentMaxLogSize field
    ///     @li @b currentLogSize for @ref LogInfoFields::currentLogSize field
    ///     @li @b entryCount for @ref LogInfoFields::entryCount field
    ///     @li @b oldestYear for @ref LogInfoFields::oldestYear field
    ///     @li @b oldestMonth for @ref LogInfoFields::oldestMonth field
    ///     @li @b oldestDay for @ref LogInfoFields::oldestDay field
    ///     @li @b oldestHour for @ref LogInfoFields::oldestHour field
    ///     @li @b oldestMinute for @ref LogInfoFields::oldestMinute field
    ///     @li @b oldestSecond for @ref LogInfoFields::oldestSecond field
    ///     @li @b reserved4 for @ref LogInfoFields::reserved4 field
    ///     @li @b newestYear for @ref LogInfoFields::newestYear field
    ///     @li @b newestMonth for @ref LogInfoFields::newestMonth field
    ///     @li @b newestDay for @ref LogInfoFields::newestDay field
    ///     @li @b newestHour for @ref LogInfoFields::newestHour field
    ///     @li @b newestMinute for @ref LogInfoFields::newestMinute field
    ///     @li @b newestSecond for @ref LogInfoFields::newestSecond field
    ///     @li @b reserved5 for @ref LogInfoFields::reserved5 field
    ///     @li @b status for @ref LogInfoFields::status field
    ///     @li @b reserved6 for @ref LogInfoFields::reserved6 field
    COMMS_MSG_FIELDS_ACCESS(
        version,
        reserved1,
        filestoreCapacity,
        reserved2,
        reserved3,
        currentMaxLogSize,
        currentLogSize,
        entryCount,
        oldestYear,
        oldestMonth,
        oldestDay,
        oldestHour,
        oldestMinute,
        oldestSecond,
        reserved4,
        newestYear,
        newestMonth,
        newestDay,
        newestHour,
        newestMinute,
        newestSecond,
        reserved5,
        status,
        reserved6
    );

    /// @brief Default constructor
    LogInfo() = default;

    /// @brief Copy constructor
    LogInfo(const LogInfo&) = default;

    /// @brief Move constructor
    LogInfo(LogInfo&& other) = default;

    /// @brief Destructor
    ~LogInfo() = default;

    /// @brief Copy assignment
    LogInfo& operator=(const LogInfo&) = default;

    /// @brief Move assignment
    LogInfo& operator=(LogInfo&&) = default;
};


}  // namespace message

}  // namespace ublox

