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
/// @brief Contains definition of MGA-INI-FREQ message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-INI-FREQ message fields.
/// @see MgaIniFreq
struct MgaIniFreqFields
{
    /// @brief Definition of "type" field.
    using type  =
    field::common::U1T<
        comms::option::ValidNumValueRange<0x21, 0x21>,
        comms::option::DefaultNumValue<0x21>,
        comms::option::FailOnInvalid<>
    >;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Enumeration value for @ref source field.
    enum class Source : std::uint8_t
    {
        EXTINT0, ///< frequency available on EXTINT0
        EXTINT1, ///< frequency available on EXTINT1
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "source" member field in @ref flags bitfield.
    using source =
        field::common::EnumT<
            Source,
            comms::option::FixedBitLength<4>,
            comms::option::ValidNumValueRange<0, (int)Source::NumOfValues - 1>
        >;

    /// @brief Definition of flags bits in @ref flags bitfield.
    struct flagsBits : public
        field::common::X1T<
            comms::option::FixedLength<1>,
            comms::option::FixedBitLength<4>,
            comms::option::BitmaskReservedBits<0xfe, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(fall);
    };

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::BitfieldT<
            std::tuple<
                source,
                flagsBits
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        ///
        ///     The names are:
        ///     @li source for @ref source
        ///     @li bits for @ref flagsBits
        ///
        COMMS_FIELD_MEMBERS_ACCESS(source, bits);
    };

    /// @brief Definition of "freq" field.
    using freq =
        field::common::I4T<
            comms::option::ScalingRatio<1, 100>,
            comms::option::UnitsHertz
        >;

    /// @brief Definition of "freqAcc" field.
    using freqAcc = field::common::U4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        reserved1,
        flags,
        freq,
        freqAcc
    >;
};

/// @brief Definition of MGA-INI-FREQ message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaIniFreqFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaIniFreq : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_INI>,
        comms::option::FieldsImpl<MgaIniFreqFields::All>,
        comms::option::MsgType<MgaIniFreq<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaIniFreqFields::type field
    ///     @li @b version for @ref MgaIniFreqFields::version field
    ///     @li @b reserved1 for @ref MgaIniFreqFields::reserved1 field
    ///     @li @b flags for @ref MgaIniFreqFields::flags field
    ///     @li @b freq for @ref MgaIniFreqFields::freq field
    ///     @li @b freqAcc for @ref MgaIniFreqFields::freqAcc field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        reserved1,
        flags,
        freq,
        freqAcc
    );

    /// @brief Default constructor
    MgaIniFreq() = default;

    /// @brief Copy constructor
    MgaIniFreq(const MgaIniFreq&) = default;

    /// @brief Move constructor
    MgaIniFreq(MgaIniFreq&& other) = default;

    /// @brief Destructor
    ~MgaIniFreq() = default;

    /// @brief Copy assignment
    MgaIniFreq& operator=(const MgaIniFreq&) = default;

    /// @brief Move assignment
    MgaIniFreq& operator=(MgaIniFreq&&) = default;
};

}  // namespace message

}  // namespace ublox

