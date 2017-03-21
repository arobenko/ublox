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
/// @brief Contains definition of MGA-GLO-EPH message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-GLO-EPH message fields.
/// @see MgaGloEph
struct MgaGloEphFields
{
    /// @brief Definition of "type" field.
    using type  =
    field::common::U1T<
        comms::option::ValidNumValueRange<1, 1>,
        comms::option::DefaultNumValue<1>,
        comms::option::FailOnInvalid<>
    >;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "svId" field.
    using svId = field::common::U1;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "FT" field.
    using FT = field::common::U1;

    /// @brief Definition of "B" field.
    using B = field::common::U1;

    /// @brief Definition of "M" field.
    using M = field::common::U1;

    /// @brief Definition of "H" field.
    using H = field::common::I1;

    /// @brief Definition of "x" field.
    using x = field::common::I4;

    /// @brief Definition of "y" field.
    using y = field::common::I4;

    /// @brief Definition of "z" field.
    using z = field::common::I4;

    /// @brief Definition of "dx" field.
    using dx = field::common::I4;

    /// @brief Definition of "dy" field.
    using dy = field::common::I4;

    /// @brief Definition of "dz" field.
    using dz = field::common::I4;

    /// @brief Definition of "ddx" field.
    using ddx = field::common::I1;

    /// @brief Definition of "ddy" field.
    using ddy = field::common::I1;

    /// @brief Definition of "ddz" field.
    using ddz = field::common::I1;

    /// @brief Definition of "tb" field.
    using tb = field::common::U1;

    /// @brief Definition of "gamma" field.
    using gamma = field::common::I2;

    /// @brief Definition of "E" field.
    using E = field::common::U1;

    /// @brief Definition of "deltaTau" field.
    using deltaTau = field::common::I1;

    /// @brief Definition of "tau" field.
    using tau = field::common::I4;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        svId,
        reserved1,
        FT,
        B,
        M,
        H,
        x,
        y,
        z,
        dx,
        dy,
        dz,
        ddx,
        ddy,
        ddz,
        tb,
        gamma,
        E,
        deltaTau,
        tau,
        reserved2
    >;
};

/// @brief Definition of MGA-GLO-EPH message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaGloEphFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaGloEph : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_GLO>,
        comms::option::FieldsImpl<MgaGloEphFields::All>,
        comms::option::MsgType<MgaGloEph<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaGloEphFields::type field
    ///     @li @b version for @ref MgaGloEphFields::version field
    ///     @li @b svId for @ref MgaGloEphFields::svId field
    ///     @li @b reserved1 for @ref MgaGloEphFields::reserved1 field
    ///     @li @b FT for @ref MgaGloEphFields::FT field
    ///     @li @b B for @ref MgaGloEphFields::B field
    ///     @li @b M for @ref MgaGloEphFields::M field
    ///     @li @b H for @ref MgaGloEphFields::H field
    ///     @li @b x for @ref MgaGloEphFields::x field
    ///     @li @b y for @ref MgaGloEphFields::y field
    ///     @li @b z for @ref MgaGloEphFields::z field
    ///     @li @b dx for @ref MgaGloEphFields::dx field
    ///     @li @b dy for @ref MgaGloEphFields::dy field
    ///     @li @b dz for @ref MgaGloEphFields::dz field
    ///     @li @b ddx for @ref MgaGloEphFields::ddx field
    ///     @li @b ddy for @ref MgaGloEphFields::ddy field
    ///     @li @b ddz for @ref MgaGloEphFields::ddz field
    ///     @li @b tb for @ref MgaGloEphFields::tb field
    ///     @li @b gamma for @ref MgaGloEphFields::gamma field
    ///     @li @b E for @ref MgaGloEphFields::E field
    ///     @li @b deltaTau for @ref MgaGloEphFields::deltaTau field
    ///     @li @b tau for @ref MgaGloEphFields::tau field
    ///     @li @b reserved2 for @ref MgaGloEphFields::reserved2 field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        svId,
        reserved1,
        FT,
        B,
        M,
        H,
        x,
        y,
        z,
        dx,
        dy,
        dz,
        ddx,
        ddy,
        ddz,
        tb,
        gamma,
        E,
        deltaTau,
        tau,
        reserved2
    );

    /// @brief Default constructor
    MgaGloEph() = default;

    /// @brief Copy constructor
    MgaGloEph(const MgaGloEph&) = default;

    /// @brief Move constructor
    MgaGloEph(MgaGloEph&& other) = default;

    /// @brief Destructor
    ~MgaGloEph() = default;

    /// @brief Copy assignment
    MgaGloEph& operator=(const MgaGloEph&) = default;

    /// @brief Move assignment
    MgaGloEph& operator=(MgaGloEph&&) = default;
};

}  // namespace message

}  // namespace ublox

