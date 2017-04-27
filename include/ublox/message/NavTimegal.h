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
/// @brief Contains definition of NAV-TIMEGAL message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-TIMEGAL message fields.
/// @see NavTimegal
struct NavTimegalFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "galTOW" field.
    using galTOW = field::common::U4T<comms::option::UnitsSeconds>;

    /// @brief Definition of "fSOW" field.
    using fGalTOW = field::nav::fTOW;

    /// @brief Definition of "week" field.
    using galWno = field::nav::week;

    /// @brief Definition of "leapS" field.
    using leapS = field::common::I1T<comms::option::UnitsSeconds>;

    /// @brief Definition of "valid" field.
    struct validBits : public
        field::common::X1T<comms::option::BitmaskReservedBits<0xf8, 0> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(galTowValid, galWnoValid, leapSValid);
    };

    /// @brief Definition of "tAcc" field.
    using tAcc = field::nav::tAcc;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        galTOW,
        fGalTOW,
        galWno,
        leapS,
        validBits,
        tAcc
    >;
};

/// @brief Definition of NAV-TIMEGAL message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavTimegalFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavTimegal : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMEGAL>,
        comms::option::FieldsImpl<NavTimegalFields::All>,
        comms::option::MsgType<NavTimegal<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavTimegalFields::iTOW field
    ///     @li @b galTOW for @ref NavTimegalFields::galTOW field
    ///     @li @b fGalTOW for @ref NavTimegalFields::fGalTOW field
    ///     @li @b galWno for @ref NavTimegalFields::galWno field
    ///     @li @b leapS for @ref NavTimegalFields::leapS field
    ///     @li @b valid for @ref NavTimegalFields::validBits field
    ///     @li @b tAcc for @ref NavTimegalFields::tAcc field
    COMMS_MSG_FIELDS_ACCESS(iTOW, galTOW, fGalTOW, galWno, leapS, valid, tAcc);

    /// @brief Default constructor
    NavTimegal() = default;

    /// @brief Copy constructor
    NavTimegal(const NavTimegal&) = default;

    /// @brief Move constructor
    NavTimegal(NavTimegal&& other) = default;

    /// @brief Destructor
    ~NavTimegal() = default;

    /// @brief Copy assignment
    NavTimegal& operator=(const NavTimegal&) = default;

    /// @brief Move assignment
    NavTimegal& operator=(NavTimegal&&) = default;
};


}  // namespace message

}  // namespace ublox





