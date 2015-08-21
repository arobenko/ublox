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

enum class CfgEkfDisable : std::uint8_t
{
    Enabled,
    Disabled,
    NumOfValues
};

using CfgEkfDisabledField =
    comms::field::EnumValue<
        field::common::FieldBase,
        CfgEkfDisable,
        comms::option::ValidNumValueRange<0, (int)CfgEkfDisable::NumOfValues - 1>
    >;

enum CfgEkfActionFlag
{
    CfgEkfActionFlag_ClearTemperatureCompensationTable = 1,
    CfgEkfActionFlag_ClearStoredCalibration = 2,
    CfgEkfActionFlag_SetNominalTachoPulses = 4,
    CfgEkfActionFlag_SetNominalGyroValues = 5,
    CfgEkfActionFlag_SetTempTableConfig = 6,
    CfgEkfActionFlag_SetDirectionPinAndGyroSenseMeaning = 7
};

using CfgEkfActionFlagsField =
    comms::field::BitmaskValue<
        field::common::FieldBase,
        comms::option::FixedLength<1>,
        comms::option::BitmaskReservedBits<0x9, 0>
    >;

enum CfgEkfInverseFlag
{
    CfgEkfInverseFlag_DirectionBackwards,
    CfgEkfInverseFlag_GyroRotationAntyClockwisePositive
};

using CfgEkfInverseFlagsField =
    comms::field::BitmaskValue<
        field::common::FieldBase,
        comms::option::FixedLength<1>,
        comms::option::BitmaskReservedBits<0xfc, 0>
    >;

using CfgEkfNomPpkmField =
    comms::field::IntValue<
        field::common::FieldBase,
        std::uint16_t,
        comms::option::ValidNumValueRange<1100, 45000>
    >;

using CfgEkfNomZeroField =
    comms::field::IntValue<
        field::common::FieldBase,
        std::uint16_t,
        comms::option::ValidNumValueRange<2000, 3000>
    >;

using CfgEkfNomSenseField =
    comms::field::IntValue<
        field::common::FieldBase,
        std::uint8_t,
        comms::option::ValidNumValueRange<20, 40>
    >;

using CfgEkfRmsTempField =
    comms::field::IntValue<
        field::common::FieldBase,
        std::uint8_t,
        comms::option::ValidNumValueRange<1, 10>
    >;

using CfgEkfTempUpdateField =
    comms::field::IntValue<
        field::common::FieldBase,
        std::uint16_t,
        comms::option::ValidNumValueRange<9, 0xffff>
    >;

using CfgEkfFields = std::tuple<
    CfgEkfDisabledField,
    CfgEkfActionFlagsField,
    field::common::res1,
    CfgEkfInverseFlagsField,
    field::common::res4,
    CfgEkfNomPpkmField,
    CfgEkfNomZeroField,
    CfgEkfNomSenseField,
    CfgEkfRmsTempField,
    CfgEkfTempUpdateField
>;

template <typename TMsgBase = Message>
class CfgEkf : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_EKF>,
        comms::option::FieldsImpl<CfgEkfFields>,
        comms::option::DispatchImpl<CfgEkf<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_EKF>,
        comms::option::FieldsImpl<CfgEkfFields>,
        comms::option::DispatchImpl<CfgEkf<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_DisableEkf,
        FieldIdx_ActionFlags,
        FieldIdx_Res,
        FieldIdx_InverseFlags,
        FieldIdx_Res2,
        FieldIdx_NomPpkm,
        FieldIdx_NomZero,
        FieldIdx_NomSens,
        FieldIdx_RmsTemp,
        FieldIdx_TempUpdate,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    CfgEkf() = default;
    CfgEkf(const CfgEkf&) = default;
    CfgEkf(CfgEkf&& other) = default;
    virtual ~CfgEkf() = default;

    CfgEkf& operator=(const CfgEkf&) = default;
    CfgEkf& operator=(CfgEkf&&) = default;
};


}  // namespace message

}  // namespace ublox

