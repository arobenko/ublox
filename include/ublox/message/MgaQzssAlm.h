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
/// @brief Contains definition of MGA-QZSS-ALM message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-QZSS-ALM message fields.
/// @see MgaQzssAlm
struct MgaQzssAlmFields
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

    /// @brief Definition of "svHealth" field.
    using svHealth = field::common::U1;

    /// @brief Definition of "e" field.
    using e = field::common::U2;

    /// @brief Definition of "almWNa" field.
    using almWNa = field::common::U1;

    /// @brief Definition of "toa" field.
    using toa = field::common::U1;

    /// @brief Definition of "deltaI" field.
    using deltaI = field::common::I2;

    /// @brief Definition of "omegaDot" field.
    using omegaDot = field::common::I2;

    /// @brief Definition of "sqrtA" field.
    using sqrtA = field::common::U4;

    /// @brief Definition of "omega0" field.
    using omega0 = field::common::I4;

    /// @brief Definition of "omega" field.
    using omega = field::common::I4;

    /// @brief Definition of "m0" field.
    using m0 = field::common::I4;

    /// @brief Definition of "af0" field.
    using af0 = field::common::I2;

    /// @brief Definition of "af1" field.
    using af1 = field::common::I2;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        svId,
        svHealth,
        e,
        almWNa,
        toa,
        deltaI,
        omegaDot,
        sqrtA,
        omega0,
        omega,
        m0,
        af0,
        af1,
        reserved1
    >;
};

/// @brief Definition of MGA-QZSS-ALM message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaQzssAlmFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaQzssAlm : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_QZSS>,
        comms::option::FieldsImpl<MgaQzssAlmFields::All>,
        comms::option::MsgType<MgaQzssAlm<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaQzssAlmFields::type field
    ///     @li @b version for @ref MgaQzssAlmFields::version field
    ///     @li @b svId for @ref MgaQzssAlmFields::svId field
    ///     @li @b svHealth for @ref MgaQzssAlmFields::svHealth field
    ///     @li @b e for @ref MgaQzssAlmFields::e field
    ///     @li @b almWNa for @ref MgaQzssAlmFields::almWNa field
    ///     @li @b toa for @ref MgaQzssAlmFields::toa field
    ///     @li @b deltaI for @ref MgaQzssAlmFields::deltaI field
    ///     @li @b omegaDot for @ref MgaQzssAlmFields::omegaDot field
    ///     @li @b sqrtA for @ref MgaQzssAlmFields::sqrtA field
    ///     @li @b omega0 for @ref MgaQzssAlmFields::omega0 field
    ///     @li @b m0 for @ref MgaQzssAlmFields::m0 field
    ///     @li @b af0 for @ref MgaQzssAlmFields::af0 field
    ///     @li @b af1 for @ref MgaQzssAlmFields::af1 field
    ///     @li @b reserved1 for @ref MgaQzssAlmFields::reserved1 field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        svId,
        svHealth,
        e,
        almWNa,
        toa,
        deltaI,
        omegaDot,
        sqrtA,
        omega0,
        omega,
        m0,
        af0,
        af1,
        reserved1
    );

    /// @brief Default constructor
    MgaQzssAlm() = default;

    /// @brief Copy constructor
    MgaQzssAlm(const MgaQzssAlm&) = default;

    /// @brief Move constructor
    MgaQzssAlm(MgaQzssAlm&& other) = default;

    /// @brief Destructor
    ~MgaQzssAlm() = default;

    /// @brief Copy assignment
    MgaQzssAlm& operator=(const MgaQzssAlm&) = default;

    /// @brief Move assignment
    MgaQzssAlm& operator=(MgaQzssAlm&&) = default;
};

}  // namespace message

}  // namespace ublox

