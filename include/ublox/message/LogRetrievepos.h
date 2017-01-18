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
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref LogRetrieveposFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class LogRetrievepos : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_RETRIEVEPOS>,
        comms::option::FieldsImpl<LogRetrieveposFields::All>,
        comms::option::MsgType<LogRetrievepos<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_RETRIEVEPOS>,
        comms::option::FieldsImpl<LogRetrieveposFields::All>,
        comms::option::MsgType<LogRetrievepos<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b entryIndex for @ref LogRetrieveposFields::entryIndex field
    ///     @li @b lon for @ref LogRetrieveposFields::lon field
    ///     @li @b lat for @ref LogRetrieveposFields::lat field
    ///     @li @b hMSL for @ref LogRetrieveposFields::hMSL field
    ///     @li @b hAcc for @ref LogRetrieveposFields::hAcc field
    ///     @li @b gSpeed for @ref LogRetrieveposFields::gSpeed field
    ///     @li @b heading for @ref LogRetrieveposFields::heading field
    ///     @li @b version for @ref LogRetrieveposFields::version field
    ///     @li @b fixType for @ref LogRetrieveposFields::fixType field
    ///     @li @b year for @ref LogRetrieveposFields::year field
    ///     @li @b month for @ref LogRetrieveposFields::month field
    ///     @li @b day for @ref LogRetrieveposFields::day field
    ///     @li @b hour for @ref LogRetrieveposFields::hour field
    ///     @li @b minute for @ref LogRetrieveposFields::minute field
    ///     @li @b second for @ref LogRetrieveposFields::second field
    ///     @li @b reserved1 for @ref LogRetrieveposFields::reserved1 field
    ///     @li @b numSV for @ref LogRetrieveposFields::numSV field
    ///     @li @b reserved2 for @ref LogRetrieveposFields::reserved2 field
    COMMS_MSG_FIELDS_ACCESS(Base,
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
    );

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

