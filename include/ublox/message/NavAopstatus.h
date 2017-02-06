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
/// @brief Contains definition of NAV-AOPSTATUS message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-AOPSTATUS message fields.
/// @see NavAopstatus
struct NavAopstatusFields
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

    /// @brief Definition of "reserved0" field.
    using reserved0 = field::common::res1;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "availGPS" field.
    using availGPS = field::common::X4;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        aopCfg,
        status,
        reserved0,
        reserved1,
        availGPS,
        reserved2,
        reserved3
    >;
};

/// @brief Definition of NAV-AOPSTATUS message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavAopstatusFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavAopstatus : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_AOPSTATUS>,
        comms::option::FieldsImpl<NavAopstatusFields::All>,
        comms::option::MsgType<NavAopstatus<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_AOPSTATUS>,
        comms::option::FieldsImpl<NavAopstatusFields::All>,
        comms::option::MsgType<NavAopstatus<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavAopstatusFields::iTOW field
    ///     @li @b aopCfg for @ref NavAopstatusFields::aopCfg field
    ///     @li @b status for @ref NavAopstatusFields::status field
    ///     @li @b reserved0 for @ref NavAopstatusFields::reserved0 field
    ///     @li @b reserved1 for @ref NavAopstatusFields::reserved1 field
    ///     @li @b availGPS for @ref NavAopstatusFields::availGPS field
    ///     @li @b reserved2 for @ref NavAopstatusFields::reserved2 field
    ///     @li @b reserved3 for @ref NavAopstatusFields::reserved3 field
    COMMS_MSG_FIELDS_ACCESS(
        iTOW,
        aopCfg,
        status,
        reserved0,
        reserved1,
        availGPS,
        reserved2,
        reserved3
    );

    /// @brief Default constructor
    NavAopstatus() = default;

    /// @brief Copy constructor
    NavAopstatus(const NavAopstatus&) = default;

    /// @brief Move constructor
    NavAopstatus(NavAopstatus&& other) = default;

    /// @brief Destructor
    virtual ~NavAopstatus() = default;

    /// @brief Copy assignment
    NavAopstatus& operator=(const NavAopstatus&) = default;

    /// @brief Move assignment
    NavAopstatus& operator=(NavAopstatus&&) = default;
};


}  // namespace message

}  // namespace ublox





