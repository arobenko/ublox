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
/// @brief Contains definition of NAV-TIMEGLO message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-TIMEGLO message fields.
/// @see NavTimeglo
struct NavTimegloFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "TOD" field.
    using TOD = field::common::U4;

    /// @brief Definition of "fTOD" field.
    using fTOD = field::nav::fTOW;

    /// @brief Definition of "Nt" field.
    using Nt = field::common::U2;

    /// @brief Definition of "N4" field.
    using N4 = field::common::U1;

    /// @brief Definition of "valid" field.
    struct validBits : public
        field::common::X1T<comms::option::BitmaskReservedBits<0xfc, 0> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(todValid, dateValid);
    };

    /// @brief Definition of "tAcc" field.
    using tAcc = field::nav::tAcc;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        TOD,
        fTOD,
        Nt,
        N4,
        validBits,
        tAcc
    >;
};

/// @brief Definition of NAV-TIMEGLO message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavTimegloFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavTimeglo : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMEGLO>,
        comms::option::FieldsImpl<NavTimegloFields::All>,
        comms::option::MsgType<NavTimeglo<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMEGLO>,
        comms::option::FieldsImpl<NavTimegloFields::All>,
        comms::option::MsgType<NavTimeglo<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavTimegloFields::iTOW field
    ///     @li @b TOD for @ref NavTimegloFields::TOD field
    ///     @li @b fTOD for @ref NavTimegloFields::fTOD field
    ///     @li @b Nt for @ref NavTimegloFields::Nt field
    ///     @li @b N4 for @ref NavTimegloFields::N4 field
    ///     @li @b valid for @ref NavTimegloFields::validBits field
    ///     @li @b tAcc for @ref NavTimegloFields::tAcc field
    COMMS_MSG_FIELDS_ACCESS(iTOW, TOD, fTOD, Nt, N4, valid, tAcc);

    /// @brief Default constructor
    NavTimeglo() = default;

    /// @brief Copy constructor
    NavTimeglo(const NavTimeglo&) = default;

    /// @brief Move constructor
    NavTimeglo(NavTimeglo&& other) = default;

    /// @brief Destructor
    ~NavTimeglo() = default;

    /// @brief Copy assignment
    NavTimeglo& operator=(const NavTimeglo&) = default;

    /// @brief Move assignment
    NavTimeglo& operator=(NavTimeglo&&) = default;
};


}  // namespace message

}  // namespace ublox





