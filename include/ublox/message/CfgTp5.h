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
/// @brief Contains definition of CFG-TP5 message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-TP5 message fields.
/// @see CfgTp5
struct CfgTp5Fields
{
    /// @brief Value enumeration for @ref tpIdx field
    using TpIdx = field::cfg::TpIdx;

    /// @brief Bits access enumeration for @ref flags bitmask field.
    enum
    {
        flags_active, ///< @b active bit index
        flags_logGpsFreq, ///< @b logGpsFreq bit index
        flags_lockedOtherSet, ///< @b lockedOtherSet bit index
        flags_isFreq, ///< @b isFreq bit index
        flags_isLength, ///< @b isLength bit index
        flags_alignToTow, ///< @b alignToTow bit index
        flags_polarity, ///< @b polarity bit index
        flags_gridUtcGps, ///< @b gridUtcGps bit index
        flags_numOfValues///< number of available bits
    };

    /// @brief Definition of "tpIdx" field.
    using tpIdx = field::cfg::tpIdx;

    /// @brief Definition of "reserved0" field.
    using reserved0 = field::common::res1;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "antCableDelay" field.
    using antCableDelay = field::common::I2T<field::common::Scaling_ns2s>;

    /// @brief Definition of "rfGroupDelay" field.
    using rfGroupDelay = field::common::I2T<field::common::Scaling_ns2s>;

    /// @brief Definition of "freqPeriod" field.
    using freqPeriod = field::common::U4T<field::common::Scaling_us2s>;

    /// @brief Definition of "freqPeriodLock" field.
    using freqPeriodLock = field::common::U4T<field::common::Scaling_us2s>;

    /// @brief Definition of "pulseLenRatio" field.
    using pulseLenRatio = field::common::U4;

    /// @brief Definition of "pulseLenRatioLock" field.
    using pulseLenRatioLock = field::common::U4;

    /// @brief Definition of "userConfigDelay" field.
    using userConfigDelay = field::common::I4T<field::common::Scaling_ns2s>;

    /// @brief Definition of "flags" field.
    using flags =
        field::common::X4T<
            comms::option::BitmaskReservedBits<0xffffff00, 0>
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        tpIdx,
        reserved0,
        reserved1,
        antCableDelay,
        rfGroupDelay,
        freqPeriod,
        freqPeriodLock,
        pulseLenRatio,
        pulseLenRatioLock,
        userConfigDelay,
        flags
    >;
};

/// @brief Definition of CFG-TP5 message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref CfgTp5Fields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgTp5 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TP5>,
        comms::option::FieldsImpl<CfgTp5Fields::All>,
        comms::option::DispatchImpl<CfgTp5<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TP5>,
        comms::option::FieldsImpl<CfgTp5Fields::All>,
        comms::option::DispatchImpl<CfgTp5<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_tpIdx, ///< @b tpIdx field, see @ref CfgTp5Fields::tpIdx
        FieldIdx_reserved0, ///< @b reserved0 field, see @ref CfgTp5Fields::reserved0
        FieldIdx_reserved1, ///< @b reserved1 field, see @ref CfgTp5Fields::reserved1
        FieldIdx_antCableDelay, ///< @b antCableDelay field, see @ref CfgTp5Fields::antCableDelay
        FieldIdx_rfGroupDelay, ///< @b rfGroupDelay field, see @ref CfgTp5Fields::rfGroupDelay
        FieldIdx_freqPeriod, ///< @b freqPeriod field, see @ref CfgTp5Fields::freqPeriod
        FieldIdx_freqPeriodLock, ///< @b freqPeriodLock field, see @ref CfgTp5Fields::freqPeriodLock
        FieldIdx_pulseLenRatio, ///< @b pulseLenRatio field, see @ref CfgTp5Fields::pulseLenRatio
        FieldIdx_pulseLenRatioLock, ///< @b pulseLenRatioLock field, see @ref CfgTp5Fields::pulseLenRatioLock
        FieldIdx_userConfigDelay, ///< @b userConfigDelay field, see @ref CfgTp5Fields::userConfigDelay
        FieldIdx_flags, ///< @b flags field, see @ref CfgTp5Fields::flags
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgTp5() = default;

    /// @brief Copy constructor
    CfgTp5(const CfgTp5&) = default;

    /// @brief Move constructor
    CfgTp5(CfgTp5&& other) = default;

    /// @brief Destructor
    virtual ~CfgTp5() = default;

    /// @brief Copy assignment
    CfgTp5& operator=(const CfgTp5&) = default;

    /// @brief Move assignment
    CfgTp5& operator=(CfgTp5&&) = default;
};


}  // namespace message

}  // namespace ublox

