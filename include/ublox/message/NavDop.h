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
/// @brief Contains definition of NAV-DOP message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-DOP message fields.
/// @see NavDop
struct NavDopFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "gDOP" field.
    using gDOP = field::nav::pDOP;

    /// @brief Definition of "pDOP" field.
    using pDOP = field::nav::pDOP;

    /// @brief Definition of "tDOP" field.
    using tDOP = field::nav::pDOP;

    /// @brief Definition of "vDOP" field.
    using vDOP = field::nav::pDOP;

    /// @brief Definition of "hDOP" field.
    using hDOP = field::nav::pDOP;

    /// @brief Definition of "nDOP" field.
    using nDOP = field::nav::pDOP;

    /// @brief Definition of "eDOP" field.
    using eDOP = field::nav::pDOP;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        gDOP,
        pDOP,
        tDOP,
        vDOP,
        hDOP,
        nDOP,
        eDOP
    >;
};

/// @brief Definition of NAV-DOP message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavDopFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavDop : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_DOP>,
        comms::option::FieldsImpl<NavDopFields::All>,
        comms::option::MsgType<NavDop<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_DOP>,
        comms::option::FieldsImpl<NavDopFields::All>,
        comms::option::MsgType<NavDop<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavDopFields::iTOW field
    ///     @li @b gDOP for @ref NavDopFields::gDOP field
    ///     @li @b pDOP for @ref NavDopFields::pDOP field
    ///     @li @b tDOP for @ref NavDopFields::tDOP field
    ///     @li @b vDOP for @ref NavDopFields::vDOP field
    ///     @li @b hDOP for @ref NavDopFields::hDOP field
    ///     @li @b nDOP for @ref NavDopFields::nDOP field
    ///     @li @b eDOP for @ref NavDopFields::eDOP field
    COMMS_MSG_FIELDS_ACCESS(Base, iTOW, gDOP, pDOP, tDOP, vDOP, hDOP, nDOP, eDOP);

    /// @brief Default constructor
    NavDop() = default;

    /// @brief Copy constructor
    NavDop(const NavDop&) = default;

    /// @brief Move constructor
    NavDop(NavDop&& other) = default;

    /// @brief Destructor
    virtual ~NavDop() = default;

    /// @brief Copy assignment
    NavDop& operator=(const NavDop&) = default;

    /// @brief Move assignment
    NavDop& operator=(NavDop&&) = default;
};


}  // namespace message

}  // namespace ublox





