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
/// @brief Contains definition of MGA-INI-POS_XYZ message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-INI-POS_XYZ message fields.
/// @see MgaIniPosXyz
struct MgaIniPosXyzFields
{
    /// @brief Definition of "type" field.
    using type  =
    field::common::U1T<
        comms::option::ValidNumValueRange<0, 0>,
        comms::option::FailOnInvalid<>
    >;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "ecefX" field.
    using ecefX = field::common::I4T<field::common::Scaling_cm2m>;

    /// @brief Definition of "ecefY" field.
    using ecefY = ecefX;

    /// @brief Definition of "ecefZ" field.
    using ecefZ = ecefX;

    /// @brief Definition of "posAcc" field.
    using posAcc = field::common::U4T<field::common::Scaling_cm2m>;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        reserved1,
        ecefX,
        ecefY,
        ecefZ,
        posAcc
    >;
};

/// @brief Definition of MGA-INI-POS_XYZ message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaIniPosXyzFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaIniPosXyz : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_INI>,
        comms::option::FieldsImpl<MgaIniPosXyzFields::All>,
        comms::option::MsgType<MgaIniPosXyz<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaIniPosXyzFields::type field
    ///     @li @b version for @ref MgaIniPosXyzFields::version field
    ///     @li @b reserved1 for @ref MgaIniPosXyzFields::reserved1 field
    ///     @li @b ecefX for @ref MgaIniPosXyzFields::ecefX field
    ///     @li @b ecefY for @ref MgaIniPosXyzFields::ecefY field
    ///     @li @b ecefZ for @ref MgaIniPosXyzFields::ecefZ field
    ///     @li @b posAcc for @ref MgaIniPosXyzFields::posAcc field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        reserved1,
        ecefX,
        ecefY,
        ecefZ,
        posAcc
    );

    /// @brief Default constructor
    MgaIniPosXyz() = default;

    /// @brief Copy constructor
    MgaIniPosXyz(const MgaIniPosXyz&) = default;

    /// @brief Move constructor
    MgaIniPosXyz(MgaIniPosXyz&& other) = default;

    /// @brief Destructor
    ~MgaIniPosXyz() = default;

    /// @brief Copy assignment
    MgaIniPosXyz& operator=(const MgaIniPosXyz&) = default;

    /// @brief Move assignment
    MgaIniPosXyz& operator=(MgaIniPosXyz&&) = default;
};

}  // namespace message

}  // namespace ublox

