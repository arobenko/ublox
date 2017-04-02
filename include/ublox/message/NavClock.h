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
/// @brief Contains definition of NAV-CLOCK message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-CLOCK message fields.
/// @see NavClock
struct NavClockFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "clkB" field.
    using clkB = field::common::I4T<field::common::Scaling_ns2s>;

    /// @brief Definition of "clkD" field.
    using clkD = field::common::I4T<field::common::Scaling_ns2s>;

    /// @brief Definition of "tAcc" field.
    using tAcc = field::nav::tAcc;

    /// @brief Definition of "fAcc" field.
    using fAcc = field::common::U4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        clkB,
        clkD,
        tAcc,
        fAcc
    >;
};

/// @brief Definition of NAV-CLOCK message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavClockFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavClock : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_CLOCK>,
        comms::option::FieldsImpl<NavClockFields::All>,
        comms::option::MsgType<NavClock<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_CLOCK>,
        comms::option::FieldsImpl<NavClockFields::All>,
        comms::option::MsgType<NavClock<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavClockFields::iTOW field
    ///     @li @b clkB for @ref NavClockFields::clkB field
    ///     @li @b clkD for @ref NavClockFields::clkD field
    ///     @li @b tAcc for @ref NavClockFields::tAcc field
    ///     @li @b fAcc for @ref NavClockFields::fAcc field
    COMMS_MSG_FIELDS_ACCESS(iTOW, clkB, clkD, tAcc, fAcc);

    /// @brief Default constructor
    NavClock() = default;

    /// @brief Copy constructor
    NavClock(const NavClock&) = default;

    /// @brief Move constructor
    NavClock(NavClock&& other) = default;

    /// @brief Destructor
    ~NavClock() = default;

    /// @brief Copy assignment
    NavClock& operator=(const NavClock&) = default;

    /// @brief Move assignment
    NavClock& operator=(NavClock&&) = default;
};


}  // namespace message

}  // namespace ublox





