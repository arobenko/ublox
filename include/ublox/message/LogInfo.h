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
    /// @brief Bits access enumeration for @ref status bitmask field.
    enum
    {
        status_recording = 3, ///< @b recording bit index
        status_inactive, ///< @b inactive bit index
        status_circular, ///< @b circular bit index
        status_numOfValues ///< upper limit for available bits
    };

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
    using status =
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xc7, 0>
        >;

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
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref LogInfoFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class LogInfo : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_INFO>,
        comms::option::FieldsImpl<LogInfoFields::All>,
        comms::option::DispatchImpl<LogInfo<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_INFO>,
        comms::option::FieldsImpl<LogInfoFields::All>,
        comms::option::DispatchImpl<LogInfo<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_version, ///< @b version field, see @ref LogInfoFields::version
        FieldIdx_reserved1, ///< @b reserved1 field, see @ref LogInfoFields::reserved1
        FieldIdx_filestoreCapacity, ///< @b filestoreCapacity field, see @ref LogInfoFields::filestoreCapacity
        FieldIdx_reserved2, ///< @b reserved2 field, see @ref LogInfoFields::reserved2
        FieldIdx_reserved3, ///< @b reserved3 field, see @ref LogInfoFields::reserved3
        FieldIdx_currentMaxLogSize, ///< @b currentMaxLogSize field, see @ref LogInfoFields::currentMaxLogSize
        FieldIdx_currentLogSize, ///< @b currentLogSize field, see @ref LogInfoFields::currentLogSize
        FieldIdx_entryCount, ///< @b entryCount field, see @ref LogInfoFields::entryCount
        FieldIdx_oldestYear, ///< @b oldestYear field, see @ref LogInfoFields::oldestYear
        FieldIdx_oldestMonth, ///< @b oldestMonth field, see @ref LogInfoFields::oldestMonth
        FieldIdx_oldestDay, ///< @b oldestDay field, see @ref LogInfoFields::oldestDay
        FieldIdx_oldestHour, ///< @b oldestHour field, see @ref LogInfoFields::oldestHour
        FieldIdx_oldestMinute, ///< @b oldestMinute field, see @ref LogInfoFields::oldestMinute
        FieldIdx_oldestSecond, ///< @b oldestSecond field, see @ref LogInfoFields::oldestSecond
        FieldIdx_reserved4, ///< @b reserved4 field, see @ref LogInfoFields::reserved4
        FieldIdx_newestYear, ///< @b newestYear field, see @ref LogInfoFields::newestYear
        FieldIdx_newestMonth, ///< @b newestMonth field, see @ref LogInfoFields::newestMonth
        FieldIdx_newestDay, ///< @b newestDay field, see @ref LogInfoFields::newestDay
        FieldIdx_newestHour, ///< @b newestHour field, see @ref LogInfoFields::newestHour
        FieldIdx_newestMinute, ///< @b newestMinute field, see @ref LogInfoFields::newestMinute
        FieldIdx_newestSecond, ///< @b newestSecond field, see @ref LogInfoFields::newestSecond
        FieldIdx_reserved5, ///< @b reserved5 field, see @ref LogInfoFields::reserved5
        FieldIdx_status, ///< @b status field, see @ref LogInfoFields::status
        FieldIdx_reserved6, ///< @b reserved6 field, see @ref LogInfoFields::reserved6
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    LogInfo() = default;

    /// @brief Copy constructor
    LogInfo(const LogInfo&) = default;

    /// @brief Move constructor
    LogInfo(LogInfo&& other) = default;

    /// @brief Destructor
    virtual ~LogInfo() = default;

    /// @brief Copy assignment
    LogInfo& operator=(const LogInfo&) = default;

    /// @brief Move assignment
    LogInfo& operator=(LogInfo&&) = default;
};


}  // namespace message

}  // namespace ublox

