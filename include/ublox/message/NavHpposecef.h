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
/// @brief Contains definition of NAV-HPPOSECEF message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{
/// @brief Accumulates details of all the NAV-HPPOSECEF message fields.
/// @see NavHpposecef
struct NavHpposecefFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res3;

    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

    /// @brief Definition of "ecefX" field.
    using ecefX = field::nav::ecefX;

    /// @brief Definition of "ecefY" field.
    using ecefY = field::nav::ecefY;

    /// @brief Definition of "ecefZ" field.
    using ecefZ = field::nav::ecefZ;

    /// @brief Definition of "ecefXHp" field.
    using ecefXHp =
        field::common::I1T<
            comms::option::ScalingRatio<1, 10>,
            comms::option::UnitsMillimeters
        >;

    /// @brief Definition of "ecefYHp" field.
    using ecefYHp = ecefXHp;

    /// @brief Definition of "ecefZHp" field.
    using ecefZHp = ecefXHp;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res1;

    /// @brief Definition of "pAcc" field.
    using pAcc =
        field::common::U4T<
            comms::option::UnitsMillimeters,
            comms::option::ScalingRatio<1, 10>
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        reserved1,
        iTOW,
        ecefX,
        ecefY,
        ecefZ,
        ecefXHp,
        ecefYHp,
        ecefZHp,
        reserved2,
        pAcc
    >;
};

/// @brief Definition of NAV-HPPOSECEF message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavHpposecefFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavHpposecef : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_HPPOSECEF>,
        comms::option::FieldsImpl<NavHpposecefFields::All>,
        comms::option::MsgType<NavHpposecef<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref NavHpposecefFields::version field
    ///     @li @b reserved1 for @ref NavHpposecefFields::reserved1 field
    ///     @li @b iTOW for @ref NavHpposecefFields::iTOW field
    ///     @li @b ecefX for @ref NavHpposecefFields::ecefX field
    ///     @li @b ecefY for @ref NavHpposecefFields::ecefY field
    ///     @li @b ecefZ for @ref NavHpposecefFields::ecefZ field
    ///     @li @b ecefXHp for @ref NavHpposecefFields::ecefXHp field
    ///     @li @b ecefYHp for @ref NavHpposecefFields::ecefYHp field
    ///     @li @b ecefZHp for @ref NavHpposecefFields::ecefZHp field
    ///     @li @b reserved2 for @ref NavHpposecefFields::reserved2 field
    ///     @li @b pAcc for @ref NavHpposecefFields::pAcc field
    COMMS_MSG_FIELDS_ACCESS(
        version,
        reserved1,
        iTOW,
        ecefX,
        ecefY,
        ecefZ,
        ecefXHp,
        ecefYHp,
        ecefZHp,
        reserved2,
        pAcc
    );

    /// @brief Default constructor
    NavHpposecef() = default;

    /// @brief Copy constructor
    NavHpposecef(const NavHpposecef&) = default;

    /// @brief Move constructor
    NavHpposecef(NavHpposecef&& other) = default;

    /// @brief Destructor
    ~NavHpposecef() = default;

    /// @brief Copy assignment
    NavHpposecef& operator=(const NavHpposecef&) = default;

    /// @brief Move assignment
    NavHpposecef& operator=(NavHpposecef&&) = default;
};


}  // namespace message

}  // namespace ublox





