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
/// @brief Contains definition of MGA-GAL-ALM message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-GAL-ALM message fields.
/// @see MgaGalAlm
struct MgaGalAlmFields
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

    /// @brief Definition of "ioda" field.
    using ioda = field::common::U1;

    /// @brief Definition of "almWNa" field.
    using almWNa = field::common::U1;

    /// @brief Definition of "toa" field.
    using toa = field::common::U2;

    /// @brief Definition of "deltaSqrtA" field.
    using deltaSqrtA = field::common::I2;

    /// @brief Definition of "e" field.
    using e = field::common::U2;

    /// @brief Definition of "deltaI" field.
    using deltaI = field::common::I2;

    /// @brief Definition of "omega0" field.
    using omega0 = field::common::I2;

    /// @brief Definition of "omegaDot" field.
    using omegaDot = field::common::I2;

    /// @brief Definition of "omega" field.
    using omega = field::common::I2;

    /// @brief Definition of "m0" field.
    using m0 = field::common::I2;

    /// @brief Definition of "af0" field.
    using af0 = field::common::I2;

    /// @brief Definition of "af1" field.
    using af1 = field::common::I2;

    /// @brief Definition of "healthE1B" field.
    using healthE1B = field::common::U1;

    /// @brief Definition of "healthE5b" field.
    using healthE5b = field::common::U1;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        svId,
        reserved1,
        ioda,
        almWNa,
        toa,
        deltaSqrtA,
        e,
        deltaI,
        omega0,
        omegaDot,
        omega,
        m0,
        af0,
        af1,
        healthE1B,
        healthE5b,
        reserved2
    >;
};

/// @brief Definition of MGA-GAL-ALM message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaGalAlmFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaGalAlm : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_GAL>,
        comms::option::FieldsImpl<MgaGalAlmFields::All>,
        comms::option::MsgType<MgaGalAlm<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaGalAlmFields::type field
    ///     @li @b version for @ref MgaGalAlmFields::version field
    ///     @li @b svId for @ref MgaGalAlmFields::svId field
    ///     @li @b reserved1 for @ref MgaGalAlmFields::reserved1 field
    ///     @li @b ioda for @ref MgaGalAlmFields::ioda field
    ///     @li @b almWNa for @ref MgaGalAlmFields::almWNa field
    ///     @li @b toa for @ref MgaGalAlmFields::toa field
    ///     @li @b deltaSqrtA for @ref MgaGalAlmFields::deltaSqrtA field
    ///     @li @b e for @ref MgaGalAlmFields::e field
    ///     @li @b deltaI for @ref MgaGalAlmFields::deltaI field
    ///     @li @b omega0 for @ref MgaGalAlmFields::omega0 field
    ///     @li @b omegaDot for @ref MgaGalAlmFields::omegaDot field
    ///     @li @b omega for @ref MgaGalAlmFields::omega field
    ///     @li @b m0 for @ref MgaGalAlmFields::m0 field
    ///     @li @b af0 for @ref MgaGalAlmFields::af0 field
    ///     @li @b af1 for @ref MgaGalAlmFields::af1 field
    ///     @li @b healthE1B for @ref MgaGalAlmFields::healthE1B field
    ///     @li @b healthE5b for @ref MgaGalAlmFields::healthE5b field
    ///     @li @b reserved2 for @ref MgaGalAlmFields::reserved2 field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        svId,
        reserved1,
        ioda,
        almWNa,
        toa,
        deltaSqrtA,
        e,
        deltaI,
        omega0,
        omegaDot,
        omega,
        m0,
        af0,
        af1,
        healthE1B,
        healthE5b,
        reserved2
    );

    /// @brief Default constructor
    MgaGalAlm() = default;

    /// @brief Copy constructor
    MgaGalAlm(const MgaGalAlm&) = default;

    /// @brief Move constructor
    MgaGalAlm(MgaGalAlm&& other) = default;

    /// @brief Destructor
    ~MgaGalAlm() = default;

    /// @brief Copy assignment
    MgaGalAlm& operator=(const MgaGalAlm&) = default;

    /// @brief Move assignment
    MgaGalAlm& operator=(MgaGalAlm&&) = default;
};

}  // namespace message

}  // namespace ublox

