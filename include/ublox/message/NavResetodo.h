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
/// @brief Contains definition of NAV-RESETODO message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-RESETODO message fields.
/// @see NavResetodo
struct NavResetodoFields
{
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<>;
};

/// @brief Definition of NAV-RESETODO message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavResetodoFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavResetodo : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_RESETODO>,
        comms::option::FieldsImpl<NavResetodoFields::All>,
        comms::option::MsgType<NavResetodo<TMsgBase> >
    >
{
public:

    /// @brief Default constructor
    NavResetodo() = default;

    /// @brief Copy constructor
    NavResetodo(const NavResetodo&) = default;

    /// @brief Move constructor
    NavResetodo(NavResetodo&& other) = default;

    /// @brief Destructor
    ~NavResetodo() = default;

    /// @brief Copy assignment
    NavResetodo& operator=(const NavResetodo&) = default;

    /// @brief Move assignment
    NavResetodo& operator=(NavResetodo&&) = default;
};


}  // namespace message

}  // namespace ublox





