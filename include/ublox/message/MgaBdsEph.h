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
/// @brief Contains definition of MGA-BDS-EPH message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-BDS-EPH message fields.
/// @see MgaBdsEph
struct MgaBdsEphFields
{
    /// @brief Definition of "type" field.
    using type  =
    field::common::U1T<
        comms::option::ValidNumValueRange<1, 1>,
        comms::option::DefaultNumValue<1>,
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

    /// @brief Definition of "SatH1" field.
    using SatH1 = field::common::U1;

    /// @brief Definition of "IODC" field.
    using IODC = field::common::U1;

    /// @brief Definition of "a2" field.
    using a2 = field::common::I2;

    /// @brief Definition of "a1" field.
    using a1 = field::common::I4;

    /// @brief Definition of "a0" field.
    using a0 = field::common::I4;

    /// @brief Definition of "toc" field.
    using toc = field::common::U4;

    /// @brief Definition of "TGD1" field.
    using TGD1 = field::common::I2;

    /// @brief Definition of "URAI" field.
    using URAI = field::common::U1;

    /// @brief Definition of "IODE" field.
    using IODE = field::common::U1;

    /// @brief Definition of "toe" field.
    using toe = field::common::U4;

    /// @brief Definition of "sqrtA" field.
    using sqrtA = field::common::U4;

    /// @brief Definition of "e" field.
    using e = field::common::U4;

    /// @brief Definition of "omega" field.
    using omega = field::common::I4;

    /// @brief Definition of "Deltan" field.
    using Deltan = field::common::I2;

    /// @brief Definition of "IDOT" field.
    using IDOT = field::common::I2;

    /// @brief Definition of "M0" field.
    using M0 = field::common::I4;

    /// @brief Definition of "Omega0" field.
    using Omega0 = field::common::I4;

    /// @brief Definition of "OmegaDot" field.
    using OmegaDot = field::common::I4;

    /// @brief Definition of "i0" field.
    using i0 = field::common::I4;

    /// @brief Definition of "Cuc" field.
    using Cuc = field::common::I4;

    /// @brief Definition of "Cus" field.
    using Cus = field::common::I4;

    /// @brief Definition of "Crc" field.
    using Crc = field::common::I4;

    /// @brief Definition of "Crs" field.
    using Crs = field::common::I4;

    /// @brief Definition of "Cic" field.
    using Cic = field::common::I4;

    /// @brief Definition of "Cis" field.
    using Cis = field::common::I4;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;


    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        svId,
        reserved1,
        SatH1,
        IODC,
        a2,
        a1,
        a0,
        toc,
        TGD1,
        URAI,
        IODE,
        toe,
        sqrtA,
        e,
        omega,
        Deltan,
        IDOT,
        M0,
        Omega0,
        OmegaDot,
        i0,
        Cuc,
        Cus,
        Crc,
        Crs,
        Cic,
        Cis,
        reserved2
    >;
};

/// @brief Definition of MGA-BDS-EPH message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaBdsEphFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaBdsEph : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_BDS>,
        comms::option::FieldsImpl<MgaBdsEphFields::All>,
        comms::option::MsgType<MgaBdsEph<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaBdsEphFields::type field
    ///     @li @b version for @ref MgaBdsEphFields::version field
    ///     @li @b svId for @ref MgaBdsEphFields::svId field
    ///     @li @b SatH1 for @ref MgaBdsEphFields::SatH1 field
    ///     @li @b IODC for @ref MgaBdsEphFields::IODC field
    ///     @li @b a2 for @ref MgaBdsEphFields::a2 field
    ///     @li @b a1 for @ref MgaBdsEphFields::a1 field
    ///     @li @b a0 for @ref MgaBdsEphFields::a0 field
    ///     @li @b toc for @ref MgaBdsEphFields::toc field
    ///     @li @b TGD1 for @ref MgaBdsEphFields::TGD1 field
    ///     @li @b URAI for @ref MgaBdsEphFields::URAI field
    ///     @li @b IODE for @ref MgaBdsEphFields::IODE field
    ///     @li @b toe for @ref MgaBdsEphFields::toe field
    ///     @li @b sqrtA for @ref MgaBdsEphFields::sqrtA field
    ///     @li @b e for @ref MgaBdsEphFields::e field
    ///     @li @b omega for @ref MgaBdsEphFields::omega field
    ///     @li @b Deltan for @ref MgaBdsEphFields::Deltan field
    ///     @li @b IDOT for @ref MgaBdsEphFields::IDOT field
    ///     @li @b M0 for @ref MgaBdsEphFields::M0 field
    ///     @li @b Omega0 for @ref MgaBdsEphFields::Omega0 field
    ///     @li @b OmegaDot for @ref MgaBdsEphFields::OmegaDot field
    ///     @li @b i0 for @ref MgaBdsEphFields::i0 field
    ///     @li @b Cuc for @ref MgaBdsEphFields::Cuc field
    ///     @li @b Cus for @ref MgaBdsEphFields::Cus field
    ///     @li @b Crc for @ref MgaBdsEphFields::Crc field
    ///     @li @b Crs for @ref MgaBdsEphFields::Crs field
    ///     @li @b Cic for @ref MgaBdsEphFields::Cic field
    ///     @li @b Cis for @ref MgaBdsEphFields::Cis field
    ///     @li @b reserved2 for @ref MgaBdsEphFields::reserved2 field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        svId,
        reserved1,
        SatH1,
        IODC,
        a2,
        a1,
        a0,
        toc,
        TGD1,
        URAI,
        IODE,
        toe,
        sqrtA,
        e,
        omega,
        Deltan,
        IDOT,
        M0,
        Omega0,
        OmegaDot,
        i0,
        Cuc,
        Cus,
        Crc,
        Crs,
        Cic,
        Cis,
        reserved2
    );

    /// @brief Default constructor
    MgaBdsEph() = default;

    /// @brief Copy constructor
    MgaBdsEph(const MgaBdsEph&) = default;

    /// @brief Move constructor
    MgaBdsEph(MgaBdsEph&& other) = default;

    /// @brief Destructor
    virtual ~MgaBdsEph() = default;

    /// @brief Copy assignment
    MgaBdsEph& operator=(const MgaBdsEph&) = default;

    /// @brief Move assignment
    MgaBdsEph& operator=(MgaBdsEph&&) = default;
};

}  // namespace message

}  // namespace ublox

