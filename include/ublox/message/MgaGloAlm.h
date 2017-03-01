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
/// @brief Contains definition of MGA-GLO-ALM message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-GLO-ALM message fields.
/// @see MgaGloAlm
struct MgaGloAlmFields
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

    /// @brief Definition of "N" field.
    using N = field::common::U2;

    /// @brief Definition of "M" field.
    using M = field::common::U1;

    /// @brief Definition of "C" field.
    using C = field::common::U1;

    /// @brief Definition of "tau" field.
    using tau = field::common::I2;

    /// @brief Definition of "epsilon" field.
    using epsilon = field::common::U2;

    /// @brief Definition of "lambda" field.
    using lambda = field::common::I4;

    /// @brief Definition of "deltaI" field.
    using deltaI = field::common::I4;

    /// @brief Definition of "tLambda" field.
    using tLambda = field::common::U4;

    /// @brief Definition of "deltaT" field.
    using deltaT = field::common::I4;

    /// @brief Definition of "deltaDT" field.
    using deltaDT = field::common::I1;

    /// @brief Definition of "H" field.
    using H = field::common::I1;

    /// @brief Definition of "omega" field.
    using omega = field::common::I2;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        svId,
        reserved1,
        N,
        M,
        C,
        tau,
        epsilon,
        lambda,
        deltaI,
        tLambda,
        deltaT,
        deltaDT,
        H,
        omega,
        reserved2
    >;
};

/// @brief Definition of MGA-GLO-ALM message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaGloAlmFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaGloAlm : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_GLO>,
        comms::option::FieldsImpl<MgaGloAlmFields::All>,
        comms::option::MsgType<MgaGloAlm<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaGloAlmFields::type field
    ///     @li @b version for @ref MgaGloAlmFields::version field
    ///     @li @b svId for @ref MgaGloAlmFields::svId field
    ///     @li @b reserved1 for @ref MgaGloAlmFields::reserved1 field
    ///     @li @b N for @ref MgaGloAlmFields::N field
    ///     @li @b M for @ref MgaGloAlmFields::M field
    ///     @li @b C for @ref MgaGloAlmFields::C field
    ///     @li @b tau for @ref MgaGloAlmFields::tau field
    ///     @li @b epsilon for @ref MgaGloAlmFields::epsilon field
    ///     @li @b lambda for @ref MgaGloAlmFields::lambda field
    ///     @li @b deltaI for @ref MgaGloAlmFields::deltaI field
    ///     @li @b tLambda for @ref MgaGloAlmFields::tLambda field
    ///     @li @b deltaT for @ref MgaGloAlmFields::deltaT field
    ///     @li @b deltaDT for @ref MgaGloAlmFields::deltaDT field
    ///     @li @b H for @ref MgaGloAlmFields::H field
    ///     @li @b omega for @ref MgaGloAlmFields::omega field
    ///     @li @b reserved2 for @ref MgaGloAlmFields::reserved2 field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        svId,
        reserved1,
        N,
        M,
        C,
        tau,
        epsilon,
        lambda,
        deltaI,
        tLambda,
        deltaT,
        deltaDT,
        H,
        omega,
        reserved2
    );

    /// @brief Default constructor
    MgaGloAlm() = default;

    /// @brief Copy constructor
    MgaGloAlm(const MgaGloAlm&) = default;

    /// @brief Move constructor
    MgaGloAlm(MgaGloAlm&& other) = default;

    /// @brief Destructor
    virtual ~MgaGloAlm() = default;

    /// @brief Copy assignment
    MgaGloAlm& operator=(const MgaGloAlm&) = default;

    /// @brief Move assignment
    MgaGloAlm& operator=(MgaGloAlm&&) = default;
};

}  // namespace message

}  // namespace ublox

