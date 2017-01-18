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
/// @brief Contains definition of CFG-PM2 message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-PM message fields.
/// @see CfgPm2
struct CfgPm2Fields
{
    /// @brief Value enumeration for @ref extintSelect field.
    enum class ExtintSelect : std::uint8_t
    {
        EXTINT0, ///< EXTINT0
        EXTINT1, ///< EXTINT1
        NumOfValues ///< number of available values
    };

    /// @brief Common value enumeration for @ref extintWake, @ref extintBackup,
    ///     and @ref limitPeakCurr member fields.
    enum class DisabledEnabled : std::uint8_t
    {
        Disabled, ///< disabled
        Enabled, ///< enabled
        NumOfValues ///< number of available values
    };

    /// @brief Value enumeration for @ref extintWake field.
    using ExtintWake = DisabledEnabled;

    /// @brief Value enumeration for @ref extintBackup field.
    using ExtintBackup = DisabledEnabled;

    /// @brief Value enumeration for @ref limitPeakCurr field.
    using LimitPeakCurr = DisabledEnabled;

    /// @brief Value enumeration for @ref mode field.
    enum class Mode : std::uint8_t
    {
        OnOff, ///< ON/OFF operation
        CyclicTracking, ///< Cyclic tracking operation
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::DefaultNumValue<1>,
            comms::option::ValidNumValueRange<1, 1>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res1;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res1;

    /// @brief Definition of "reserved" member of @ref flags bitfield field.
    using reserved =
        field::common::res1T<
            comms::option::FixedBitLength<4>
        >;

    /// @brief Definition of "extintSelect" member of @ref flags bitfield field.
    using extintSelect =
        field::common::EnumT<
            ExtintSelect,
            comms::option::ValidNumValueRange<0, (int)ExtintSelect::NumOfValues - 1>,
            comms::option::FixedBitLength<1>
        >;

    /// @brief Definition of "extintWake" member of @ref flags bitfield field.
    using extintWake =
        field::common::EnumT<
            ExtintWake,
            comms::option::ValidNumValueRange<0, (int)ExtintWake::NumOfValues - 1>,
            comms::option::FixedBitLength<1>
        >;

    /// @brief Definition of "extintBackup" member of @ref flags bitfield field.
    using extintBackup =
        field::common::EnumT<
            ExtintBackup,
            comms::option::ValidNumValueRange<0, (int)ExtintBackup::NumOfValues - 1>,
            comms::option::FixedBitLength<1>
        >;

    /// @brief Definition of "limitPeakCurr" member of @ref flags bitfield field.
    using limitPeakCurr =
        field::common::EnumT<
            LimitPeakCurr,
            comms::option::ValidNumValueRange<0, (int)LimitPeakCurr::NumOfValues - 1>,
            comms::option::FixedBitLength<2>
        >;

    /// @brief Definition of "waitTimeFix" bit as a bitmask member of @ref flags bitfield field.
    struct waitTimeFix : public
        field::common::X1T<comms::option::FixedBitLength<1> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(bit);
    };

    /// @brief Definition of "updateRTC" bit as a bitmask member of @ref flags bitfield field.
    struct updateRTC : public
        field::common::X1T<comms::option::FixedBitLength<1> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(bit);
    };

    /// @brief Definition of "updateEPH" bit as a bitmask member of @ref flags bitfield field.
    struct updateEPH : public
        field::common::X1T<comms::option::FixedBitLength<1> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(bit);
    };

    /// @brief Definition of "doNotEnterOff" bit as a bitmask member of @ref flags bitfield field.
    struct doNotEnterOff : public
        field::common::X1T<comms::option::FixedBitLength<1> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(bit);
    };

    /// @brief Definition of "mode" member of @ref flags bitfield field.
    using mode =
        field::common::EnumT<
            Mode,
            comms::option::ValidNumValueRange<0, (int)Mode::NumOfValues - 1>,
            comms::option::FixedBitLength<2>
        >;

    /// @brief Base class of @ref flags field.
    using flagsBase =
        field::common::BitfieldT<
            std::tuple<
                reserved,
                extintSelect,
                extintWake,
                extintBackup,
                field::common::res1T<
                    comms::option::FixedBitLength<1>
                >,
                limitPeakCurr,
                waitTimeFix,
                updateRTC,
                updateEPH,
                field::common::res1T<
                    comms::option::FixedBitLength<3>
                >,
                doNotEnterOff,
                mode,
                field::common::res2T<
                    comms::option::FixedBitLength<13>
                >
            >
        >;

    /// @brief Definition of "flags" field.
    struct flags : public flagsBase
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(flagsBase,
            invalid1,
            extintSelect,
            extintWake,
            extintBackup,
            invalid2,
            limitPeakCurr,
            waitTimeFix,
            updateRTC,
            updateEPH,
            invalid3,
            doNotEnterOff,
            mode,
            invalid4);
    };

    /// @brief Definition of "updatePeriod" field.
    using updatePeriod = field::common::U4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "searchPeriod" field.
    using searchPeriod = field::common::U4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "gridOffset" field.
    using gridOffset = field::common::U4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "onTime" field.
    using onTime = field::common::U2;

    /// @brief Definition of "minAcqTime" field.
    using minAcqTime = field::common::U2;

    /// @brief Definition of "reserved4" field.
    using reserved4 = field::common::res2;

    /// @brief Definition of "reserved5" field.
    using reserved5 = field::common::res2;

    /// @brief Definition of "reserved6" field.
    using reserved6 = field::common::res4;

    /// @brief Definition of "reserved7" field.
    using reserved7 = field::common::res4;

    /// @brief Definition of "reserved8" field.
    using reserved8 = field::common::res1;

    /// @brief Definition of "reserved9" field.
    using reserved9 = field::common::res1;

    /// @brief Definition of "reserved10" field.
    using reserved10 = field::common::res2;

    /// @brief Definition of "reserved11" field.
    using reserved11 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        version,
        reserved1,
        reserved2,
        reserved3,
        flags,
        updatePeriod,
        searchPeriod,
        gridOffset,
        onTime,
        minAcqTime,
        reserved4,
        reserved5,
        reserved6,
        reserved7,
        reserved8,
        reserved9,
        reserved10,
        reserved11
    >;
};

/// @brief Definition of CFG-PM2 message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgPm2Fields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgPm2 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PM2>,
        comms::option::FieldsImpl<CfgPm2Fields::All>,
        comms::option::MsgType<CfgPm2<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PM2>,
        comms::option::FieldsImpl<CfgPm2Fields::All>,
        comms::option::MsgType<CfgPm2<TMsgBase> >
    > Base;
public:
    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref CfgPm2Fields::version field
    ///     @li @b reserved1 for @ref CfgPm2Fields::reserved1 field
    ///     @li @b reserved2 for @ref CfgPm2Fields::reserved2 field
    ///     @li @b reserved3 for @ref CfgPm2Fields::reserved3 field
    ///     @li @b flags for @ref CfgPm2Fields::flags field
    ///     @li @b updatePeriod for @ref CfgPm2Fields::updatePeriod field
    ///     @li @b searchPeriod for @ref CfgPm2Fields::searchPeriod field
    ///     @li @b gridOffset for @ref CfgPm2Fields::gridOffset field
    ///     @li @b onTime for @ref CfgPm2Fields::onTime field
    ///     @li @b minAcqTime for @ref CfgPm2Fields::minAcqTime field
    ///     @li @b reserved4 for @ref CfgPm2Fields::reserved4 field
    ///     @li @b reserved5 for @ref CfgPm2Fields::reserved5 field
    ///     @li @b reserved6 for @ref CfgPm2Fields::reserved6 field
    ///     @li @b reserved7 for @ref CfgPm2Fields::reserved7 field
    ///     @li @b reserved8 for @ref CfgPm2Fields::reserved8 field
    ///     @li @b reserved9 for @ref CfgPm2Fields::reserved9 field
    ///     @li @b reserved10 for @ref CfgPm2Fields::reserved10 field
    ///     @li @b reserved11 for @ref CfgPm2Fields::reserved11 field
    COMMS_MSG_FIELDS_ACCESS(Base,
        version,
        reserved1,
        reserved2,
        reserved3,
        flags,
        updatePeriod,
        searchPeriod,
        gridOffset,
        onTime,
        minAcqTime,
        reserved4,
        reserved5,
        reserved6,
        reserved7,
        reserved8,
        reserved9,
        reserved10,
        reserved11
    );

    /// @brief Default constructor
    CfgPm2() = default;

    /// @brief Copy constructor
    CfgPm2(const CfgPm2&) = default;

    /// @brief Move constructor
    CfgPm2(CfgPm2&& other) = default;

    /// @brief Destructor
    virtual ~CfgPm2() = default;

    /// @brief Copy assignment
    CfgPm2& operator=(const CfgPm2&) = default;

    /// @brief Move assignment
    CfgPm2& operator=(CfgPm2&&) = default;
};


}  // namespace message

}  // namespace ublox

