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
    struct remainingFlags : public
        field::common::X4T<
            comms::option::FixedBitLength<22>,
            comms::option::BitmaskReservedBits<0xfffffff8, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(waitTimeFix, updateRTC, updateEPH);
    };

    /// @brief Definition of "flags" field.
    struct flags : public
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
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(invalid1, internal, extintSelect, extintWake, extintBackup, invalid2, limitPeakCurr, remainingFlags);
    };

    /// @brief Definition of "updatePeriod" field.
    using updatePeriod = field::common::U4T<comms::option::UnitsMilliseconds>;

    /// @brief Definition of "searchPeriod" field.
    using searchPeriod = field::common::U4T<comms::option::UnitsMilliseconds>;

    /// @brief Definition of "gridOffset" field.
    using gridOffset = field::common::U4T<comms::option::UnitsMilliseconds>;

    /// @brief Definition of "onTime" field.
    using onTime = field::common::U2T<comms::option::UnitsSeconds>;

    /// @brief Definition of "minAcqTime" field.
    using minAcqTime = field::common::U2T<comms::option::UnitsSeconds>;

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
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgPmFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgPm : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PM>,
        comms::option::FieldsImpl<CfgPmFields::All>,
        comms::option::MsgType<CfgPm<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PM>,
        comms::option::FieldsImpl<CfgPmFields::All>,
        comms::option::MsgType<CfgPm<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b version for @ref CfgPmFields::version field
    ///     @li @b reserved1 for @ref CfgPmFields::reserved1 field
    ///     @li @b reserved2 for @ref CfgPmFields::reserved2 field
    ///     @li @b reserved3 for @ref CfgPmFields::reserved3 field
    ///     @li @b flags for @ref CfgPmFields::flags field
    ///     @li @b updatePeriod for @ref CfgPmFields::updatePeriod field
    ///     @li @b searchPeriod for @ref CfgPmFields::searchPeriod field
    ///     @li @b gridOffset for @ref CfgPmFields::gridOffset field
    ///     @li @b onTime for @ref CfgPmFields::onTime field
    ///     @li @b minAcqTime for @ref CfgPmFields::minAcqTime field
    COMMS_MSG_FIELDS_ACCESS(
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
    );

    /// @brief Default constructor
    CfgPm() = default;

    /// @brief Copy constructor
    CfgPm(const CfgPm&) = default;

    /// @brief Move constructor
    CfgPm(CfgPm&& other) = default;

    /// @brief Destructor
    ~CfgPm() = default;

    /// @brief Copy assignment
    CfgPm& operator=(const CfgPm&) = default;

    /// @brief Move assignment
    CfgPm& operator=(CfgPm&&) = default;
};


}  // namespace message

}  // namespace ublox

