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
/// @brief Contains definition of NAV-SVIN message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-SVIN message fields.
/// @see NavSvin
struct NavSvinFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res3;

    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "dur" field.
    using dur = field::common::U4T<comms::option::UnitsSeconds>;

    /// @brief Definition of "meanX" field.
    using meanX =
        field::common::I4T<
            comms::option::UnitsCentimeters
        >;

    /// @brief Definition of "meanY" field.
    using meanY = meanX;

    /// @brief Definition of "meanZ" field.
    using meanZ = meanX;

    /// @brief Definition of "meanXHP" field.
    using meanXHP =
        field::common::I1T<
            comms::option::UnitsMillimeters,
            comms::option::ScalingRatio<1, 10>,
            comms::option::ValidNumValueRange<-99, 99>
        >;

    /// @brief Definition of "meanYHP" field.
    using meanYHP = meanXHP;

    /// @brief Definition of "meanZHP" field.
    using meanZHP = meanXHP;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res1;

    /// @brief Definition of "meanAcc" field.
    using meanAcc =
        field::common::U4T<
            comms::option::UnitsMillimeters,
            comms::option::ScalingRatio<1, 10>
        >;

    /// @brief Definition of "obs" field.
    using obs = field::common::U4;

    /// @brief Definition of "valid" field.
    using isValid = field::common::U1T<comms::option::ValidNumValueRange<0, 1> >;

    /// @brief Definition of "active" field.
    using active = field::common::U1T<comms::option::ValidNumValueRange<0, 1> >;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res2;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        reserved1,
        iTOW,
        dur,
        meanX,
        meanY,
        meanZ,
        meanXHP,
        meanYHP,
        meanZHP,
        reserved2,
        meanAcc,
        obs,
        isValid,
        active,
        reserved3
    >;
};

/// @brief Definition of NAV-SVIN message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavSvinFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavSvin : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SVIN>,
        comms::option::FieldsImpl<NavSvinFields::All>,
        comms::option::MsgType<NavSvin<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref NavSvinFields::version field
    ///     @li @b reserved1 for @ref NavSvinFields::reserved1 field
    ///     @li @b iTOW for @ref NavSvinFields::iTOW field
    ///     @li @b dur for @ref NavSvinFields::dur field
    ///     @li @b meanX for @ref NavSvinFields::meanX field
    ///     @li @b meanY for @ref NavSvinFields::meanY field
    ///     @li @b meanZ for @ref NavSvinFields::meanZ field
    ///     @li @b meanXHP for @ref NavSvinFields::meanXHP field
    ///     @li @b meanYHP for @ref NavSvinFields::meanYHP field
    ///     @li @b meanYHP for @ref NavSvinFields::meanYHP field
    ///     @li @b reserved2 for @ref NavSvinFields::reserved2 field
    ///     @li @b meanAcc for @ref NavSvinFields::meanAcc field
    ///     @li @b obs for @ref NavSvinFields::obs field
    ///     @li @b valid for @ref NavSvinFields::isValid field
    ///     @li @b active for @ref NavSvinFields::active field
    ///     @li @b reserved3 for @ref NavSvinFields::reserved3 field
    COMMS_MSG_FIELDS_ACCESS(
        version,
        reserved1,
        iTOW,
        dur,
        meanX,
        meanY,
        meanZ,
        meanXHP,
        meanYHP,
        meanZHP,
        reserved2,
        meanAcc,
        obs,
        valid,
        active,
        reserved3
    );

    /// @brief Default constructor
    NavSvin() = default;

    /// @brief Copy constructor
    NavSvin(const NavSvin&) = default;

    /// @brief Move constructor
    NavSvin(NavSvin&& other) = default;

    /// @brief Destructor
    ~NavSvin() = default;

    /// @brief Copy assignment
    NavSvin& operator=(const NavSvin&) = default;

    /// @brief Move assignment
    NavSvin& operator=(NavSvin&&) = default;
};


}  // namespace message

}  // namespace ublox





