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
/// @brief Contains definition of NAV-AOPSTATUS (ublox-8) message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-AOPSTATUS (ublox-8) message fields.
/// @see NavAopstatusU8
struct NavAopstatusU8Fields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "aopCfg" field.
    struct aopCfg : public
        field::common::X1T<comms::option::BitmaskReservedBits<0xfe, 0> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(useAOP);
    };

    /// @brief Definition of "status" field.
    using status = field::common::U1;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        aopCfg,
        status,
        reserved1,
        reserved2,
        reserved3
    >;
};

/// @brief Definition of NAV-AOPSTATUS (ublox-8) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavAopstatusU8Fields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavAopstatusU8 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_AOPSTATUS>,
        comms::option::FieldsImpl<NavAopstatusU8Fields::All>,
        comms::option::MsgType<NavAopstatusU8<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_AOPSTATUS>,
        comms::option::FieldsImpl<NavAopstatusU8Fields::All>,
        comms::option::MsgType<NavAopstatusU8<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavAopstatusU8Fields::iTOW field
    ///     @li @b aopCfg for @ref NavAopstatusU8Fields::aopCfg field
    ///     @li @b status for @ref NavAopstatusU8Fields::status field
    ///     @li @b reserved1 for @ref NavAopstatusU8Fields::reserved1 field
    ///     @li @b reserved2 for @ref NavAopstatusU8Fields::reserved2 field
    ///     @li @b reserved3 for @ref NavAopstatusU8Fields::reserved3 field
    COMMS_MSG_FIELDS_ACCESS(
        iTOW,
        aopCfg,
        status,
        reserved1,
        reserved2,
        reserved3
    );

    /// @brief Default constructor
    NavAopstatusU8() = default;

    /// @brief Copy constructor
    NavAopstatusU8(const NavAopstatusU8&) = default;

    /// @brief Move constructor
    NavAopstatusU8(NavAopstatusU8&& other) = default;

    /// @brief Destructor
    virtual ~NavAopstatusU8() = default;

    /// @brief Copy assignment
    NavAopstatusU8& operator=(const NavAopstatusU8&) = default;

    /// @brief Move assignment
    NavAopstatusU8& operator=(NavAopstatusU8&&) = default;
};


}  // namespace message

}  // namespace ublox





