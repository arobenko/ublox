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
/// @brief Contains definition of NAV-HPPOSLLH message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-HPPOSLLH message fields.
/// @see NavHpposllh
struct NavHpposllhFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<comms::option::ValidNumValueRange<0, 0> >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res3;

    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "lon" field.
    using lon = field::nav::lon;

    /// @brief Definition of "lat" field.
    using lat = field::nav::lat;

    /// @brief Definition of "height" field.
    using height = field::nav::height;

    /// @brief Definition of "hMSL" field.
    using hMSL = field::nav::hMSL;

    /// @brief Definition of "lonHp" field.
    using lonHp =
        field::common::I1T<
            comms::option::ScalingRatio<1, 1000000000L>,
            comms::option::UnitsDegrees,
            comms::option::ValidNumValueRange<-99, 99>
        >;

    /// @brief Definition of "lonHp" field.
    using latHp = lonHp;

    /// @brief Definition of "heightHp" field.
    using heightHp =
        field::common::I1T<
            comms::option::UnitsMillimeters,
            comms::option::ScalingRatio<1, 10>,
            comms::option::ValidNumValueRange<-9, 9>
        >;

    /// @brief Definition of "hMSLHp" field.
    using hMSLHp = heightHp;

    /// @brief Definition of "hAcc" field.
    using hAcc =
        field::common::U4T<
            comms::option::UnitsMillimeters,
            comms::option::ScalingRatio<1, 10>
        >;

    /// @brief Definition of "vAcc" field.
    using vAcc = hAcc;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        reserved1,
        iTOW,
        lon,
        lat,
        height,
        hMSL,
        lonHp,
        latHp,
        heightHp,
        hMSLHp,
        hAcc,
        vAcc
    >;
};

/// @brief Definition of NAV-HPPOSLLH message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavHpposllhFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavHpposllh : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_HPPOSLLH>,
        comms::option::FieldsImpl<NavHpposllhFields::All>,
        comms::option::MsgType<NavHpposllh<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref NavHpposllhFields::version field
    ///     @li @b reserved1 for @ref NavHpposllhFields::reserved1 field
    ///     @li @b iTOW for @ref NavHpposllhFields::iTOW field
    ///     @li @b lon for @ref NavHpposllhFields::lon field
    ///     @li @b lat for @ref NavHpposllhFields::lat field
    ///     @li @b height for @ref NavHpposllhFields::height field
    ///     @li @b hMSL for @ref NavHpposllhFields::hMSL field
    ///     @li @b lonHp for @ref NavHpposllhFields::lonHp field
    ///     @li @b latHp for @ref NavHpposllhFields::latHp field
    ///     @li @b heightHp for @ref NavHpposllhFields::heightHp field
    ///     @li @b hMSLHp for @ref NavHpposllhFields::hMSLHp field
    ///     @li @b hAcc for @ref NavHpposllhFields::hAcc field
    ///     @li @b vAcc for @ref NavHpposllhFields::vAcc field
    COMMS_MSG_FIELDS_ACCESS(
        version,
        reserved1,
        iTOW,
        lon,
        lat,
        height,
        hMSL,
        lonHp,
        latHp,
        heightHp,
        hMSLHp,
        hAcc,
        vAcc);

    /// @brief Default constructor
    NavHpposllh() = default;

    /// @brief Copy constructor
    NavHpposllh(const NavHpposllh&) = default;

    /// @brief Move constructor
    NavHpposllh(NavHpposllh&& other) = default;

    /// @brief Destructor
    ~NavHpposllh() = default;

    /// @brief Copy assignment
    NavHpposllh& operator=(const NavHpposllh&) = default;

    /// @brief Move assignment
    NavHpposllh& operator=(NavHpposllh&&) = default;
};

}  // namespace message

}  // namespace ublox





