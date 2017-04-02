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
/// @brief Contains definition of MGA-INI-POS_LLH message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-INI-POS_LLH message fields.
/// @see MgaIniPosLlh
struct MgaIniPosLlhFields
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

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "lat" field.
    using lat = field::common::I4T<comms::option::ScalingRatio<1, 10000000> >;

    /// @brief Definition of "lon" field.
    using lon = field::common::I4T<comms::option::ScalingRatio<1, 10000000> >;

    /// @brief Definition of "alt" field.
    using alt = field::common::I4T<field::common::Scaling_cm2m>;

    /// @brief Definition of "posAcc" field.
    using posAcc = field::common::U4T<field::common::Scaling_cm2m>;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        reserved1,
        lat,
        lon,
        alt,
        posAcc
    >;
};

/// @brief Definition of MGA-INI-POS_LLH message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaIniPosLlhFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaIniPosLlh : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_INI>,
        comms::option::FieldsImpl<MgaIniPosLlhFields::All>,
        comms::option::MsgType<MgaIniPosLlh<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaIniPosLlhFields::type field
    ///     @li @b version for @ref MgaIniPosLlhFields::version field
    ///     @li @b reserved1 for @ref MgaIniPosLlhFields::reserved1 field
    ///     @li @b lat for @ref MgaIniPosLlhFields::lat field
    ///     @li @b lon for @ref MgaIniPosLlhFields::lon field
    ///     @li @b alt for @ref MgaIniPosLlhFields::alt field
    ///     @li @b posAcc for @ref MgaIniPosLlhFields::posAcc field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        reserved1,
        lat,
        lon,
        alt,
        posAcc
    );

    /// @brief Default constructor
    MgaIniPosLlh() = default;

    /// @brief Copy constructor
    MgaIniPosLlh(const MgaIniPosLlh&) = default;

    /// @brief Move constructor
    MgaIniPosLlh(MgaIniPosLlh&& other) = default;

    /// @brief Destructor
    ~MgaIniPosLlh() = default;

    /// @brief Copy assignment
    MgaIniPosLlh& operator=(const MgaIniPosLlh&) = default;

    /// @brief Move assignment
    MgaIniPosLlh& operator=(MgaIniPosLlh&&) = default;
};

}  // namespace message

}  // namespace ublox

