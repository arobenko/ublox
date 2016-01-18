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

enum
{
    CfgEsfgwtField_flags_setVehicle = 12,
    CfgEsfgwtField_flags_setTime,
    CfgEsfgwtField_flags_setWt,
    CfgEsfgwtField_flags_numOfValues
};

using CfgEsfgwtField_flags =
    field::common::X2T<
        comms::option::BitmaskReservedBits<0x8fff, 0>
    >;
using CfgEsfgwtField_id = field::common::U2;
using CfgEsfgwtField_wtFactor =
    field::common::U4T<
        comms::option::ScalingRatio<1, 1000000L>
    >;
using CfgEsfgwtField_reserved1 = field::common::res4;
using CfgEsfgwtField_wtQuantError =
    field::common::U4T<
        comms::option::ScalingRatio<1, 1000000L>
    >;
using CfgEsfgwtField_timeTagFactor =
    field::common::U4T<
        comms::option::ScalingRatio<1, 1000000L>
    >;
using CfgEsfgwtField_wtCountMax = field::common::U4;
using CfgEsfgwtField_timeTagMax = field::common::U4;
using CfgEsfgwtField_wtLatency =
    field::common::U2T<
        field::common::Scaling_ms2s
    >;
using CfgEsfgwtField_reserved2 = field::common::res2;
using CfgEsfgwtField_wtFrequency = field::common::U1;
using CfgEsfgwtField_reserved3 = field::common::res1;
using CfgEsfgwtField_speedDeadBand =
    field::common::U2T<
        field::common::Scaling_cm2m
    >;
using CfgEsfgwtField_reserved4 = field::common::res4;
using CfgEsfgwtField_reserved5 = field::common::res4;

using CfgEsfgwtFields = std::tuple<
    CfgEsfgwtField_flags,
    CfgEsfgwtField_id,
    CfgEsfgwtField_wtFactor,
    CfgEsfgwtField_reserved1,
    CfgEsfgwtField_wtQuantError,
    CfgEsfgwtField_timeTagFactor,
    CfgEsfgwtField_wtCountMax,
    CfgEsfgwtField_timeTagMax,
    CfgEsfgwtField_wtLatency,
    CfgEsfgwtField_reserved2,
    CfgEsfgwtField_wtFrequency,
    CfgEsfgwtField_reserved3,
    CfgEsfgwtField_speedDeadBand,
    CfgEsfgwtField_reserved4,
    CfgEsfgwtField_reserved5
>;

template <typename TMsgBase = Message>
class CfgEsfgwt : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_ESFGWT>,
        comms::option::FieldsImpl<CfgEsfgwtFields>,
        comms::option::DispatchImpl<CfgEsfgwt<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_ESFGWT>,
        comms::option::FieldsImpl<CfgEsfgwtFields>,
        comms::option::DispatchImpl<CfgEsfgwt<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_flags,
        FieldIdx_id,
        FieldIdx_wtFactor,
        FieldIdx_reserved1,
        FieldIdx_wtQuantError,
        FieldIdx_timeTagFactor,
        FieldIdx_wtCountMax,
        FieldIdx_timeTagMax,
        FieldIdx_wtLatency,
        FieldIdx_reserved2,
        FieldIdx_wtFrequency,
        FieldIdx_reserved3,
        FieldIdx_speedDeadBand,
        FieldIdx_reserved4,
        FieldIdx_reserved5,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgEsfgwt() = default;

    /// @brief Copy constructor
    CfgEsfgwt(const CfgEsfgwt&) = default;

    /// @brief Move constructor
    CfgEsfgwt(CfgEsfgwt&& other) = default;

    /// @brief Destructor
    virtual ~CfgEsfgwt() = default;

    /// @brief Copy assignment
    CfgEsfgwt& operator=(const CfgEsfgwt&) = default;

    /// @brief Move assignment
    CfgEsfgwt& operator=(CfgEsfgwt&&) = default;
};


}  // namespace message

}  // namespace ublox

