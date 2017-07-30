//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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
/// @brief Contains definition of TIM-TM2 message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the TIM-TM2 message fields.
/// @see TimTm2
struct TimTm2Fields
{
    /// @brief Value enumeration for @ref timeBase field.
    enum class TimeBase : std::uint8_t
    {
        ReceiverTime, ///< Receiver Time
        GPS, ///< GPS
        UTC, ///< UTC
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "ch" field.
    using ch =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 1>
        >;

    /// @brief Definition of the 3 least significant bits of @ref flags bitfield
    ///     as a separate bitmask member field.
    struct flagsLowBits : public
        field::common::X1T<
            comms::option::FixedBitLength<3>,
            comms::option::BitmaskReservedBits<0xf8, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(mode, run, newFallingEdge);
    };

    /// @brief Definition of "timeBase" member field of @ref flags bitfield.
    using timeBase =
        field::common::EnumT<
            TimeBase,
            comms::option::FixedBitLength<2>,
            comms::option::ValidNumValueRange<0, (int)TimeBase::NumOfValues - 1>
        >;

    /// @brief Definition of the 3 most significant bits of @ref flags bitfield
    ///     as a separate bitmask member field.
    struct flagsHighBits : public
        field::common::X1T<
            comms::option::FixedBitLength<3>,
            comms::option::BitmaskReservedBits<0xf8, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(utc, time, newRisingEdge);
    };

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::BitfieldT<
            std::tuple<
                flagsLowBits,
                timeBase,
                flagsHighBits
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(flagsLowBits, timeBase, flagsHighBits);
    };

    /// @brief Definition of "count" field.
    using count = field::common::U2;

    /// @brief Definition of "wnR" field.
    using wnR = field::common::U2;

    /// @brief Definition of "wnF" field.
    using wnF = field::common::U2;

    /// @brief Definition of "towMsR" field.
    using towMsR = field::common::U4T<comms::option::UnitsMilliseconds>;

    /// @brief Definition of "towSubMsR" field.
    using towSubMsR = field::common::U4T<comms::option::UnitsNanoseconds>;

    /// @brief Definition of "towMsF" field.
    using towMsF = field::common::U4T<comms::option::UnitsMilliseconds>;

    /// @brief Definition of "towSubMsF" field.
    using towSubMsF = field::common::U4T<comms::option::UnitsNanoseconds>;

    /// @brief Definition of "accEst" field.
    using accEst = field::common::U4T<comms::option::UnitsNanoseconds>;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        ch,
        flags,
        count,
        wnR,
        wnF,
        towMsR,
        towSubMsR,
        towMsF,
        towSubMsF,
        accEst
    >;

};

/// @brief Definition of TIM-TM2 message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref TimTm2Fields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class TimTm2 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_TM2>,
        comms::option::FieldsImpl<TimTm2Fields::All>,
        comms::option::MsgType<TimTm2<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b ch for @ref TimTm2Fields::ch field
    ///     @li @b flags for @ref TimTm2Fields::flags field
    ///     @li @b count for @ref TimTm2Fields::count field
    ///     @li @b wnR for @ref TimTm2Fields::wnR field
    ///     @li @b wnF for @ref TimTm2Fields::wnF field
    ///     @li @b towMsR for @ref TimTm2Fields::towMsR field
    ///     @li @b towSubMsR for @ref TimTm2Fields::towSubMsR field
    ///     @li @b towMsF for @ref TimTm2Fields::towMsF field
    ///     @li @b towSubMsF for @ref TimTm2Fields::towSubMsF field
    ///     @li @b accEst for @ref TimTm2Fields::accEst field
    COMMS_MSG_FIELDS_ACCESS(
        ch,
        flags,
        count,
        wnR,
        wnF,
        towMsR,
        towSubMsR,
        towMsF,
        towSubMsF,
        accEst
    );

    /// @brief Default constructor
    TimTm2() = default;

    /// @brief Copy constructor
    TimTm2(const TimTm2&) = default;

    /// @brief Move constructor
    TimTm2(TimTm2&& other) = default;

    /// @brief Destructor
    ~TimTm2() = default;

    /// @brief Copy assignment
    TimTm2& operator=(const TimTm2&) = default;

    /// @brief Move assignment
    TimTm2& operator=(TimTm2&&) = default;
};


}  // namespace message

}  // namespace ublox

