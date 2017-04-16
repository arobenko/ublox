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
/// @brief Contains definition of MGA-GPS-UTC message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-GPS-UTC message fields.
/// @see MgaGpsUtc
struct MgaGpsUtcFields
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

    /// @brief Definition of "utcA0" field.
    using utcA0 =
        field::common::I4T<
            comms::option::ScalingRatio<1, 0x40000000>,
            comms::option::UnitsSeconds
        >;

    /// @brief Definition of "utcA1" field.
    using utcA1 =
        field::common::I4T<
            comms::option::ScalingRatio<1, 0x4000000000000ULL>,
            comms::option::UnitsSeconds
        >;

    /// @brief Definition of "utcDtLS" field.
    using utcDtLS = field::common::I1T<comms::option::UnitsSeconds>;

    /// @brief Definition of "utcTot" field.
    using utcTot =
        field::common::U1T<
            comms::option::ScalingRatio<0x1000, 1>,
            comms::option::UnitsSeconds
        >;

    /// @brief Definition of "utcWNt" field.
    using utcWNt = field::common::U1T<comms::option::UnitsWeeks>;

    /// @brief Definition of "utcWNlsf" field.
    using utcWNlsf = field::common::U1T<comms::option::UnitsWeeks>;

    /// @brief Definition of "utcDn" field.
    using utcDn = field::common::U1T<comms::option::UnitsDays>;

    /// @brief Definition of "utcDtLSF" field.
    using utcDtLSF = field::common::I1T<comms::option::UnitsSeconds>;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res2;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        reserved1,
        utcA0,
        utcA1,
        utcDtLS,
        utcTot,
        utcWNt,
        utcWNlsf,
        utcDn,
        utcDtLSF,
        reserved2
    >;
};

/// @brief Definition of MGA-GPS-UTC message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaGpsUtcFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaGpsUtc : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_GPS>,
        comms::option::FieldsImpl<MgaGpsUtcFields::All>,
        comms::option::MsgType<MgaGpsUtc<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaGpsUtcFields::type field
    ///     @li @b version for @ref MgaGpsUtcFields::version field
    ///     @li @b reserved1 for @ref MgaGpsUtcFields::reserved1 field
    ///     @li @b utcA0 for @ref MgaGpsUtcFields::utcA0 field
    ///     @li @b utcA1 for @ref MgaGpsUtcFields::utcA1 field
    ///     @li @b utcDtLS for @ref MgaGpsUtcFields::utcDtLS field
    ///     @li @b utcTot for @ref MgaGpsUtcFields::utcTot field
    ///     @li @b utcWNt for @ref MgaGpsUtcFields::utcWNt field
    ///     @li @b utcWNlsf for @ref MgaGpsUtcFields::utcWNlsf field
    ///     @li @b utcDn for @ref MgaGpsUtcFields::utcDn field
    ///     @li @b utcDtLSF for @ref MgaGpsUtcFields::utcDtLSF field
    ///     @li @b reserved2 for @ref MgaGpsUtcFields::reserved2 field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        reserved1,
        utcA0,
        utcA1,
        utcDtLS,
        utcTot,
        utcWNt,
        utcWNlsf,
        utcDn,
        utcDtLSF,
        reserved2
    );

    /// @brief Default constructor
    MgaGpsUtc() = default;

    /// @brief Copy constructor
    MgaGpsUtc(const MgaGpsUtc&) = default;

    /// @brief Move constructor
    MgaGpsUtc(MgaGpsUtc&& other) = default;

    /// @brief Destructor
    ~MgaGpsUtc() = default;

    /// @brief Copy assignment
    MgaGpsUtc& operator=(const MgaGpsUtc&) = default;

    /// @brief Move assignment
    MgaGpsUtc& operator=(MgaGpsUtc&&) = default;
};

}  // namespace message

}  // namespace ublox

