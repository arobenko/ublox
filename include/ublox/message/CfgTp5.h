//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
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


#pragma once

#include "comms/Message.h"
#include "ublox/Message.h"
#include "ublox/field/MsgId.h"
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

using CfgTp5_TpIdx = field::cfg::TpIdx;

enum
{
    CfgTp5Field_flags_active,
    CfgTp5Field_flags_logGpsFreq,
    CfgTp5Field_flags_lockedOtherSet,
    CfgTp5Field_flags_isFreq,
    CfgTp5Field_flags_isLength,
    CfgTp5Field_flags_alignToTow,
    CfgTp5Field_flags_polarity,
    CfgTp5Field_flags_gridUtcGps,
    CfgTp5Field_flags_numOfValues
};

using CfgTp5Field_tpIdx = field::cfg::tpIdx;
using CfgTp5Field_reserved0 = field::common::res1;
using CfgTp5Field_reserved1 = field::common::res2;
using CfgTp5Field_antCableDelay = field::common::I2T<field::common::Scaling_ns2s>;
using CfgTp5Field_rfGroupDelay = field::common::I2T<field::common::Scaling_ns2s>;
using CfgTp5Field_freqPeriod = field::common::U4T<field::common::Scaling_us2s>;
using CfgTp5Field_freqPeriodLock = field::common::U4T<field::common::Scaling_us2s>;
using CfgTp5Field_pulseLenRatio = field::common::U4;
using CfgTp5Field_pulseLenRatioLock = field::common::U4;
using CfgTp5Field_userConfigDelay = field::common::I4T<field::common::Scaling_ns2s>;
using CfgTp5Field_flags =
    field::common::X4T<
        comms::option::BitmaskReservedBits<0xffffff00, 0>
    >;

using CfgTp5Fields = std::tuple<
    CfgTp5Field_tpIdx,
    CfgTp5Field_reserved0,
    CfgTp5Field_reserved1,
    CfgTp5Field_antCableDelay,
    CfgTp5Field_rfGroupDelay,
    CfgTp5Field_freqPeriod,
    CfgTp5Field_freqPeriodLock,
    CfgTp5Field_pulseLenRatio,
    CfgTp5Field_pulseLenRatioLock,
    CfgTp5Field_userConfigDelay,
    CfgTp5Field_flags
>;

template <typename TMsgBase = Message>
class CfgTp5 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TP5>,
        comms::option::FieldsImpl<CfgTp5Fields>,
        comms::option::DispatchImpl<CfgTp5<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TP5>,
        comms::option::FieldsImpl<CfgTp5Fields>,
        comms::option::DispatchImpl<CfgTp5<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_tpIdx,
        FieldIdx_reserved0,
        FieldIdx_reserved1,
        FieldIdx_antCableDelay,
        FieldIdx_rfGroupDelay,
        FieldIdx_freqPeriod,
        FieldIdx_freqPeriodLock,
        FieldIdx_pulseLenRatio,
        FieldIdx_pulseLenRatioLock,
        FieldIdx_userConfigDelay,
        FieldIdx_flags,
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

