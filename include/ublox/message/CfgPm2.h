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

    /// @brief Use this enumeration to access member fields of @ref flags bitfield.
    enum
    {
        flags_reserved, ///< @b index of @b reserved member field
        flags_extintSelect, ///< @b index of @b extintSelect member field
        flags_extintWake, ///< @b index of @b extintWake member field
        flags_extintBackup, ///< @b index of @b extintBackup member field
        flags_limitPeakCurr = flags_extintBackup + 2,  ///< @b index of @b limitPeakCurr member field
        flags_waitTimeFix, ///< @b index of @b waitTimeFix member field
        flags_updateRTC, ///< @b index of @b updateRTC member field
        flags_updateEPH, ///< @b index of @b updateEPH member field
        flags_doNotEnterOff = flags_updateEPH + 2,  ///< @b index of @b doNotEnterOff member field
        flags_mode,  ///< @b index of @b mode member field
        flags_numOfValues = flags_mode + 2  ///< number of available member fields
    };

    /// @brief Single bit access enumerator for @ref waitTimeFix member of @ref flags.
    enum
    {
        waitTimeFix_bit, ///< single available bit
        waitTimeFix_numOfValues ///< number of available bits
    };

    /// @brief Single bit access enumerator for @ref updateRTC member of @ref flags.
    enum
    {
        updateRTC_bit, ///< single available bit
        updateRTC_numOfValues ///< number of available bits
    };

    /// @brief Single bit access enumerator for @ref updateEPH member of @ref flags.
    enum
    {
        updateEPH_bit, ///< single available bit
        updateEPH_numOfValues ///< number of available bits
    };

    /// @brief Single bit access enumerator for @ref doNotEnterOff member of @ref flags.
    enum
    {
        doNotEnterOff_bit, ///< single available bit
        doNotEnterOff_numOfValues ///< number of available bits
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
    using waitTimeFix =
        field::common::X1T<comms::option::FixedBitLength<1> >;

    /// @brief Definition of "updateRTC" bit as a bitmask member of @ref flags bitfield field.
    using updateRTC =
        field::common::X1T<comms::option::FixedBitLength<1> >;

    /// @brief Definition of "updateEPH" bit as a bitmask member of @ref flags bitfield field.
    using updateEPH =
        field::common::X1T<comms::option::FixedBitLength<1> >;

    /// @brief Definition of "doNotEnterOff" bit as a bitmask member of @ref flags bitfield field.
    using doNotEnterOff =
        field::common::X1T<comms::option::FixedBitLength<1> >;

    /// @brief Definition of "mode" member of @ref flags bitfield field.
    using mode =
        field::common::EnumT<
            Mode,
            comms::option::ValidNumValueRange<0, (int)Mode::NumOfValues - 1>,
            comms::option::FixedBitLength<2>
        >;

    /// @brief Definition of "flags" field.
    using flags =
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
///     See @ref CfgPm2Fields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgPm2 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PM2>,
        comms::option::FieldsImpl<CfgPm2Fields::All>,
        comms::option::MsgType<CfgPm2<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PM2>,
        comms::option::FieldsImpl<CfgPm2Fields::All>,
        comms::option::MsgType<CfgPm2<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_version, ///< @b version field, see @ref CfgPm2Fields::version
        FieldIdx_reserved1, ///< @b reserved1 field, see @ref CfgPm2Fields::reserved1
        FieldIdx_reserved2, ///< @b reserved2 field, see @ref CfgPm2Fields::reserved2
        FieldIdx_reserved3, ///< @b reserved3 field, see @ref CfgPm2Fields::reserved3
        FieldIdx_flags, ///< @b flags field, see @ref CfgPm2Fields::flags
        FieldIdx_updatePeriod, ///< @b updatePeriod field, see @ref CfgPm2Fields::updatePeriod
        FieldIdx_searchPeriod, ///< @b searchPeriod field, see @ref CfgPm2Fields::searchPeriod
        FieldIdx_gridOffset, ///< @b gridOffset field, see @ref CfgPm2Fields::gridOffset
        FieldIdx_onTime, ///< @b onTime field, see @ref CfgPm2Fields::onTime
        FieldIdx_minAcqTime, ///< @b minAcqTime field, see @ref CfgPm2Fields::minAcqTime
        FieldIdx_reserved4, ///< @b reserved4 field, see @ref CfgPm2Fields::reserved4
        FieldIdx_reserved5, ///< @b reserved5 field, see @ref CfgPm2Fields::reserved5
        FieldIdx_reserved6, ///< @b reserved6 field, see @ref CfgPm2Fields::reserved6
        FieldIdx_reserved7, ///< @b reserved7 field, see @ref CfgPm2Fields::reserved7
        FieldIdx_reserved8, ///< @b reserved8 field, see @ref CfgPm2Fields::reserved8
        FieldIdx_reserved9, ///< @b reserved9 field, see @ref CfgPm2Fields::reserved9
        FieldIdx_reserved10, ///< @b reserved10 field, see @ref CfgPm2Fields::reserved10
        FieldIdx_reserved11, ///< @b reserved11 field, see @ref CfgPm2Fields::reserved11
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        CfgPm2Fields::version& version; ///< @b version field, see @ref CfgPm2Fields::version
        CfgPm2Fields::reserved1& reserved1; ///< @b reserved1 field, see @ref CfgPm2Fields::reserved1
        CfgPm2Fields::reserved2& reserved2; ///< @b reserved2 field, see @ref CfgPm2Fields::reserved2
        CfgPm2Fields::reserved3& reserved3; ///< @b reserved3 field, see @ref CfgPm2Fields::reserved3
        CfgPm2Fields::flags& flags; ///< @b flags field, see @ref CfgPm2Fields::flags
        CfgPm2Fields::updatePeriod& updatePeriod; ///< @b updatePeriod field, see @ref CfgPm2Fields::updatePeriod
        CfgPm2Fields::searchPeriod& searchPeriod; ///< @b searchPeriod field, see @ref CfgPm2Fields::searchPeriod
        CfgPm2Fields::gridOffset& gridOffset; ///< @b gridOffset field, see @ref CfgPm2Fields::gridOffset
        CfgPm2Fields::onTime& onTime; ///< @b onTime field, see @ref CfgPm2Fields::onTime
        CfgPm2Fields::minAcqTime& minAcqTime; ///< @b minAcqTime field, see @ref CfgPm2Fields::minAcqTime
        CfgPm2Fields::reserved4& reserved4; ///< @b reserved4 field, see @ref CfgPm2Fields::reserved4
        CfgPm2Fields::reserved5& reserved5; ///< @b reserved5 field, see @ref CfgPm2Fields::reserved5
        CfgPm2Fields::reserved6& reserved6; ///< @b reserved6 field, see @ref CfgPm2Fields::reserved6
        CfgPm2Fields::reserved7& reserved7; ///< @b reserved7 field, see @ref CfgPm2Fields::reserved7
        CfgPm2Fields::reserved8& reserved8; ///< @b reserved8 field, see @ref CfgPm2Fields::reserved8
        CfgPm2Fields::reserved9& reserved9; ///< @b reserved9 field, see @ref CfgPm2Fields::reserved9
        CfgPm2Fields::reserved10& reserved10; ///< @b reserved10 field, see @ref CfgPm2Fields::reserved10
        CfgPm2Fields::reserved11& reserved11; ///< @b reserved11 field, see @ref CfgPm2Fields::reserved11
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const CfgPm2Fields::version& version; ///< @b version field, see @ref CfgPm2Fields::version
        const CfgPm2Fields::reserved1& reserved1; ///< @b reserved1 field, see @ref CfgPm2Fields::reserved1
        const CfgPm2Fields::reserved2& reserved2; ///< @b reserved2 field, see @ref CfgPm2Fields::reserved2
        const CfgPm2Fields::reserved3& reserved3; ///< @b reserved3 field, see @ref CfgPm2Fields::reserved3
        const CfgPm2Fields::flags& flags; ///< @b flags field, see @ref CfgPm2Fields::flags
        const CfgPm2Fields::updatePeriod& updatePeriod; ///< @b updatePeriod field, see @ref CfgPm2Fields::updatePeriod
        const CfgPm2Fields::searchPeriod& searchPeriod; ///< @b searchPeriod field, see @ref CfgPm2Fields::searchPeriod
        const CfgPm2Fields::gridOffset& gridOffset; ///< @b gridOffset field, see @ref CfgPm2Fields::gridOffset
        const CfgPm2Fields::onTime& onTime; ///< @b onTime field, see @ref CfgPm2Fields::onTime
        const CfgPm2Fields::minAcqTime& minAcqTime; ///< @b minAcqTime field, see @ref CfgPm2Fields::minAcqTime
        const CfgPm2Fields::reserved4& reserved4; ///< @b reserved4 field, see @ref CfgPm2Fields::reserved4
        const CfgPm2Fields::reserved5& reserved5; ///< @b reserved5 field, see @ref CfgPm2Fields::reserved5
        const CfgPm2Fields::reserved6& reserved6; ///< @b reserved6 field, see @ref CfgPm2Fields::reserved6
        const CfgPm2Fields::reserved7& reserved7; ///< @b reserved7 field, see @ref CfgPm2Fields::reserved7
        const CfgPm2Fields::reserved8& reserved8; ///< @b reserved8 field, see @ref CfgPm2Fields::reserved8
        const CfgPm2Fields::reserved9& reserved9; ///< @b reserved9 field, see @ref CfgPm2Fields::reserved9
        const CfgPm2Fields::reserved10& reserved10; ///< @b reserved10 field, see @ref CfgPm2Fields::reserved10
        const CfgPm2Fields::reserved11& reserved11; ///< @b reserved11 field, see @ref CfgPm2Fields::reserved11
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
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
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

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

