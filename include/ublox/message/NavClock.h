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
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref NavClockFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavClock : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_CLOCK>,
        comms::option::FieldsImpl<NavClockFields::All>,
        comms::option::DispatchImpl<NavClock<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_CLOCK>,
        comms::option::FieldsImpl<NavClockFields::All>,
        comms::option::DispatchImpl<NavClock<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_iTOW, ///< @b iTOW field, see @ref NavClockFields::iTOW
        FieldIdx_clkB, ///< @b clkB field, see @ref NavClockFields::clkB
        FieldIdx_clkD, ///< @b clkD field, see @ref NavClockFields::clkD
        FieldIdx_tAcc, ///< @b tAcc field, see @ref NavClockFields::tAcc
        FieldIdx_fAcc, ///< @b fAcc field, see @ref NavClockFields::fAcc
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    NavClock() = default;

    /// @brief Copy constructor
    NavClock(const NavClock&) = default;

    /// @brief Move constructor
    NavClock(NavClock&& other) = default;

    /// @brief Destructor
    virtual ~NavClock() = default;

    /// @brief Copy assignment
    NavClock& operator=(const NavClock&) = default;

    /// @brief Move assignment
    NavClock& operator=(NavClock&&) = default;
};


}  // namespace message

}  // namespace ublox





