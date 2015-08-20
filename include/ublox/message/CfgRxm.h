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
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

enum class CfgRxmGpsSensitivityMode : std::uint8_t
{
    Normal,
    FastAcquisition,
    HighAcquisition,
    Auto,
    NumOfValues
};

using CfgRxmGpsSensitivityModeField =
    comms::field::EnumValue<
        field::common::FieldBase,
        CfgRxmGpsSensitivityMode,
        comms::option::ValidNumValueRange<(int)CfgRxmGpsSensitivityMode::Normal, (int)CfgRxmGpsSensitivityMode::NumOfValues - 1>
    >;

enum class CfgRxmLowPowerMode : std::uint8_t
{
    ContinuousTracking,
    FixNow,
    NumOfValues
};

using CfgRxmLowPowerModeField =
    comms::field::EnumValue<
        field::common::FieldBase,
        CfgRxmLowPowerMode,
        comms::option::ValidNumValueRange<(int)CfgRxmLowPowerMode::ContinuousTracking, (int)CfgRxmLowPowerMode::NumOfValues - 1>
    >;

using CfgRxmFields = std::tuple<
    CfgRxmGpsSensitivityModeField,
    CfgRxmLowPowerModeField
>;

template <typename TMsgBase = Message>
class CfgRxm : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RXM>,
        comms::option::FieldsImpl<CfgRxmFields>,
        comms::option::DispatchImpl<CfgRxm<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RXM>,
        comms::option::FieldsImpl<CfgRxmFields>,
        comms::option::DispatchImpl<CfgRxm<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_GpsMode,
        FieldIdx_LowPowerMode,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    CfgRxm() = default;
    CfgRxm(const CfgRxm&) = default;
    CfgRxm(CfgRxm&& other) = default;
    virtual ~CfgRxm() = default;

    CfgRxm& operator=(const CfgRxm&) = default;
    CfgRxm& operator=(CfgRxm&&) = default;
};


}  // namespace message

}  // namespace ublox

