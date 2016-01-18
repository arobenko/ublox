//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
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


#pragma once

#include "comms/Message.h"
#include "ublox/Message.h"
#include "ublox/field/common.h"
#include "ublox/field/log.h"

namespace ublox
{

namespace message
{

enum
{
    LogInfoField_status_recording = 3,
    LogInfoField_status_inactive,
    LogInfoField_status_circular,
    LogInfoField_status_numOfValues
};

using LogInfoField_version =
    field::common::U1T<
        comms::option::DefaultNumValue<1>,
        comms::option::ValidNumValueRange<1, 1>
    >;
using LogInfoField_reserved1 = field::common::res3;
using LogInfoField_filestoreCapacity  = field::common::U4;
using LogInfoField_reserved2 = field::common::res4;
using LogInfoField_reserved3 = field::common::res4;
using LogInfoField_currentMaxLogSize = field::common::U4;
using LogInfoField_currentLogSize = field::common::U4;
using LogInfoField_entryCount = field::common::U4;
using LogInfoField_oldestYear = field::log::year;
using LogInfoField_oldestMonth = field::log::month;
using LogInfoField_oldestDay = field::log::day;
using LogInfoField_oldestHour = field::log::hour;
using LogInfoField_oldestMinute = field::log::minute;
using LogInfoField_oldestSecond = field::log::second;
using LogInfoField_reserved4  = field::common::res1;
using LogInfoField_newestYear = field::log::year;
using LogInfoField_newestMonth = field::log::month;
using LogInfoField_newestDay = field::log::day;
using LogInfoField_newestHour = field::log::hour;
using LogInfoField_newestMinute = field::log::minute;
using LogInfoField_newestSecond = field::log::second;
using LogInfoField_reserved5  = field::common::res1;
using LogInfoField_status =
    field::common::X1T<
        comms::option::BitmaskReservedBits<0xc7, 0>
    >;
using LogInfoField_reserved6  = field::common::res3;

using LogInfoFields = std::tuple<
    LogInfoField_version,
    LogInfoField_reserved1,
    LogInfoField_filestoreCapacity,
    LogInfoField_reserved2,
    LogInfoField_reserved3,
    LogInfoField_currentMaxLogSize,
    LogInfoField_currentLogSize,
    LogInfoField_entryCount,
    LogInfoField_oldestYear,
    LogInfoField_oldestMonth,
    LogInfoField_oldestDay,
    LogInfoField_oldestHour,
    LogInfoField_oldestMinute,
    LogInfoField_oldestSecond,
    LogInfoField_reserved4,
    LogInfoField_newestYear,
    LogInfoField_newestMonth,
    LogInfoField_newestDay,
    LogInfoField_newestHour,
    LogInfoField_newestMinute,
    LogInfoField_newestSecond,
    LogInfoField_reserved5,
    LogInfoField_status,
    LogInfoField_reserved6
>;


template <typename TMsgBase = Message>
class LogInfo : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_INFO>,
        comms::option::FieldsImpl<LogInfoFields>,
        comms::option::DispatchImpl<LogInfo<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_INFO>,
        comms::option::FieldsImpl<LogInfoFields>,
        comms::option::DispatchImpl<LogInfo<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_version,
        FieldIdx_reserved1,
        FieldIdx_filestoreCapacity,
        FieldIdx_reserved2,
        FieldIdx_reserved3,
        FieldIdx_currentMaxLogSize,
        FieldIdx_currentLogSize,
        FieldIdx_entryCount,
        FieldIdx_oldestYear,
        FieldIdx_oldestMonth,
        FieldIdx_oldestDay,
        FieldIdx_oldestHour,
        FieldIdx_oldestMinute,
        FieldIdx_oldestSecond,
        FieldIdx_reserved4,
        FieldIdx_newestYear,
        FieldIdx_newestMonth,
        FieldIdx_newestDay,
        FieldIdx_newestHour,
        FieldIdx_newestMinute,
        FieldIdx_newestSecond,
        FieldIdx_reserved5,
        FieldIdx_status,
        FieldIdx_reserved6,
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

