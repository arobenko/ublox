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
/// @brief Contains definition of NAV-TIMEGPS message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-TIMEGPS message fields.
/// @see NavTimegps
struct NavTimegpsFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "fTOW" field.
    using fTOW = field::nav::fTOW;

    /// @brief Definition of "week" field.
    using week = field::nav::week;

    /// @brief Definition of "leapS" field.
    using leapS = field::common::I1;

    /// @brief Definition of "valid" field.
    struct validBits : public
        field::common::X1T<comms::option::BitmaskReservedBits<0xf8, 0> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(towValid, weekValid, leapSValid);
    };

    /// @brief Definition of "tAcc" field.
    using tAcc = field::nav::tAcc;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        fTOW,
        week,
        leapS,
        validBits,
        tAcc
    >;
};

/// @brief Definition of NAV-TIMEGPS message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavTimegpsFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavTimegps : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMEGPS>,
        comms::option::FieldsImpl<NavTimegpsFields::All>,
        comms::option::MsgType<NavTimegps<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMEGPS>,
        comms::option::FieldsImpl<NavTimegpsFields::All>,
        comms::option::MsgType<NavTimegps<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavTimegpsFields::iTOW field
    ///     @li @b fTOW for @ref NavTimegpsFields::fTOW field
    ///     @li @b week for @ref NavTimegpsFields::week field
    ///     @li @b leapS for @ref NavTimegpsFields::leapS field
    ///     @li @b valid for @ref NavTimegpsFields::validBits field
    ///     @li @b tAcc for @ref NavTimegpsFields::tAcc field
    COMMS_MSG_FIELDS_ACCESS(Base, iTOW, fTOW, week, leapS, valid, tAcc);

    /// @brief Default constructor
    NavTimegps() = default;

    /// @brief Copy constructor
    NavTimegps(const NavTimegps&) = default;

    /// @brief Move constructor
    NavTimegps(NavTimegps&& other) = default;

    /// @brief Destructor
    virtual ~NavTimegps() = default;

    /// @brief Copy assignment
    NavTimegps& operator=(const NavTimegps&) = default;

    /// @brief Move assignment
    NavTimegps& operator=(NavTimegps&&) = default;
};


}  // namespace message

}  // namespace ublox





