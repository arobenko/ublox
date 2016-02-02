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
/// @brief Contains definition of LOG-RETRIEVEPOS message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/log.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the LOG-RETRIEVEPOS message fields.
/// @see LogRetrievepos
struct LogRetrieveposFields
{
    /// @brief Value enumeration for @ref fixType field.
    enum class FixType : std::uint8_t
    {
        Fix_2D = 2, ///< 2D fix
        Fix_3D ///< 3D fix
    };

    /// @brief Definition of "entryIndex" field.
    using entryIndex  = field::common::U4;

    /// @brief Definition of "lon" field.
    using lon = field::common::I4T<comms::option::ScalingRatio<1, 10000000> >;

    /// @brief Definition of "lat" field.
    using lat = lon;

    /// @brief Definition of "hMSL" field.
    using hMSL = field::common::I4T<field::common::Scaling_mm2m>;

    /// @brief Definition of "hAcc" field.
    using hAcc = field::common::U4T<field::common::Scaling_mm2m>;

    /// @brief Definition of "gSpeed" field.
    using gSpeed = field::common::U4T<field::common::Scaling_mm2m>;

    /// @brief Definition of "heading" field.
    using heading = field::common::U4;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "fixType" field.
    using fixType =
        field::common::EnumT<
            FixType,
            comms::option::ValidNumValueRange<(int)FixType::Fix_2D, (int)FixType::Fix_3D>
        >;

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

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "numSV" field.
    using numSV = field::common::U1;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res1;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        entryIndex,
        lon,
        lat,
        hMSL,
        hAcc,
        gSpeed,
        heading,
        version,
        fixType,
        year,
        month,
        day,
        hour,
        minute,
        second,
        reserved1,
        numSV,
        reserved2
    >;
};

/// @brief Definition of LOG-RETRIEVEPOS message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref LogRetrieveposFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class LogRetrievepos : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_RETRIEVEPOS>,
        comms::option::FieldsImpl<LogRetrieveposFields::All>,
        comms::option::DispatchImpl<LogRetrievepos<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_RETRIEVEPOS>,
        comms::option::FieldsImpl<LogRetrieveposFields::All>,
        comms::option::DispatchImpl<LogRetrievepos<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_entryIndex, ///< @b entryIndex field, see @ref LogRetrieveposFields::entryIndex
        FieldIdx_lon, ///< @b lon field, see @ref LogRetrieveposFields::lon
        FieldIdx_lat, ///< @b lat field, see @ref LogRetrieveposFields::lat
        FieldIdx_hMSL, ///< @b hMSL field, see @ref LogRetrieveposFields::hMSL
        FieldIdx_hAcc, ///< @b hAcc field, see @ref LogRetrieveposFields::hAcc
        FieldIdx_gSpeed, ///< @b gSpeed field, see @ref LogRetrieveposFields::gSpeed
        FieldIdx_heading, ///< @b heading field, see @ref LogRetrieveposFields::heading
        FieldIdx_version, ///< @b version field, see @ref LogRetrieveposFields::version
        FieldIdx_fixType, ///< @b fixType field, see @ref LogRetrieveposFields::fixType
        FieldIdx_year, ///< @b year field, see @ref LogRetrieveposFields::year
        FieldIdx_month, ///< @b month field, see @ref LogRetrieveposFields::month
        FieldIdx_day, ///< @b day field, see @ref LogRetrieveposFields::day
        FieldIdx_hour, ///< @b hour field, see @ref LogRetrieveposFields::hour
        FieldIdx_minute, ///< @b minute field, see @ref LogRetrieveposFields::minute
        FieldIdx_second, ///< @b second field, see @ref LogRetrieveposFields::second
        FieldIdx_reserved1, ///< @b reserved1 field, see @ref LogRetrieveposFields::reserved1
        FieldIdx_numSV, ///< @b numSV field, see @ref LogRetrieveposFields::numSV
        FieldIdx_reserved2, ///< @b reserved2 field, see @ref LogRetrieveposFields::reserved2
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

