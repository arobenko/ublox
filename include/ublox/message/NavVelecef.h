//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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
/// @brief Contains definition of NAV-VELECEF message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-VELECEF message fields.
/// @see NavVelecef
struct NavVelecefFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "ecefVX" field.
    using ecefVX = field::nav::ecefVX;

    /// @brief Definition of "ecefVY" field.
    using ecefVY = field::nav::ecefVY;

    /// @brief Definition of "ecefVZ" field.
    using ecefVZ = field::nav::ecefVZ;

    /// @brief Definition of "sAcc" field.
    using sAcc = field::nav::sAcc;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        ecefVX,
        ecefVY,
        ecefVZ,
        sAcc
    >;
};

/// @brief Definition of NAV-VELECEF message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavVelecefFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavVelecef : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_VELECEF>,
        comms::option::FieldsImpl<NavVelecefFields::All>,
        comms::option::MsgType<NavVelecef<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavVelecefFields::iTOW field
    ///     @li @b ecefVX for @ref NavVelecefFields::ecefVX field
    ///     @li @b ecefVY for @ref NavVelecefFields::ecefVY field
    ///     @li @b ecefVZ for @ref NavVelecefFields::ecefVZ field
    ///     @li @b sAcc for @ref NavVelecefFields::sAcc field
    COMMS_MSG_FIELDS_ACCESS(iTOW, ecefVX, ecefVY, ecefVZ, sAcc);

    /// @brief Default constructor
    NavVelecef() = default;

    /// @brief Copy constructor
    NavVelecef(const NavVelecef&) = default;

    /// @brief Move constructor
    NavVelecef(NavVelecef&& other) = default;

    /// @brief Destructor
    ~NavVelecef() = default;

    /// @brief Copy assignment
    NavVelecef& operator=(const NavVelecef&) = default;

    /// @brief Move assignment
    NavVelecef& operator=(NavVelecef&&) = default;
};


}  // namespace message

}  // namespace ublox





