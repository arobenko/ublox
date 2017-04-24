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
/// @brief Contains definition of NAV-POSECEF message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{
/// @brief Accumulates details of all the NAV-POSECEF message fields.
/// @see NavPosecef
struct NavPosecefFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "iTOW" field.
    using ecefX = field::nav::ecefX;

    /// @brief Definition of "iTOW" field.
    using ecefY = field::nav::ecefY;

    /// @brief Definition of "iTOW" field.
    using ecefZ = field::nav::ecefZ;

    /// @brief Definition of "iTOW" field.
    using pAcc = field::nav::pAcc;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        ecefX,
        ecefY,
        ecefZ,
        pAcc
    >;
};

/// @brief Definition of NAV-POSECEF message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavPosecefFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavPosecef : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_POSECEF>,
        comms::option::FieldsImpl<NavPosecefFields::All>,
        comms::option::MsgType<NavPosecef<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavPosecefFields::iTOW field
    ///     @li @b ecefX for @ref NavPosecefFields::ecefX field
    ///     @li @b ecefY for @ref NavPosecefFields::ecefY field
    ///     @li @b ecefZ for @ref NavPosecefFields::ecefZ field
    ///     @li @b pAcc for @ref NavPosecefFields::pAcc field
    COMMS_MSG_FIELDS_ACCESS(iTOW, ecefX, ecefY, ecefZ, pAcc);

    /// @brief Default constructor
    NavPosecef() = default;

    /// @brief Copy constructor
    NavPosecef(const NavPosecef&) = default;

    /// @brief Move constructor
    NavPosecef(NavPosecef&& other) = default;

    /// @brief Destructor
    ~NavPosecef() = default;

    /// @brief Copy assignment
    NavPosecef& operator=(const NavPosecef&) = default;

    /// @brief Move assignment
    NavPosecef& operator=(NavPosecef&&) = default;
};


}  // namespace message

}  // namespace ublox





