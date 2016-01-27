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
/// @brief Contains definition of CFG-PM message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-PM message fields.
/// @see CfgPm
struct CfgPmFields
{
    /// @brief Value enumeration for @ref extintSelect field.
    enum class ExtintSelect : std::uint8_t
    {
        EXTINT0,
        EXTINT1,
        NumOfValues
    };

    /// @brief Common value enumeration for @ref extintWake, @ref extintBackup,
    ///     and @ref limitPeakCurr member fields.
    enum class DisabledEnabled : std::uint8_t
    {
        Disabled,
        Enabled,
        NumOfValues
    };

    /// @brief Value enumeration for @ref extintWake field.
    using ExtintWake = DisabledEnabled;

    /// @brief Value enumeration for @ref extintBackup field.
    using ExtintBackup = DisabledEnabled;

    /// @brief Value enumeration for @ref limitPeakCurr field.
    using LimitPeakCurr = DisabledEnabled;

    /// @brief Use this enumeration to access member fields of @ref flags bitfield.
    enum
    {
        flags_internal = 1, ///< @b index of @b internal member field
        flags_extintSelect, ///< @b index of @b extintSelect member field
        flags_extintWake, ///< @b index of @b extintWake member field
        flags_extintBackup, ///< @b index of @b extintBackup member field
        flags_limitPeakCurr = flags_extintBackup + 2,  ///< @b index of @b limitPeakCurr member field
        flags_remainingFlags, ///< @b index of @b remainingFlags member field
        flags_numOfValues ///< upper limit for available member fields
    };

    /// @brief Bits access enumeration for @ref remainingFlags bitmask field.
    enum
    {
        remainingFlags_waitTimeFix, ///< @b waitTimeFix bit index
        remainingFlags_updateRTC, ///< @b updateRTC bit index
        remainingFlags_updateEPH, ///< @b updateEPH bit index
        remainingFlags_numOfValues ///< number of available bits
    };


    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res1;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res1;

    /// @brief Definition of "internal" member of @ref flags bitfield field.
    using internal =
        field::common::U1T<
            comms::option::FixedBitLength<2>,
            comms::option::DefaultNumValue<1>,
            comms::option::ValidNumValueRange<1, 1>
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

    /// @brief Definition of remaining bits in @ref flags bitfield field as a single bitmask.
    using remainingFlags =
        field::common::X4T<
            comms::option::FixedBitLength<22>,
            comms::option::BitmaskReservedBits<0xfffffff8, 0>
        >;

    /// @brief Definition of "flags" field.
    using flags =
        field::common::BitfieldT<
            std::tuple<
                field::common::res1T<
                    comms::option::FixedBitLength<2>
                >,
                internal,
                extintSelect,
                extintWake,
                extintBackup,
                field::common::res1T<
                    comms::option::FixedBitLength<1>
                >,
                limitPeakCurr,
                remainingFlags
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
        minAcqTime
    >;
};

/// @brief Definition of CFG-PM message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref CfgPmFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgPm : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PM>,
        comms::option::FieldsImpl<CfgPmFields::All>,
        comms::option::DispatchImpl<CfgPm<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PM>,
        comms::option::FieldsImpl<CfgPmFields::All>,
        comms::option::DispatchImpl<CfgPm<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_version, ///< @b version field, see @ref CfgPmFields::version
        FieldIdx_reserved1, ///< @b reserved1 field, see @ref CfgPmFields::reserved1
        FieldIdx_reserved2, ///< @b reserved2 field, see @ref CfgPmFields::reserved2
        FieldIdx_reserved3, ///< @b reserved3 field, see @ref CfgPmFields::reserved3
        FieldIdx_flags, ///< @b flags field, see @ref CfgPmFields::flags
        FieldIdx_updatePeriod, ///< @b updatePeriod field, see @ref CfgPmFields::updatePeriod
        FieldIdx_searchPeriod, ///< @b searchPeriod field, see @ref CfgPmFields::searchPeriod
        FieldIdx_gridOffset, ///< @b gridOffset field, see @ref CfgPmFields::gridOffset
        FieldIdx_onTime, ///< @b onTime field, see @ref CfgPmFields::onTime
        FieldIdx_minAcqTime, ///< @b minAcqTime field, see @ref CfgPmFields::minAcqTime
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgPm() = default;

    /// @brief Copy constructor
    CfgPm(const CfgPm&) = default;

    /// @brief Move constructor
    CfgPm(CfgPm&& other) = default;

    /// @brief Destructor
    virtual ~CfgPm() = default;

    /// @brief Copy assignment
    CfgPm& operator=(const CfgPm&) = default;

    /// @brief Move assignment
    CfgPm& operator=(CfgPm&&) = default;
};


}  // namespace message

}  // namespace ublox

