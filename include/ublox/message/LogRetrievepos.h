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

enum class LogRetrievepos_FixType : std::uint8_t
{
    Fix_2D = 2,
    Fix_3D
};

using LogRetrieveposField_entryIndex  = field::common::U4;
using LogRetrieveposField_lon = field::common::I4T<comms::option::ScalingRatio<1, 7> >;
using LogRetrieveposField_lat = LogRetrieveposField_lon;
using LogRetrieveposField_hMSL = field::common::I4T<field::common::Scaling_mm2m>;
using LogRetrieveposField_hAcc = field::common::U4T<field::common::Scaling_mm2m>;
using LogRetrieveposField_gSpeed = field::common::U4T<field::common::Scaling_mm2m>;
using LogRetrieveposField_heading = field::common::U4;
using LogRetrieveposField_version =
    field::common::U1T<
        comms::option::ValidNumValueRange<0, 0>
    >;
using LogRetrieveposField_fixType =
    field::common::EnumT<
        LogRetrievepos_FixType,
        comms::option::ValidNumValueRange<(int)LogRetrievepos_FixType::Fix_2D, (int)LogRetrievepos_FixType::Fix_3D>
    >;
using LogRetrieveposField_year = field::log::year;
using LogRetrieveposField_month = field::log::month;
using LogRetrieveposField_day = field::log::day;
using LogRetrieveposField_hour = field::log::hour;
using LogRetrieveposField_minute = field::log::minute;
using LogRetrieveposField_second = field::log::second;
using LogRetrieveposField_reserved1 = field::common::res1;
using LogRetrieveposField_numSV = field::common::U1;
using LogRetrieveposField_reserved2 = field::common::res1;

using LogRetrieveposFields = std::tuple<
    LogRetrieveposField_entryIndex,
    LogRetrieveposField_lon,
    LogRetrieveposField_lat,
    LogRetrieveposField_hMSL,
    LogRetrieveposField_hAcc,
    LogRetrieveposField_gSpeed,
    LogRetrieveposField_heading,
    LogRetrieveposField_version,
    LogRetrieveposField_fixType,
    LogRetrieveposField_year,
    LogRetrieveposField_month,
    LogRetrieveposField_day,
    LogRetrieveposField_hour,
    LogRetrieveposField_minute,
    LogRetrieveposField_second,
    LogRetrieveposField_reserved1,
    LogRetrieveposField_numSV,
    LogRetrieveposField_reserved2
>;


template <typename TMsgBase = Message>
class LogRetrievepos : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_RETRIEVEPOS>,
        comms::option::FieldsImpl<LogRetrieveposFields>,
        comms::option::DispatchImpl<LogRetrievepos<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_RETRIEVEPOS>,
        comms::option::FieldsImpl<LogRetrieveposFields>,
        comms::option::DispatchImpl<LogRetrievepos<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_entryIndex,
        FieldIdx_lon,
        FieldIdx_lat,
        FieldIdx_hMSL,
        FieldIdx_hAcc,
        FieldIdx_gSpeed,
        FieldIdx_heading,
        FieldIdx_version,
        FieldIdx_fixType,
        FieldIdx_year,
        FieldIdx_month,
        FieldIdx_day,
        FieldIdx_hour,
        FieldIdx_minute,
        FieldIdx_second,
        FieldIdx_reserved1,
        FieldIdx_numSV,
        FieldIdx_reserved2,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    LogRetrievepos() = default;

    /// @brief Copy constructor
    LogRetrievepos(const LogRetrievepos&) = default;

    /// @brief Move constructor
    LogRetrievepos(LogRetrievepos&& other) = default;

    /// @brief Destructor
    virtual ~LogRetrievepos() = default;

    /// @brief Copy assignment
    LogRetrievepos& operator=(const LogRetrievepos&) = default;

    /// @brief Move assignment
    LogRetrievepos& operator=(LogRetrievepos&&) = default;
};


}  // namespace message

}  // namespace ublox

