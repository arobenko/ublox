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
/// @brief Contains definition of MGA-GAL-EPH message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-GAL-EPH message fields.
/// @see MgaGalEph
struct MgaGalEphFields
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

    /// @brief Definition of "iodNav" field.
    using iodNav = field::common::U2;

    /// @brief Definition of "deltaN" field.
    using deltaN = field::common::I2;

    /// @brief Definition of "m0" field.
    using m0 = field::common::I4;

    /// @brief Definition of "e" field.
    using e = field::common::U4;

    /// @brief Definition of "sqrtA" field.
    using sqrtA = field::common::U4;

    /// @brief Definition of "omega0" field.
    using omega0 = field::common::I4;

    /// @brief Definition of "i0" field.
    using i0 = field::common::I4;

    /// @brief Definition of "omega" field.
    using omega = field::common::I4;

    /// @brief Definition of "omegaDot" field.
    using omegaDot = field::common::I4;

    /// @brief Definition of "iDot" field.
    using iDot = field::common::I2;

    /// @brief Definition of "cuc" field.
    using cuc = field::common::I2;

    /// @brief Definition of "cus" field.
    using cus = field::common::I2;

    /// @brief Definition of "crc" field.
    using crc = field::common::I2;

    /// @brief Definition of "crs" field.
    using crs = field::common::I2;

    /// @brief Definition of "cic" field.
    using cic = field::common::I2;

    /// @brief Definition of "cis" field.
    using cis = field::common::I2;

    /// @brief Definition of "toe" field.
    using toe = field::common::U2;

    /// @brief Definition of "af0" field.
    using af0 = field::common::I4;

    /// @brief Definition of "af1" field.
    using af1 = field::common::I4;

    /// @brief Definition of "af2" field.
    using af2 = field::common::I1;

    /// @brief Definition of "sisaIndexE1E5b" field.
    using sisaIndexE1E5b = field::common::U1;

    /// @brief Definition of "toc" field.
    using toc = field::common::U2;

    /// @brief Definition of "bgdE1E5b" field.
    using bgdE1E5b = field::common::I2;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res2;

    /// @brief Definition of "healthE1B" field.
    using healthE1B = field::common::U1;

    /// @brief Definition of "dataValidityE1B" field.
    using dataValidityE1B = field::common::U1;

    /// @brief Definition of "healthE5B" field.
    using healthE5B = field::common::U1;

    /// @brief Definition of "dataValidityE5B" field.
    using dataValidityE5B = field::common::U1;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        svId,
        reserved1,
        iodNav,
        deltaN,
        m0,
        e,
        sqrtA,
        omega0,
        i0,
        omega,
        omegaDot,
        iDot,
        cuc,
        cus,
        crc,
        crs,
        cic,
        cis,
        toe,
        af0,
        af1,
        af2,
        sisaIndexE1E5b,
        toc,
        bgdE1E5b,
        reserved2,
        healthE1B,
        dataValidityE1B,
        healthE5B,
        dataValidityE5B,
        reserved3
    >;
};

/// @brief Definition of MGA-GAL-EPH message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaGalEphFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaGalEph : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_GAL>,
        comms::option::FieldsImpl<MgaGalEphFields::All>,
        comms::option::MsgType<MgaGalEph<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaGalEphFields::type field
    ///     @li @b version for @ref MgaGalEphFields::version field
    ///     @li @b svId for @ref MgaGalEphFields::svId field
    ///     @li @b reserved1 for @ref MgaGalEphFields::reserved1 field
    ///     @li @b iodNav for @ref MgaGalEphFields::iodNav field
    ///     @li @b deltaN for @ref MgaGalEphFields::deltaN field
    ///     @li @b m0 for @ref MgaGalEphFields::m0 field
    ///     @li @b e for @ref MgaGalEphFields::e field
    ///     @li @b sqrtA for @ref MgaGalEphFields::sqrtA field
    ///     @li @b omega0 for @ref MgaGalEphFields::omega0 field
    ///     @li @b i0 for @ref MgaGalEphFields::i0 field
    ///     @li @b omega for @ref MgaGalEphFields::omega field
    ///     @li @b omegaDot for @ref MgaGalEphFields::omegaDot field
    ///     @li @b iDot for @ref MgaGalEphFields::iDot field
    ///     @li @b cuc for @ref MgaGalEphFields::cuc field
    ///     @li @b cus for @ref MgaGalEphFields::cus field
    ///     @li @b crc for @ref MgaGalEphFields::crc field
    ///     @li @b cic for @ref MgaGalEphFields::cic field
    ///     @li @b cis for @ref MgaGalEphFields::cis field
    ///     @li @b toe for @ref MgaGalEphFields::toe field
    ///     @li @b af0 for @ref MgaGalEphFields::af0 field
    ///     @li @b af1 for @ref MgaGalEphFields::af1 field
    ///     @li @b af2 for @ref MgaGalEphFields::af2 field
    ///     @li @b sisaIndexE1E5b for @ref MgaGalEphFields::sisaIndexE1E5b field
    ///     @li @b toc for @ref MgaGalEphFields::toc field
    ///     @li @b bgdE1E5b for @ref MgaGalEphFields::bgdE1E5b field
    ///     @li @b reserved2 for @ref MgaGalEphFields::reserved2 field
    ///     @li @b healthE1B for @ref MgaGalEphFields::healthE1B field
    ///     @li @b dataValidityE1B for @ref MgaGalEphFields::dataValidityE1B field
    ///     @li @b healthE5B for @ref MgaGalEphFields::healthE5B field
    ///     @li @b dataValidityE5B for @ref MgaGalEphFields::dataValidityE5B field
    ///     @li @b reserved3 for @ref MgaGalEphFields::reserved3 field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        svId,
        reserved1,
        iodNav,
        deltaN,
        m0,
        e,
        sqrtA,
        omega0,
        i0,
        omega,
        omegaDot,
        iDot,
        cuc,
        cus,
        crc,
        crs,
        cic,
        cis,
        toe,
        af0,
        af1,
        af2,
        sisaIndexE1E5b,
        toc,
        bgdE1E5b,
        reserved2,
        healthE1B,
        dataValidityE1B,
        healthE5B,
        dataValidityE5B,
        reserved3
    );

    /// @brief Default constructor
    MgaGalEph() = default;

    /// @brief Copy constructor
    MgaGalEph(const MgaGalEph&) = default;

    /// @brief Move constructor
    MgaGalEph(MgaGalEph&& other) = default;

    /// @brief Destructor
    ~MgaGalEph() = default;

    /// @brief Copy assignment
    MgaGalEph& operator=(const MgaGalEph&) = default;

    /// @brief Move assignment
    MgaGalEph& operator=(MgaGalEph&&) = default;
};

}  // namespace message

}  // namespace ublox

