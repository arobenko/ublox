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
/// @brief Contains definition of MGA-GAL-UTC message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-GAL-UTC message fields.
/// @see MgaGalUtc
struct MgaGalUtcFields
{
    /// @brief Definition of "type" field.
    using type  =
    field::common::U1T<
        comms::option::ValidNumValueRange<5, 5>,
        comms::option::DefaultNumValue<5>,
        comms::option::FailOnInvalid
    >;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "a0" field.
    using a0 = field::common::I4;

    /// @brief Definition of "a1" field.
    using a1 = field::common::I4;

    /// @brief Definition of "dtLS" field.
    using dtLS = field::common::I1;

    /// @brief Definition of "tot" field.
    using tot = field::common::U1;

    /// @brief Definition of "wnt" field.
    using wnt = field::common::U1;

    /// @brief Definition of "wnLSF" field.
    using wnLSF = field::common::U1;

    /// @brief Definition of "dN" field.
    using dN = field::common::U1;

    /// @brief Definition of "dTLSF" field.
    using dTLSF = field::common::I1;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res2;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        reserved1,
        a0,
        a1,
        dtLS,
        tot,
        wnt,
        wnLSF,
        dN,
        dTLSF,
        reserved2
    >;
};

/// @brief Definition of MGA-GAL-UTC message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaGalUtcFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaGalUtc : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_GAL>,
        comms::option::FieldsImpl<MgaGalUtcFields::All>,
        comms::option::MsgType<MgaGalUtc<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaGalUtcFields::type field
    ///     @li @b version for @ref MgaGalUtcFields::version field
    ///     @li @b reserved1 for @ref MgaGalUtcFields::reserved1 field
    ///     @li @b a0 for @ref MgaGalUtcFields::a0 field
    ///     @li @b a1 for @ref MgaGalUtcFields::a1 field
    ///     @li @b dtLS for @ref MgaGalUtcFields::dtLS field
    ///     @li @b tot for @ref MgaGalUtcFields::tot field
    ///     @li @b wnt for @ref MgaGalUtcFields::wnt field
    ///     @li @b wnLSF for @ref MgaGalUtcFields::wnLSF field
    ///     @li @b dN for @ref MgaGalUtcFields::dN field
    ///     @li @b dTLSF for @ref MgaGalUtcFields::dTLSF field
    ///     @li @b reserved2 for @ref MgaGalUtcFields::reserved2 field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        reserved1,
        a0,
        a1,
        dtLS,
        tot,
        wnt,
        wnLSF,
        dN,
        dTLSF,
        reserved2
    );

    /// @brief Default constructor
    MgaGalUtc() = default;

    /// @brief Copy constructor
    MgaGalUtc(const MgaGalUtc&) = default;

    /// @brief Move constructor
    MgaGalUtc(MgaGalUtc&& other) = default;

    /// @brief Destructor
    ~MgaGalUtc() = default;

    /// @brief Copy assignment
    MgaGalUtc& operator=(const MgaGalUtc&) = default;

    /// @brief Move assignment
    MgaGalUtc& operator=(MgaGalUtc&&) = default;
};

}  // namespace message

}  // namespace ublox

