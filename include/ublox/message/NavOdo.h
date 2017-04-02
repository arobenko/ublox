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
/// @brief Contains definition of NAV-ODO message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-ODO message fields.
/// @see NavOdo
struct NavOdoFields
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

    /// @brief Definition of "distance" field.
    using distance = field::common::U4;

    /// @brief Definition of "totalDistance" field.
    using totalDistance = field::common::U4;

    /// @brief Definition of "distanceStd" field.
    using distanceStd = field::common::U4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        reserved1,
        iTOW,
        distance,
        totalDistance,
        distanceStd
    >;
};

/// @brief Definition of NAV-ODO message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavOdoFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavOdo : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_ODO>,
        comms::option::FieldsImpl<NavOdoFields::All>,
        comms::option::MsgType<NavOdo<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref NavOdoFields::version field
    ///     @li @b reserved1 for @ref NavOdoFields::reserved1 field
    ///     @li @b iTOW for @ref NavOdoFields::iTOW field
    ///     @li @b distance for @ref NavOdoFields::distance field
    ///     @li @b distanceStd for @ref NavOdoFields::distanceStd field
    COMMS_MSG_FIELDS_ACCESS(
        version,
        reserved1,
        iTOW,
        distance,
        totalDistance,
        distanceStd
    );

    /// @brief Default constructor
    NavOdo() = default;

    /// @brief Copy constructor
    NavOdo(const NavOdo&) = default;

    /// @brief Move constructor
    NavOdo(NavOdo&& other) = default;

    /// @brief Destructor
    ~NavOdo() = default;

    /// @brief Copy assignment
    NavOdo& operator=(const NavOdo&) = default;

    /// @brief Move assignment
    NavOdo& operator=(NavOdo&&) = default;
};


}  // namespace message

}  // namespace ublox





