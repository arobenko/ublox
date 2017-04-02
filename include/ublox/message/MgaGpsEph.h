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
/// @brief Contains definition of MGA-GPS-EPH message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-GPS-EPH message fields.
/// @see MgaGpsEph
struct MgaGpsEphFields
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

/// @brief Definition of MGA-GPS-EPH message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaGpsEphFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaGpsEph : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_GPS>,
        comms::option::FieldsImpl<MgaGpsEphFields::All>,
        comms::option::MsgType<MgaGpsEph<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaGpsEphFields::type field
    ///     @li @b version for @ref MgaGpsEphFields::version field
    ///     @li @b svId for @ref MgaGpsEphFields::svId field
    ///     @li @b reserved1 for @ref MgaGpsEphFields::reserved1 field
    ///     @li @b fitInterval for @ref MgaGpsEphFields::fitInterval field
    ///     @li @b uraIndex for @ref MgaGpsEphFields::uraIndex field
    ///     @li @b svHealth for @ref MgaGpsEphFields::svHealth field
    ///     @li @b tgd for @ref MgaGpsEphFields::tgd field
    ///     @li @b iodc for @ref MgaGpsEphFields::iodc field
    ///     @li @b toc for @ref MgaGpsEphFields::toc field
    ///     @li @b reserved2 for @ref MgaGpsEphFields::reserved2 field
    ///     @li @b af2 for @ref MgaGpsEphFields::af2 field
    ///     @li @b af1 for @ref MgaGpsEphFields::af1 field
    ///     @li @b af0 for @ref MgaGpsEphFields::af0 field
    ///     @li @b crs for @ref MgaGpsEphFields::crs field
    ///     @li @b deltaN for @ref MgaGpsEphFields::deltaN field
    ///     @li @b m0 for @ref MgaGpsEphFields::m0 field
    ///     @li @b cuc for @ref MgaGpsEphFields::cuc field
    ///     @li @b cus for @ref MgaGpsEphFields::cus field
    ///     @li @b e for @ref MgaGpsEphFields::e field
    ///     @li @b sqrtA for @ref MgaGpsEphFields::sqrtA field
    ///     @li @b toe for @ref MgaGpsEphFields::toe field
    ///     @li @b cic for @ref MgaGpsEphFields::cic field
    ///     @li @b omega0 for @ref MgaGpsEphFields::omega0 field
    ///     @li @b cis for @ref MgaGpsEphFields::cis field
    ///     @li @b crc for @ref MgaGpsEphFields::crc field
    ///     @li @b i0 for @ref MgaGpsEphFields::i0 field
    ///     @li @b omega for @ref MgaGpsEphFields::omega field
    ///     @li @b omegaDot for @ref MgaGpsEphFields::omegaDot field
    ///     @li @b idot for @ref MgaGpsEphFields::idot field
    ///     @li @b reserved3 for @ref MgaGpsEphFields::reserved3 field
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
    MgaGpsEph() = default;

    /// @brief Copy constructor
    MgaGpsEph(const MgaGpsEph&) = default;

    /// @brief Move constructor
    MgaGpsEph(MgaGpsEph&& other) = default;

    /// @brief Destructor
    ~MgaGpsEph() = default;

    /// @brief Copy assignment
    MgaGpsEph& operator=(const MgaGpsEph&) = default;

    /// @brief Move assignment
    MgaGpsEph& operator=(MgaGpsEph&&) = default;
};

}  // namespace message

}  // namespace ublox

