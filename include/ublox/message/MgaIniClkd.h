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
/// @brief Contains definition of MGA-INI-CLKD message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-INI-CLKD message fields.
/// @see MgaIniClkd
struct MgaIniClkdFields
{
    /// @brief Definition of "type" field.
    using type  =
    field::common::U1T<
        comms::option::ValidNumValueRange<0x20, 0x20>,
        comms::option::DefaultNumValue<0x20>,
        comms::option::FailOnInvalid<>
    >;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "clkD" field.
    using clkD = field::common::I4T<comms::option::UnitsNanoseconds>;

    /// @brief Definition of "clkDAcc" field.
    using clkDAcc = field::common::U4T<comms::option::UnitsNanoseconds>;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        reserved1,
        clkD,
        clkDAcc
    >;
};

/// @brief Definition of MGA-INI-CLKD message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaIniClkdFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaIniClkd : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_INI>,
        comms::option::FieldsImpl<MgaIniClkdFields::All>,
        comms::option::MsgType<MgaIniClkd<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaIniClkdFields::type field
    ///     @li @b version for @ref MgaIniClkdFields::version field
    ///     @li @b reserved1 for @ref MgaIniClkdFields::reserved1 field
    ///     @li @b clkD for @ref MgaIniClkdFields::clkD field
    ///     @li @b clkDAcc for @ref MgaIniClkdFields::clkDAcc field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        reserved1,
        clkD,
        clkDAcc
    );

    /// @brief Default constructor
    MgaIniClkd() = default;

    /// @brief Copy constructor
    MgaIniClkd(const MgaIniClkd&) = default;

    /// @brief Move constructor
    MgaIniClkd(MgaIniClkd&& other) = default;

    /// @brief Destructor
    ~MgaIniClkd() = default;

    /// @brief Copy assignment
    MgaIniClkd& operator=(const MgaIniClkd&) = default;

    /// @brief Move assignment
    MgaIniClkd& operator=(MgaIniClkd&&) = default;
};

}  // namespace message

}  // namespace ublox

