//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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

    /// @brief Use this enumeration to access member fields of @ref flags bitfield.
    enum
    {
        flags_lowBits, ///< index of @ref flagsLowBits member field
        flags_timeBase, ///< index of @ref timeBase member field
        flags_highBits, ///< index of @ref flagsHighBits member field
        flags_numOfValues ///< number of member fields
    };

    /// @brief Bits access enumeration for bits in @b flagsLowBits member of
    ///     @ref flags bitfield field.
    enum
    {
        flagsLowBits_mode, ///< @b mode bit index
        flagsLowBits_run, ///< @b run bit index
        flagsLowBits_newFallingEdge, ///< @b newFallingEdge bit index
        flagsLowBits_numOfValues ///< number of available bits
    };

    /// @brief Bits access enumeration for bits in @b flagsHighBits member of
    ///     @ref flags bitfield field.
    enum
    {
        flagsHighBits_utc, ///< @b utc bit index
        flagsHighBits_time, ///< @b time bit index
        flagsHighBits_newRisingEdge, ///< @b newRisingEdge bit index
        flagsHighBits_numOfValues ///< number of available bits
    };

    /// @brief Definition of "ch" field.
    using ch =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 1>
        >;

    /// @brief Definition of the 3 least significant bits of @ref flags bitfield
    ///     as a separate bitmask member field.
    using flagsLowBits =
        field::common::X1T<
            comms::option::FixedBitLength<3>,
            comms::option::BitmaskReservedBits<0xf8, 0>
        >;

    /// @brief Definition of "timeBase" member field of @ref flags bitfield.
    using timeBase =
        field::common::EnumT<
            TimeBase,
            comms::option::FixedBitLength<2>,
            comms::option::ValidNumValueRange<0, (int)TimeBase::NumOfValues - 1>
        >;

    /// @brief Definition of the 3 most significant bits of @ref flags bitfield
    ///     as a separate bitmask member field.
    using flagsHighBits =
        field::common::X1T<
            comms::option::FixedBitLength<3>,
            comms::option::BitmaskReservedBits<0xf8, 0>
        >;

    /// @brief Definition of "flags" field.
    using flags =
        field::common::BitfieldT<
            std::tuple<
                flagsLowBits,
                timeBase,
                flagsHighBits
            >
        >;

    /// @brief Definition of "count" field.
    using count = field::common::U2;

    /// @brief Definition of "wnR" field.
    using wnR = field::common::U2;

    /// @brief Definition of "wnF" field.
    using wnF = field::common::U2;

    /// @brief Definition of "towMsR" field.
    using towMsR = field::common::U4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "towSubMsR" field.
    using towSubMsR = field::common::U4T<field::common::Scaling_ns2s>;

    /// @brief Definition of "towMsF" field.
    using towMsF = field::common::U4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "towSubMsF" field.
    using towSubMsF = field::common::U4T<field::common::Scaling_ns2s>;

    /// @brief Definition of "accEst" field.
    using accEst = field::common::U4T<field::common::Scaling_ns2s>;

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
///     See @ref TimTm2Fields and for definition of the fields this message contains.
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
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_TM2>,
        comms::option::FieldsImpl<TimTm2Fields::All>,
        comms::option::MsgType<TimTm2<TMsgBase> >
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_ch, ///< @b ch field, see @ref TimTm2Fields::ch
        FieldIdx_flags, ///< @b flags field, see @ref TimTm2Fields::flags
        FieldIdx_count, ///< @b count field, see @ref TimTm2Fields::count
        FieldIdx_wnR, ///< @b wnR field, see @ref TimTm2Fields::wnR
        FieldIdx_wnF, ///< @b wnF field, see @ref TimTm2Fields::wnF
        FieldIdx_towMsR, ///< @b towMsR field, see @ref TimTm2Fields::towMsR
        FieldIdx_towSubMsR, ///< @b towSubMsR field, see @ref TimTm2Fields::towSubMsR
        FieldIdx_towMsF, ///< @b towMsF field, see @ref TimTm2Fields::towMsF
        FieldIdx_towSubMsF, ///< @b towSubMsF field, see @ref TimTm2Fields::towSubMsF
        FieldIdx_accEst, ///< @b accEst field, see @ref TimTm2Fields::accEst
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        TimTm2Fields::ch& ch; ///< @b ch field, see @ref TimTm2Fields::ch
        TimTm2Fields::flags& flags; ///< @b flags field, see @ref TimTm2Fields::flags
        TimTm2Fields::count& count; ///< @b count field, see @ref TimTm2Fields::count
        TimTm2Fields::wnR& wnR; ///< @b wnR field, see @ref TimTm2Fields::wnR
        TimTm2Fields::wnF& wnF; ///< @b wnF field, see @ref TimTm2Fields::wnF
        TimTm2Fields::towMsR& towMsR; ///< @b towMsR field, see @ref TimTm2Fields::towMsR
        TimTm2Fields::towSubMsR& towSubMsR; ///< @b towSubMsR field, see @ref TimTm2Fields::towSubMsR
        TimTm2Fields::towMsF& towMsF; ///< @b towMsF field, see @ref TimTm2Fields::towMsF
        TimTm2Fields::towSubMsF& towSubMsF; ///< @b towSubMsF field, see @ref TimTm2Fields::towSubMsF
        TimTm2Fields::accEst& accEst; ///< @b accEst field, see @ref TimTm2Fields::accEst
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const TimTm2Fields::ch& ch; ///< @b ch field, see @ref TimTm2Fields::ch
        const TimTm2Fields::flags& flags; ///< @b flags field, see @ref TimTm2Fields::flags
        const TimTm2Fields::count& count; ///< @b count field, see @ref TimTm2Fields::count
        const TimTm2Fields::wnR& wnR; ///< @b wnR field, see @ref TimTm2Fields::wnR
        const TimTm2Fields::wnF& wnF; ///< @b wnF field, see @ref TimTm2Fields::wnF
        const TimTm2Fields::towMsR& towMsR; ///< @b towMsR field, see @ref TimTm2Fields::towMsR
        const TimTm2Fields::towSubMsR& towSubMsR; ///< @b towSubMsR field, see @ref TimTm2Fields::towSubMsR
        const TimTm2Fields::towMsF& towMsF; ///< @b towMsF field, see @ref TimTm2Fields::towMsF
        const TimTm2Fields::towSubMsF& towSubMsF; ///< @b towSubMsF field, see @ref TimTm2Fields::towSubMsF
        const TimTm2Fields::accEst& accEst; ///< @b accEst field, see @ref TimTm2Fields::accEst
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base,
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
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    TimTm2() = default;

    /// @brief Copy constructor
    TimTm2(const TimTm2&) = default;

    /// @brief Move constructor
    TimTm2(TimTm2&& other) = default;

    /// @brief Destructor
    virtual ~TimTm2() = default;

    /// @brief Copy assignment
    TimTm2& operator=(const TimTm2&) = default;

    /// @brief Move assignment
    TimTm2& operator=(TimTm2&&) = default;
};


}  // namespace message

}  // namespace ublox

