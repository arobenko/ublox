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
/// @brief Contains definition of NAV-ATT message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-ATT message fields.
/// @see NavAtt
struct NavAttFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<comms::option::ValidNumValueRange<0, 0> >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res3;

    /// @bried Definition of "roll" field.
    using roll =
        field::common::I4T<
            comms::option::UnitsDegrees,
            comms::option::ScalingRatio<1, 100000>
        >;

    /// @bried Definition of "pitch" field.
    using pitch =
        field::common::I4T<
            comms::option::UnitsDegrees,
            comms::option::ScalingRatio<1, 100000>
        >;

    /// @bried Definition of "heading" field.
    using heading =
        field::common::I4T<
            comms::option::UnitsDegrees,
            comms::option::ScalingRatio<1, 100000>
        >;

    /// @bried Definition of "accRoll" field.
    using accRoll =
        field::common::U4T<
            comms::option::UnitsDegrees,
            comms::option::ScalingRatio<1, 100000>
        >;

    /// @bried Definition of "accPitch" field.
    using accPitch =
        field::common::U4T<
            comms::option::UnitsDegrees,
            comms::option::ScalingRatio<1, 100000>
        >;

    /// @bried Definition of "accHeading" field.
    using accHeading =
        field::common::U4T<
            comms::option::UnitsDegrees,
            comms::option::ScalingRatio<1, 100000>
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        version,
        reserved1,
        roll,
        pitch,
        heading,
        accRoll,
        accPitch,
        accHeading
    >;
};

/// @brief Definition of NAV-ATT message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavAttFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavAtt : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_ATT>,
        comms::option::FieldsImpl<NavAttFields::All>,
        comms::option::MsgType<NavAtt<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavAttFields::iTOW field
    ///     @li @b version for @ref NavAttFields::version field
    ///     @li @b reserved1 for @ref NavAttFields::reserved1 field
    ///     @li @b roll for @ref NavAttFields::roll field
    ///     @li @b pitch for @ref NavAttFields::pitch field
    ///     @li @b heading for @ref NavAttFields::heading field
    ///     @li @b accRoll for @ref NavAttFields::accRoll field
    ///     @li @b accPitch for @ref NavAttFields::accPitch field
    ///     @li @b accHeading for @ref NavAttFields::accHeading field
    COMMS_MSG_FIELDS_ACCESS(
        iTOW,
        version,
        reserved1,
        roll,
        pitch,
        heading,
        accRoll,
        accPitch,
        accHeading
    );

    /// @brief Default constructor
    NavAtt() = default;

    /// @brief Copy constructor
    NavAtt(const NavAtt&) = default;

    /// @brief Move constructor
    NavAtt(NavAtt&& other) = default;

    /// @brief Destructor
    ~NavAtt() = default;

    /// @brief Copy assignment
    NavAtt& operator=(const NavAtt&) = default;

    /// @brief Move assignment
    NavAtt& operator=(NavAtt&&) = default;
};


}  // namespace message

}  // namespace ublox





