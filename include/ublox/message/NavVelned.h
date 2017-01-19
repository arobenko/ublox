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
/// @brief Contains definition of NAV-VELNED message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-VELNED message fields.
/// @see NavVelned
struct NavVelnedFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "velN" field.
    using velN = field::common::I4T<field::common::Scaling_cm2m>;;

    /// @brief Definition of "velE" field.
    using velE = velN;

    /// @brief Definition of "velD" field.
    using velD = velN;

    /// @brief Definition of "speed" field.
    using speed = field::common::U4T<field::common::Scaling_cm2m>;

    /// @brief Definition of "gSpeed" field.
    using gSpeed = field::common::U4T<field::common::Scaling_cm2m>;

    /// @brief Definition of "heading" field.
    using heading = field::nav::heading;

    /// @brief Definition of "sAcc" field.
    using sAcc = field::nav::sAcc;

    /// @brief Definition of "cAcc" field.
    using cAcc =
        field::common::U4T<comms::option::ScalingRatio<1, 100000> >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        velN,
        velE,
        velD,
        speed,
        gSpeed,
        heading,
        sAcc,
        cAcc
    >;
};

/// @brief Definition of NAV-VELNED message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavVelnedFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavVelned : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_VELNED>,
        comms::option::FieldsImpl<NavVelnedFields::All>,
        comms::option::MsgType<NavVelned<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_VELNED>,
        comms::option::FieldsImpl<NavVelnedFields::All>,
        comms::option::MsgType<NavVelned<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavVelnedFields::iTOW field
    ///     @li @b velN for @ref NavVelnedFields::velN field
    ///     @li @b velE for @ref NavVelnedFields::velE field
    ///     @li @b velD for @ref NavVelnedFields::velD field
    ///     @li @b speed for @ref NavVelnedFields::speed field
    ///     @li @b gSpeed for @ref NavVelnedFields::gSpeed field
    ///     @li @b heading for @ref NavVelnedFields::heading field
    ///     @li @b sAcc for @ref NavVelnedFields::sAcc field
    ///     @li @b cAcc for @ref NavVelnedFields::cAcc field
    COMMS_MSG_FIELDS_ACCESS(Base, iTOW, velN, velE, velD, speed, gSpeed, heading, sAcc, cAcc);

    /// @brief Default constructor
    NavVelned() = default;

    /// @brief Copy constructor
    NavVelned(const NavVelned&) = default;

    /// @brief Move constructor
    NavVelned(NavVelned&& other) = default;

    /// @brief Destructor
    virtual ~NavVelned() = default;

    /// @brief Copy assignment
    NavVelned& operator=(const NavVelned&) = default;

    /// @brief Move assignment
    NavVelned& operator=(NavVelned&&) = default;
};


}  // namespace message

}  // namespace ublox





