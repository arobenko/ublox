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
/// @brief Contains definition of MON-GNSS message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MON-GNSS message fields.
/// @see MonGnss
struct MonGnssFields
{
    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<1, 1>,
            comms::option::DefaultNumValue<1>
        >;

    /// @brief Definition of "supported" field.
    struct supported : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xf0, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(GPSSup, GlonassSup, BeidouSup, GalileoSup);
    };

    /// @brief Definition of "defaultGnss" field.
    struct defaultGnss : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xf0, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(GPSDef, GlonassDef, BeidouDef, GalileoDef);
    };

    /// @brief Definition of "enabled" field.
    struct enabled : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xf0, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(GPSEna, GlonassEna, BeidouEna, GalileoEna);
    };


    /// @brief Definition of "simultaneous" field.
    using simultaneous = field::common::U1;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res3;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        supported,
        defaultGnss,
        enabled,
        simultaneous,
        reserved1
    >;
};

/// @brief Definition of MON-GNSS message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MonGnssFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MonGnss : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_GNSS>,
        comms::option::FieldsImpl<MonGnssFields::All>,
        comms::option::MsgType<MonGnss<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref MonGnssFields::version field
    ///     @li @b supported for @ref MonGnssFields::supported field
    ///     @li @b defaultGnss for @ref MonGnssFields::defaultGnss field
    ///     @li @b enabled for @ref MonGnssFields::enabled field
    ///     @li @b simultaneous for @ref MonGnssFields::simultaneous field
    ///     @li @b reserved1 for @ref MonGnssFields::reserved1 field
    COMMS_MSG_FIELDS_ACCESS(
        version,
        supported,
        defaultGnss,
        enabled,
        simultaneous,
        reserved1
    );

    /// @brief Default constructor
    MonGnss() = default;

    /// @brief Copy constructor
    MonGnss(const MonGnss&) = default;

    /// @brief Move constructor
    MonGnss(MonGnss&& other) = default;

    /// @brief Destructor
    ~MonGnss() = default;

    /// @brief Copy assignment
    MonGnss& operator=(const MonGnss&) = default;

    /// @brief Move assignment
    MonGnss& operator=(MonGnss&&) = default;
};

}  // namespace message

}  // namespace ublox

