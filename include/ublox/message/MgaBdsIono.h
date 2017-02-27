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
/// @brief Contains definition of MGA-BDS-IONO message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-BDS-IONO message fields.
/// @see MgaBdsIono
struct MgaBdsIonoFields
{
    /// @brief Definition of "type" field.
    using type  =
    field::common::U1T<
        comms::option::ValidNumValueRange<6, 6>,
        comms::option::DefaultNumValue<6>,
        comms::option::FailOnInvalid
    >;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "alpha0" field.
    using alpha0 = field::common::I1;

    /// @brief Definition of "alpha1" field.
    using alpha1 = field::common::I1;

    /// @brief Definition of "alpha2" field.
    using alpha2 = field::common::I1;

    /// @brief Definition of "alpha3" field.
    using alpha3 = field::common::I1;

    /// @brief Definition of "beta0" field.
    using beta0 = field::common::I1;

    /// @brief Definition of "beta1" field.
    using beta1 = field::common::I1;

    /// @brief Definition of "beta2" field.
    using beta2 = field::common::I1;

    /// @brief Definition of "beta3" field.
    using beta3 = field::common::I1;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;


    // TODO
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        reserved1,
        alpha0,
        alpha1,
        alpha2,
        alpha3,
        beta0,
        beta1,
        beta2,
        beta3,
        reserved2
    >;
};

/// @brief Definition of MGA-BDS-IONO message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaBdsIonoFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaBdsIono : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_BDS>,
        comms::option::FieldsImpl<MgaBdsIonoFields::All>,
        comms::option::MsgType<MgaBdsIono<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaBdsIonoFields::type field
    ///     @li @b version for @ref MgaBdsIonoFields::version field
    ///     @li @b reserved1 for @ref MgaBdsIonoFields::reserved1 field
    ///     @li @b alpha0 for @ref MgaBdsIonoFields::alpha0 field
    ///     @li @b alpha1 for @ref MgaBdsIonoFields::alpha1 field
    ///     @li @b alpha2 for @ref MgaBdsIonoFields::alpha2 field
    ///     @li @b alpha3 for @ref MgaBdsIonoFields::alpha3 field
    ///     @li @b beta0 for @ref MgaBdsIonoFields::beta0 field
    ///     @li @b beta1 for @ref MgaBdsIonoFields::beta1 field
    ///     @li @b beta2 for @ref MgaBdsIonoFields::beta2 field
    ///     @li @b beta3 for @ref MgaBdsIonoFields::beta3 field
    ///     @li @b reserved2 for @ref MgaBdsIonoFields::reserved2 field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        reserved1,
        alpha0,
        alpha1,
        alpha2,
        alpha3,
        beta0,
        beta1,
        beta2,
        beta3,
        reserved2
    );

    /// @brief Default constructor
    MgaBdsIono() = default;

    /// @brief Copy constructor
    MgaBdsIono(const MgaBdsIono&) = default;

    /// @brief Move constructor
    MgaBdsIono(MgaBdsIono&& other) = default;

    /// @brief Destructor
    virtual ~MgaBdsIono() = default;

    /// @brief Copy assignment
    MgaBdsIono& operator=(const MgaBdsIono&) = default;

    /// @brief Move assignment
    MgaBdsIono& operator=(MgaBdsIono&&) = default;
};

}  // namespace message

}  // namespace ublox

