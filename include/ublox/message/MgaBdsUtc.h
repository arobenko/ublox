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
/// @brief Contains definition of MGA-BDS-UTC message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-BDS-UTC message fields.
/// @see MgaBdsUtc
struct MgaBdsUtcFields
{
    /// @brief Definition of "type" field.
    using type  =
    field::common::U1T<
        comms::option::ValidNumValueRange<5, 5>,
        comms::option::DefaultNumValue<5>,
        comms::option::FailOnInvalid<>
    >;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "a0UTC" field.
    using a0UTC =
        field::common::I4T<
            comms::option::ScalingRatio<1, 0x40000000>,
            comms::option::UnitsSeconds
        >;

    /// @brief Definition of "a1UTC" field.
    using a1UTC =
        field::common::I4T<
            comms::option::ScalingRatio<1, 0x4000000000000ULL>
        >;

    /// @brief Definition of "dtLS" field.
    using dtLS = field::common::I1T<comms::option::UnitsSeconds>;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res1;

    /// @brief Definition of "wnRec" field.
    using wnRec = field::common::U1T<comms::option::UnitsWeeks>;

    /// @brief Definition of "wnLSF" field.
    using wnLSF = field::common::U1T<comms::option::UnitsWeeks>;

    /// @brief Definition of "dN" field.
    using dN = field::common::U1T<comms::option::UnitsDays>;

    /// @brief Definition of "dtLSF" field.
    using dtLSF = field::common::I1T<comms::option::UnitsSeconds>;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res2;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        reserved1,
        a0UTC,
        a1UTC,
        dtLS,
        reserved2,
        wnRec,
        wnLSF,
        dN,
        dtLSF,
        reserved3
    >;
};

/// @brief Definition of MGA-BDS-UTC message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaBdsUtcFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaBdsUtc : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_BDS>,
        comms::option::FieldsImpl<MgaBdsUtcFields::All>,
        comms::option::MsgType<MgaBdsUtc<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaBdsUtcFields::type field
    ///     @li @b version for @ref MgaBdsUtcFields::version field
    ///     @li @b reserved1 for @ref MgaBdsUtcFields::reserved1 field
    ///     @li @b a0UTC for @ref MgaBdsUtcFields::a0UTC field
    ///     @li @b a1UTC for @ref MgaBdsUtcFields::a1UTC field
    ///     @li @b dtLS for @ref MgaBdsUtcFields::dtLS field
    ///     @li @b reserved2 for @ref MgaBdsUtcFields::reserved2 field
    ///     @li @b wnRec for @ref MgaBdsUtcFields::wnRec field
    ///     @li @b wnLSF for @ref MgaBdsUtcFields::wnLSF field
    ///     @li @b dN for @ref MgaBdsUtcFields::dN field
    ///     @li @b dtLSF for @ref MgaBdsUtcFields::dtLSF field
    ///     @li @b reserved3 for @ref MgaBdsUtcFields::reserved3 field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        reserved1,
        a0UTC,
        a1UTC,
        dtLS,
        reserved2,
        wnRec,
        wnLSF,
        dN,
        dtLSF,
        reserved3
    );

    /// @brief Default constructor
    MgaBdsUtc() = default;

    /// @brief Copy constructor
    MgaBdsUtc(const MgaBdsUtc&) = default;

    /// @brief Move constructor
    MgaBdsUtc(MgaBdsUtc&& other) = default;

    /// @brief Destructor
    ~MgaBdsUtc() = default;

    /// @brief Copy assignment
    MgaBdsUtc& operator=(const MgaBdsUtc&) = default;

    /// @brief Move assignment
    MgaBdsUtc& operator=(MgaBdsUtc&&) = default;
};

}  // namespace message

}  // namespace ublox

