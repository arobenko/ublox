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
/// @brief Contains definition of MGA-INI-TIME_UTC message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-INI-TIME_UTC message fields.
/// @see MgaIniTimeUtc
struct MgaIniTimeUtcFields
{
    /// @brief Definition of "type" field.
    using type  =
    field::common::U1T<
        comms::option::ValidNumValueRange<0x10, 0x10>,
        comms::option::DefaultNumValue<0x10>,
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

    /// @brief Definition of "leapSecs" field.
    using leapSecs = field::common::I1;

    /// @brief Definition of "year" field.
    using year = field::common::U2;

    /// @brief Definition of "month" field.
    using month  =
        field::common::U1T<
            comms::option::ValidNumValueRange<1, 12>
        >;

    /// @brief Definition of "day" field.
    using day  =
        field::common::U1T<
            comms::option::ValidNumValueRange<1, 31>
        >;

    /// @brief Definition of "hour" field.
    using hour  =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 23>
        >;

    /// @brief Definition of "minute" field.
    using minute  =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 59>
        >;

    /// @brief Definition of "second" field.
    using second  =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 60>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1  = field::common::res1;

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
        leapSecs,
        year,
        month,
        day,
        hour,
        minute,
        second,
        reserved1,
        ns,
        tAccS,
        reserved2,
        tAccNs
    >;
};

/// @brief Definition of MGA-INI-TIME_UTC message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaIniTimeUtcFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaIniTimeUtc : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_INI>,
        comms::option::FieldsImpl<MgaIniTimeUtcFields::All>,
        comms::option::MsgType<MgaIniTimeUtc<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaIniTimeUtcFields::type field
    ///     @li @b version for @ref MgaIniTimeUtcFields::version field
    ///     @li @b ref for @ref MgaIniTimeUtcFields::ref field
    ///     @li @b leapSecs for @ref MgaIniTimeUtcFields::leapSecs field
    ///     @li @b year for @ref MgaIniTimeUtcFields::year field
    ///     @li @b month for @ref MgaIniTimeUtcFields::month field
    ///     @li @b day for @ref MgaIniTimeUtcFields::day field
    ///     @li @b hour for @ref MgaIniTimeUtcFields::hour field
    ///     @li @b minute for @ref MgaIniTimeUtcFields::minute field
    ///     @li @b second for @ref MgaIniTimeUtcFields::second field
    ///     @li @b reserved1 for @ref MgaIniTimeUtcFields::reserved1 field
    ///     @li @b ns for @ref MgaIniTimeUtcFields::ns field
    ///     @li @b tAccS for @ref MgaIniTimeUtcFields::tAccS field
    ///     @li @b reserved2 for @ref MgaIniTimeUtcFields::reserved2 field
    ///     @li @b tAccNs for @ref MgaIniTimeUtcFields::tAccNs field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        ref,
        leapSecs,
        year,
        month,
        day,
        hour,
        minute,
        second,
        reserved1,
        ns,
        tAccS,
        reserved2,
        tAccNs
    );

    /// @brief Default constructor
    MgaIniTimeUtc() = default;

    /// @brief Copy constructor
    MgaIniTimeUtc(const MgaIniTimeUtc&) = default;

    /// @brief Move constructor
    MgaIniTimeUtc(MgaIniTimeUtc&& other) = default;

    /// @brief Destructor
    ~MgaIniTimeUtc() = default;

    /// @brief Copy assignment
    MgaIniTimeUtc& operator=(const MgaIniTimeUtc&) = default;

    /// @brief Move assignment
    MgaIniTimeUtc& operator=(MgaIniTimeUtc&&) = default;
};

}  // namespace message

}  // namespace ublox

