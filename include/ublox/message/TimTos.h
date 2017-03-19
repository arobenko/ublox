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
/// @brief Contains definition of TIM-TOS message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the TIM-TOS message fields.
/// @see TimTos
struct TimTosFields
{
    /// @brief Definition of "version" field.
    using version = field::common::U1T<comms::option::ValidNumValueRange<0, 0> >;

    /// @brief Definition of "gnssId" field.
    using gnssId = field::common::gnssId;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "low" flags bits in @ref flags bitfield.
    struct flagsLow : public
        field::common::X1T<
            comms::option::FixedBitLength<8>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(
            leapNow,
            leapSoon,
            leapPositive,
            timeInLimit,
            intOscInLimit,
            extOscInLimit,
            gnssTimeValid,
            UTCTimeValid
        );
    };

    /// @brief Enumeration value for @ref discSrc field
    enum class DiscSrc : std::uint8_t
    {
        Internal, ///< internal oschillator
        Gnss, ///< GNSS
        EXTINT0, ///< EXTINT0
        EXTINT1, ///< EXTINT1
        HostInternal, ///< internal oscillator measured by the host
        HostExternal, ///< external oscillator measured by the host
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "discSrc" member field of @ref flags bitfield.
    using discSrc =
        field::common::EnumT<
            DiscSrc,
            comms::option::ValidNumValueRange<0, (int)DiscSrc::NumOfValues - 1>,
            comms::option::FixedBitLength<3>
        >;


    /// @brief Definition of "high" flags bits in @ref flags bitfield.
    struct flagsHigh : public
        field::common::X4T<
            comms::option::FixedBitLength<21>,
            comms::option::BitmaskReservedBits<0xfffffff8, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(raim, cohPulse, lockedPulse);
    };

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::BitfieldT<
            std::tuple<
                flagsLow,
                discSrc,
                flagsHigh
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(flagsLow, discSrc, flagsHigh);
    };

    /// @brief Definition of "year" field.
    using year = field::common::U2;

    /// @brief Definition of "month" field.
    using month = field::common::U1;

    /// @brief Definition of "day" field.
    using day = field::common::U1;

    /// @brief Definition of "hour" field.
    using hour = field::common::U1;

    /// @brief Definition of "minute" field.
    using minute = field::common::U1;

    /// @brief Definition of "second" field.
    using second = field::common::U1;

    /// @brief Definition of "utcStandard" field.
    using utcStandard = field::common::utcStandard;

    /// @brief Definition of "utcOffset" field.
    using utcOffset = field::common::I4T<field::common::Scaling_ns2s>;

    /// @brief Definition of "utcUncertainty" field.
    using utcUncertainty = field::common::U4T<field::common::Scaling_ns2s>;

    /// @brief Definition of "week" field.
    using week = field::common::U4;

    /// @brief Definition of "TOW" field.
    using TOW = field::common::U4;

    /// @brief Definition of "gnssOffset" field.
    using gnssOffset = field::common::I4T<field::common::Scaling_ns2s>;

    /// @brief Definition of "gnssUncertainty" field.
    using gnssUncertainty = field::common::U4T<field::common::Scaling_ns2s>;

    /// @brief Definition of "intOscOffset" field.
    using intOscOffset = field::common::I4T<comms::option::ScalingRatio<1, 0x100> >;

    /// @brief Definition of "intOscUncertainty" field.
    using intOscUncertainty = field::common::U4T<comms::option::ScalingRatio<1, 0x100> >;

    /// @brief Definition of "extOscOffset" field.
    using extOscOffset = field::common::I4T<comms::option::ScalingRatio<1, 0x100> >;

    /// @brief Definition of "extOscUncertainty" field.
    using extOscUncertainty = field::common::U4T<comms::option::ScalingRatio<1, 0x100> >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        gnssId,
        reserved1,
        flags,
        year,
        month,
        day,
        hour,
        minute,
        second,
        utcStandard,
        utcOffset,
        utcUncertainty,
        week,
        TOW,
        gnssOffset,
        gnssUncertainty,
        intOscOffset,
        intOscUncertainty,
        extOscOffset,
        extOscUncertainty
    >;
};

/// @brief Definition of TIM-TOS message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref TimTosFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class TimTos : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_TOS>,
        comms::option::FieldsImpl<TimTosFields::All>,
        comms::option::MsgType<TimTos<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref TimTosFields::version field
    ///     @li @b gnssId for @ref TimTosFields::gnssId field
    ///     @li @b reserved1 for @ref TimTosFields::reserved1 field
    ///     @li @b flags for @ref TimTosFields::flags field
    ///     @li @b year for @ref TimTosFields::year field
    ///     @li @b month for @ref TimTosFields::month field
    ///     @li @b day for @ref TimTosFields::day field
    ///     @li @b hour for @ref TimTosFields::hour field
    ///     @li @b minute for @ref TimTosFields::minute field
    ///     @li @b second for @ref TimTosFields::second field
    ///     @li @b utcStandard for @ref TimTosFields::utcStandard field
    ///     @li @b utcOffset for @ref TimTosFields::utcOffset field
    ///     @li @b utcUncertainty for @ref TimTosFields::utcUncertainty field
    ///     @li @b week for @ref TimTosFields::week field
    ///     @li @b TOW for @ref TimTosFields::TOW field
    ///     @li @b gnssOffset for @ref TimTosFields::gnssOffset field
    ///     @li @b gnssUncertainty for @ref TimTosFields::gnssUncertainty field
    ///     @li @b intOscOffset for @ref TimTosFields::intOscOffset field
    ///     @li @b intOscUncertainty for @ref TimTosFields::intOscUncertainty field
    ///     @li @b extOscOffset for @ref TimTosFields::extOscOffset field
    ///     @li @b extOscUncertainty for @ref TimTosFields::extOscUncertainty field
    COMMS_MSG_FIELDS_ACCESS(
        version,
        gnssId,
        reserved1,
        flags,
        year,
        month,
        day,
        hour,
        minute,
        second,
        utcStandard,
        utcOffset,
        utcUncertainty,
        week,
        TOW,
        gnssOffset,
        gnssUncertainty,
        intOscOffset,
        intOscUncertainty,
        extOscOffset,
        extOscUncertainty
    );

    /// @brief Default constructor
    TimTos() = default;

    /// @brief Copy constructor
    TimTos(const TimTos&) = default;

    /// @brief Move constructor
    TimTos(TimTos&& other) = default;

    /// @brief Destructor
    virtual ~TimTos() = default;

    /// @brief Copy assignment
    TimTos& operator=(const TimTos&) = default;

    /// @brief Move assignment
    TimTos& operator=(TimTos&&) = default;
};


}  // namespace message

}  // namespace ublox

