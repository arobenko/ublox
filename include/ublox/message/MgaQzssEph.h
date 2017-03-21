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
/// @brief Contains definition of MGA-QZSS-EPH message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-QZSS-EPH message fields.
/// @see MgaQzssEph
struct MgaQzssEphFields
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

    /// @brief Definition of "fitInterval" field.
    using fitInterval = field::common::U1;

    /// @brief Definition of "uraIndex" field.
    using uraIndex = field::common::U1;

    /// @brief Definition of "svHealth" field.
    using svHealth = field::common::U1;

    /// @brief Definition of "tgd" field.
    using tgd = field::common::I1;

    /// @brief Definition of "iodc" field.
    using iodc = field::common::U2;

    /// @brief Definition of "toc" field.
    using toc = field::common::U2;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res1;

    /// @brief Definition of "af2" field.
    using af2 = field::common::I1;

    /// @brief Definition of "af1" field.
    using af1 = field::common::I2;

    /// @brief Definition of "af0" field.
    using af0 = field::common::I4;

    /// @brief Definition of "crs" field.
    using crs = field::common::I2;

    /// @brief Definition of "deltaN" field.
    using deltaN = field::common::I2;

    /// @brief Definition of "m0" field.
    using m0 = field::common::I4;

    /// @brief Definition of "cuc" field.
    using cuc = field::common::I2;

    /// @brief Definition of "cus" field.
    using cus = field::common::I2;

    /// @brief Definition of "e" field.
    using e = field::common::U4;

    /// @brief Definition of "sqrtA" field.
    using sqrtA = field::common::U4;

    /// @brief Definition of "toe" field.
    using toe = field::common::U2;

    /// @brief Definition of "cic" field.
    using cic = field::common::I2;

    /// @brief Definition of "omega0" field.
    using omega0 = field::common::I4;

    /// @brief Definition of "cis" field.
    using cis = field::common::I2;

    /// @brief Definition of "crc" field.
    using crc = field::common::I2;

    /// @brief Definition of "i0" field.
    using i0 = field::common::I4;

    /// @brief Definition of "omega" field.
    using omega = field::common::I4;

    /// @brief Definition of "omegaDot" field.
    using omegaDot = field::common::I4;

    /// @brief Definition of "idot" field.
    using idot = field::common::I2;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res2;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        svId,
        reserved1,
        fitInterval,
        uraIndex,
        svHealth,
        tgd,
        iodc,
        toc,
        reserved2,
        af2,
        af1,
        af0,
        crs,
        deltaN,
        m0,
        cuc,
        cus,
        e,
        sqrtA,
        toe,
        cic,
        omega0,
        cis,
        crc,
        i0,
        omega,
        omegaDot,
        idot,
        reserved3
    >;
};

/// @brief Definition of MGA-QZSS-EPH message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaQzssEphFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaQzssEph : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_QZSS>,
        comms::option::FieldsImpl<MgaQzssEphFields::All>,
        comms::option::MsgType<MgaQzssEph<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaQzssEphFields::type field
    ///     @li @b version for @ref MgaQzssEphFields::version field
    ///     @li @b svId for @ref MgaQzssEphFields::svId field
    ///     @li @b reserved1 for @ref MgaQzssEphFields::reserved1 field
    ///     @li @b fitInterval for @ref MgaQzssEphFields::fitInterval field
    ///     @li @b uraIndex for @ref MgaQzssEphFields::uraIndex field
    ///     @li @b svHealth for @ref MgaQzssEphFields::svHealth field
    ///     @li @b tgd for @ref MgaQzssEphFields::tgd field
    ///     @li @b iodc for @ref MgaQzssEphFields::iodc field
    ///     @li @b toc for @ref MgaQzssEphFields::toc field
    ///     @li @b reserved2 for @ref MgaQzssEphFields::reserved2 field
    ///     @li @b af2 for @ref MgaQzssEphFields::af2 field
    ///     @li @b af1 for @ref MgaQzssEphFields::af1 field
    ///     @li @b af0 for @ref MgaQzssEphFields::af0 field
    ///     @li @b crs for @ref MgaQzssEphFields::crs field
    ///     @li @b deltaN for @ref MgaQzssEphFields::deltaN field
    ///     @li @b m0 for @ref MgaQzssEphFields::m0 field
    ///     @li @b cuc for @ref MgaQzssEphFields::cuc field
    ///     @li @b cus for @ref MgaQzssEphFields::cus field
    ///     @li @b e for @ref MgaQzssEphFields::e field
    ///     @li @b sqrtA for @ref MgaQzssEphFields::sqrtA field
    ///     @li @b toe for @ref MgaQzssEphFields::toe field
    ///     @li @b cic for @ref MgaQzssEphFields::cic field
    ///     @li @b omega0 for @ref MgaQzssEphFields::omega0 field
    ///     @li @b cis for @ref MgaQzssEphFields::cis field
    ///     @li @b crc for @ref MgaQzssEphFields::crc field
    ///     @li @b i0 for @ref MgaQzssEphFields::i0 field
    ///     @li @b omega for @ref MgaQzssEphFields::omega field
    ///     @li @b omegaDot for @ref MgaQzssEphFields::omegaDot field
    ///     @li @b idot for @ref MgaQzssEphFields::idot field
    ///     @li @b reserved3 for @ref MgaQzssEphFields::reserved3 field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        svId,
        reserved1,
        fitInterval,
        uraIndex,
        svHealth,
        tgd,
        iodc,
        toc,
        reserved2,
        af2,
        af1,
        af0,
        crs,
        deltaN,
        m0,
        cuc,
        cus,
        e,
        sqrtA,
        toe,
        cic,
        omega0,
        cis,
        crc,
        i0,
        omega,
        omegaDot,
        idot,
        reserved3
    );

    /// @brief Default constructor
    MgaQzssEph() = default;

    /// @brief Copy constructor
    MgaQzssEph(const MgaQzssEph&) = default;

    /// @brief Move constructor
    MgaQzssEph(MgaQzssEph&& other) = default;

    /// @brief Destructor
    ~MgaQzssEph() = default;

    /// @brief Copy assignment
    MgaQzssEph& operator=(const MgaQzssEph&) = default;

    /// @brief Move assignment
    MgaQzssEph& operator=(MgaQzssEph&&) = default;
};

}  // namespace message

}  // namespace ublox

