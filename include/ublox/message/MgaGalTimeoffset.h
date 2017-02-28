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
/// @brief Contains definition of MGA-GAL-TIMEOFFSET message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-GAL-TIMEOFFSET message fields.
/// @see MgaGalTimeoffset
struct MgaGalTimeoffsetFields
{
    /// @brief Definition of "type" field.
    using type  =
    field::common::U1T<
        comms::option::ValidNumValueRange<3, 3>,
        comms::option::DefaultNumValue<3>,
        comms::option::FailOnInvalid
    >;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "a0G" field.
    using a0G = field::common::I2;

    /// @brief Definition of "a1G" field.
    using a1G = field::common::I2;

    /// @brief Definition of "t0G" field.
    using t0G = field::common::U1;

    /// @brief Definition of "wn0G" field.
    using wn0G = field::common::U1;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res2;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        reserved1,
        a0G,
        a1G,
        t0G,
        wn0G,
        reserved2
    >;
};

/// @brief Definition of MGA-GAL-TIMEOFFSET message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaGalTimeoffsetFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaGalTimeoffset : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_GAL>,
        comms::option::FieldsImpl<MgaGalTimeoffsetFields::All>,
        comms::option::MsgType<MgaGalTimeoffset<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaGalTimeoffsetFields::type field
    ///     @li @b version for @ref MgaGalTimeoffsetFields::version field
    ///     @li @b reserved1 for @ref MgaGalTimeoffsetFields::reserved1 field
    ///     @li @b a0G for @ref MgaGalTimeoffsetFields::a0G field
    ///     @li @b a1G for @ref MgaGalTimeoffsetFields::a1G field
    ///     @li @b t0G for @ref MgaGalTimeoffsetFields::t0G field
    ///     @li @b wn0G for @ref MgaGalTimeoffsetFields::wn0G field
    ///     @li @b reserved2 for @ref MgaGalTimeoffsetFields::reserved2 field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        reserved1,
        a0G,
        a1G,
        t0G,
        wn0G,
        reserved2
    );

    /// @brief Default constructor
    MgaGalTimeoffset() = default;

    /// @brief Copy constructor
    MgaGalTimeoffset(const MgaGalTimeoffset&) = default;

    /// @brief Move constructor
    MgaGalTimeoffset(MgaGalTimeoffset&& other) = default;

    /// @brief Destructor
    virtual ~MgaGalTimeoffset() = default;

    /// @brief Copy assignment
    MgaGalTimeoffset& operator=(const MgaGalTimeoffset&) = default;

    /// @brief Move assignment
    MgaGalTimeoffset& operator=(MgaGalTimeoffset&&) = default;
};

}  // namespace message

}  // namespace ublox

