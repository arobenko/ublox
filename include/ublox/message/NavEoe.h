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
/// @brief Contains definition of NAV-EOE message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-EOE message fields.
/// @see NavEoe
struct NavEoeFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW
    >;
};

/// @brief Definition of NAV-EOE message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavEoeFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavEoe : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_EOE>,
        comms::option::FieldsImpl<NavEoeFields::All>,
        comms::option::MsgType<NavEoe<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_EOE>,
        comms::option::FieldsImpl<NavEoeFields::All>,
        comms::option::MsgType<NavEoe<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavEoeFields::iTOW field
    COMMS_MSG_FIELDS_ACCESS(iTOW);

    /// @brief Default constructor
    NavEoe() = default;

    /// @brief Copy constructor
    NavEoe(const NavEoe&) = default;

    /// @brief Move constructor
    NavEoe(NavEoe&& other) = default;

    /// @brief Destructor
    virtual ~NavEoe() = default;

    /// @brief Copy assignment
    NavEoe& operator=(const NavEoe&) = default;

    /// @brief Move assignment
    NavEoe& operator=(NavEoe&&) = default;
};


}  // namespace message

}  // namespace ublox





