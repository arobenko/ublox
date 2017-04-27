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
/// @brief Contains definition of MGA-GLO-TIMEOFFSET message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-GLO-TIMEOFFSET message fields.
/// @see MgaGloTimeoffset
struct MgaGloTimeoffsetFields
{
    /// @brief Definition of "type" field.
    using type  =
    field::common::U1T<
        comms::option::ValidNumValueRange<3, 3>,
        comms::option::DefaultNumValue<3>,
        comms::option::FailOnInvalid<>
    >;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "N" field.
    using N = field::common::U2T<comms::option::UnitsDays>;

    /// @brief Definition of "tauC" field.
    using tauC =
        field::common::I4T<
            comms::option::ScalingRatio<1, 0x8000000>,
            comms::option::UnitsSeconds
        >;

    /// @brief Definition of "tauGps" field.
    using tauGps =
        field::common::I4T<
            comms::option::ScalingRatio<1, 0x80000000>,
            comms::option::UnitsSeconds
        >;

    /// @brief Definition of "B1" field.
    using B1 =
        field::common::I2T<
            comms::option::ScalingRatio<1, 0x400>,
            comms::option::UnitsSeconds
        >;

    /// @brief Definition of "B2" field.
    using B2 =
        field::common::I2T<
            comms::option::ScalingRatio<1, 0x10000>,
            comms::option::UnitsSeconds
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        N,
        tauC,
        tauGps,
        B1,
        B2,
        reserved1
    >;
};

/// @brief Definition of MGA-GLO-TIMEOFFSET message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaGloTimeoffsetFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaGloTimeoffset : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_GLO>,
        comms::option::FieldsImpl<MgaGloTimeoffsetFields::All>,
        comms::option::MsgType<MgaGloTimeoffset<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaGloTimeoffsetFields::type field
    ///     @li @b version for @ref MgaGloTimeoffsetFields::version field
    ///     @li @b N for @ref MgaGloTimeoffsetFields::N field
    ///     @li @b tauC for @ref MgaGloTimeoffsetFields::tauC field
    ///     @li @b tauGps for @ref MgaGloTimeoffsetFields::tauGps field
    ///     @li @b B1 for @ref MgaGloTimeoffsetFields::B1 field
    ///     @li @b B2 for @ref MgaGloTimeoffsetFields::B2 field
    ///     @li @b reserved1 for @ref MgaGloTimeoffsetFields::reserved1 field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        N,
        tauC,
        tauGps,
        B1,
        B2,
        reserved1
    );

    /// @brief Default constructor
    MgaGloTimeoffset() = default;

    /// @brief Copy constructor
    MgaGloTimeoffset(const MgaGloTimeoffset&) = default;

    /// @brief Move constructor
    MgaGloTimeoffset(MgaGloTimeoffset&& other) = default;

    /// @brief Destructor
    ~MgaGloTimeoffset() = default;

    /// @brief Copy assignment
    MgaGloTimeoffset& operator=(const MgaGloTimeoffset&) = default;

    /// @brief Move assignment
    MgaGloTimeoffset& operator=(MgaGloTimeoffset&&) = default;
};

}  // namespace message

}  // namespace ublox

