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
/// @brief Contains definition of MGA-INI-TIME_GNSS message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-INI-TIME_GNSS message fields.
/// @see MgaIniTimeGnss
struct MgaIniTimeGnssFields
{
    /// @brief Definition of "type" field.
    using type  =
    field::common::U1T<
        comms::option::ValidNumValueRange<0x11, 0x11>,
        comms::option::DefaultNumValue<0x11>,
        comms::option::FailOnInvalid
    >;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Enumeration value for @ref source field.
    enum class Source : std::uint8_t
    {
        None, ///< none
        EXTINT0, ///< relative to pulse sent to EXTINT0
        EXTINT1, ///< relative to pulse sent to EXTINT1
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "source" member field of @ref ref bitfield.
    using source =
        field::common::EnumT<
            Source,
            comms::option::ValidNumValueRange<0, (int)Source::NumOfValues - 1>,
            comms::option::FixedBitLength<4>
        >;

    /// @brief Definition of remaining bits in @ref ref bitfield.
    struct flags : public
        field::common::X1T<
            comms::option::FixedBitLength<4>,
            comms::option::BitmaskReservedBits<0xfc, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(fall, last);
    };

    /// @brief Definition of "ref" field.
    struct ref : public
        field::common::BitfieldT<
            std::tuple<
                source,
                flags
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(source, flags);
    };

    /// @brief Definition of "gnssId" field.
    using gnssId = field::common::gnssId;

    /// @brief Definition of "reserved1" field.
    using reserved1  = field::common::res2;

    /// @brief Definition of "week" field.
    using week = field::common::U2;

    /// @brief Definition of "tow" field.
    using tow = field::common::U4;

    /// @brief Definition of "ns" field.
    using ns =
        field::common::U4T<
            comms::option::ValidNumValueRange<0, 999999999>
        >;

    /// @brief Definition of "tAccS" field.
    using tAccS = field::common::U2;

    /// @brief Definition of "reserved2" field.
    using reserved2  = field::common::res2;


    /// @brief Definition of "tAccNs" field.
    using tAccNs =
        field::common::U4T<
            comms::option::ValidNumValueRange<0, 999999999>
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        ref,
        gnssId,
        reserved1,
        week,
        tow,
        ns,
        tAccS,
        reserved2,
        tAccNs
    >;
};

/// @brief Definition of MGA-INI-TIME_GNSS message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaIniTimeGnssFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaIniTimeGnss : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_INI>,
        comms::option::FieldsImpl<MgaIniTimeGnssFields::All>,
        comms::option::MsgType<MgaIniTimeGnss<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaIniTimeGnssFields::type field
    ///     @li @b version for @ref MgaIniTimeGnssFields::version field
    ///     @li @b ref for @ref MgaIniTimeGnssFields::ref field
    ///     @li @b gnssId for @ref MgaIniTimeGnssFields::gnssId field
    ///     @li @b reserved1 for @ref MgaIniTimeGnssFields::reserved1 field
    ///     @li @b week for @ref MgaIniTimeGnssFields::week field
    ///     @li @b tow for @ref MgaIniTimeGnssFields::tow field
    ///     @li @b ns for @ref MgaIniTimeGnssFields::ns field
    ///     @li @b tAccS for @ref MgaIniTimeGnssFields::tAccS field
    ///     @li @b reserved2 for @ref MgaIniTimeGnssFields::reserved2 field
    ///     @li @b tAccNs for @ref MgaIniTimeGnssFields::tAccNs field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        ref,
        gnssId,
        reserved1,
        week,
        tow,
        ns,
        tAccS,
        reserved2,
        tAccNs
    );

    /// @brief Default constructor
    MgaIniTimeGnss() = default;

    /// @brief Copy constructor
    MgaIniTimeGnss(const MgaIniTimeGnss&) = default;

    /// @brief Move constructor
    MgaIniTimeGnss(MgaIniTimeGnss&& other) = default;

    /// @brief Destructor
    virtual ~MgaIniTimeGnss() = default;

    /// @brief Copy assignment
    MgaIniTimeGnss& operator=(const MgaIniTimeGnss&) = default;

    /// @brief Move assignment
    MgaIniTimeGnss& operator=(MgaIniTimeGnss&&) = default;
};

}  // namespace message

}  // namespace ublox

