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
/// @brief Contains definition of MGA-BDS-ALM message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-BDS-ALM message fields.
/// @see MgaBdsAlm
struct MgaBdsAlmFields
{
    /// @brief Definition of "type" field.
    using type  =
    field::common::U1T<
        comms::option::ValidNumValueRange<2, 2>,
        comms::option::DefaultNumValue<2>,
        comms::option::FailOnInvalid
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

    /// @brief Definition of "Wna" field.
    using Wna = field::common::U1;

    /// @brief Definition of "toa" field.
    using toa = field::common::U1;

    /// @brief Definition of "deltaI" field.
    using deltaI = field::common::I2;

    /// @brief Definition of "sqrtA" field.
    using sqrtA = field::common::U4;

    /// @brief Definition of "e" field.
    using e = field::common::U4;

    /// @brief Definition of "omega" field.
    using omega = field::common::I4;

    /// @brief Definition of "M0" field.
    using M0 = field::common::I4;

    /// @brief Definition of "Omega0" field.
    using Omega0 = field::common::I4;

    /// @brief Definition of "OmegaDot" field.
    using OmegaDot = field::common::I4;

    /// @brief Definition of "a0" field.
    using a0 = field::common::I2;

    /// @brief Definition of "a1" field.
    using a1 = field::common::I2;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;


    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        svId,
        reserved1,
        Wna,
        toa,
        deltaI,
        sqrtA,
        e,
        omega,
        M0,
        Omega0,
        OmegaDot,
        a0,
        a1,
        reserved2
    >;
};

/// @brief Definition of MGA-BDS-ALM message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaBdsAlmFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaBdsAlm : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_BDS>,
        comms::option::FieldsImpl<MgaBdsAlmFields::All>,
        comms::option::MsgType<MgaBdsAlm<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaBdsAlmFields::type field
    ///     @li @b version for @ref MgaBdsAlmFields::version field
    ///     @li @b svId for @ref MgaBdsAlmFields::svId field
    ///     @li @b reserved1 for @ref MgaBdsAlmFields::reserved1 field
    ///     @li @b Wna for @ref MgaBdsAlmFields::Wna field
    ///     @li @b toa for @ref MgaBdsAlmFields::toa field
    ///     @li @b deltaI for @ref MgaBdsAlmFields::deltaI field
    ///     @li @b sqrtA for @ref MgaBdsAlmFields::sqrtA field
    ///     @li @b e for @ref MgaBdsAlmFields::e field
    ///     @li @b omega for @ref MgaBdsAlmFields::omega field
    ///     @li @b M0 for @ref MgaBdsAlmFields::M0 field
    ///     @li @b Omega0 for @ref MgaBdsAlmFields::Omega0 field
    ///     @li @b OmegaDot for @ref MgaBdsAlmFields::OmegaDot field
    ///     @li @b a0 for @ref MgaBdsAlmFields::a0 field
    ///     @li @b a1 for @ref MgaBdsAlmFields::a1 field
    ///     @li @b reserved2 for @ref MgaBdsAlmFields::reserved2 field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        svId,
        reserved1,
        Wna,
        toa,
        deltaI,
        sqrtA,
        e,
        omega,
        M0,
        Omega0,
        OmegaDot,
        a0,
        a1,
        reserved2
    );

    /// @brief Default constructor
    MgaBdsAlm() = default;

    /// @brief Copy constructor
    MgaBdsAlm(const MgaBdsAlm&) = default;

    /// @brief Move constructor
    MgaBdsAlm(MgaBdsAlm&& other) = default;

    /// @brief Destructor
    ~MgaBdsAlm() = default;

    /// @brief Copy assignment
    MgaBdsAlm& operator=(const MgaBdsAlm&) = default;

    /// @brief Move assignment
    MgaBdsAlm& operator=(MgaBdsAlm&&) = default;
};

}  // namespace message

}  // namespace ublox

