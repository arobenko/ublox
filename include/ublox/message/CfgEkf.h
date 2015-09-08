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

enum class CfgEkf_DisableEkf : std::uint8_t
{
    Enabled,
    Disabled,
    NumOfValues
};

enum
{
    CfgEkfActionFlag_ClearTemperatureCompensationTable = 1,
    CfgEkfActionFlag_ClearStoredCalibration = 2,
    CfgEkfActionFlag_SetNominalTachoPulses = 4,
    CfgEkfActionFlag_SetNominalGyroValues = 5,
    CfgEkfActionFlag_SetTempTableConfig = 6,
    CfgEkfActionFlag_SetDirectionPinAndGyroSenseMeaning = 7
};

enum
{
    CfgEkfField_actionFlags_reserved0,
    CfgEkfField_actionFlags_clTab,
    CfgEkfField_actionFlags_clCalib,
    CfgEkfField_actionFlags_reserved1,
    CfgEkfField_actionFlags_nomTacho,
    CfgEkfField_actionFlags_nomGyro,
    CfgEkfField_actionFlags_setTemp,
    CfgEkfField_actionFlags_dir,
    CfgEkfField_actionFlags_numOfValues
};

enum
{
    CfgEkfField_configFlags_pulsesPerM,
    CfgEkfField_configFlags_useSerWt,
    CfgEkfField_configFlags_numOfValues
};

enum
{
    CfgEkfField_inverseFlags_invDir,
    CfgEkfField_inverseFlags_invGyro,
    CfgEkfField_inverseFlags_numOfValues
};

using CfgEkfField_disableEkf =
    comms::field::EnumValue<
        field::common::FieldBase,
        CfgEkf_DisableEkf,
        comms::option::ValidNumValueRange<0, (int)CfgEkf_DisableEkf::NumOfValues - 1>
    >;
using CfgEkfField_actionFlags =
    field::common::X1T<
        comms::option::BitmaskReservedBits<0x9, 0>
    >;
using CfgEkfField_configFlags =
    field::common::X1T<
        comms::option::BitmaskReservedBits<0xfc, 0>
    >;
using CfgEkfField_inverseFlags =
    field::common::X1T<
        comms::option::BitmaskReservedBits<0xfc, 0>
    >;
using CfgEkfField_reserved2 = field::common::res4;
using CfgEkfField_nomPPDist = field::common::U2;
using CfgEkfField_nomZero =
    field::common::U2T<
        comms::option::ValidNumValueRange<2000, 3000>
    >;
using CfgEkfField_nomSens =
    field::common::U1T<
        comms::option::ValidNumValueRange<20, 40>
    >;
using CfgEkfField_rmsTemp =
    field::common::U1T<
        comms::option::ValidNumValueRange<1, 10>,
        comms::option::ScalingRatio<1, 10>
    >;
using CfgEkfField_tempUpdate =
    field::common::U2T<
        comms::option::ValidNumValueRange<9, 0xffff>
    >;

using CfgEkfFields = std::tuple<
    CfgEkfField_disableEkf,
    CfgEkfField_actionFlags,
    CfgEkfField_configFlags,
    CfgEkfField_inverseFlags,
    CfgEkfField_reserved2,
    CfgEkfField_nomPPDist,
    CfgEkfField_nomZero,
    CfgEkfField_nomSens,
    CfgEkfField_rmsTemp,
    CfgEkfField_tempUpdate
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
        FieldIdx_disableEkf,
        FieldIdx_actionFlags,
        FieldIdx_configFlags,
        FieldIdx_inverseFlags,
        FieldIdx_reserved2,
        FieldIdx_nomPPDist,
        FieldIdx_nomZero,
        FieldIdx_nomSens,
        FieldIdx_rmsTemp,
        FieldIdx_tempUpdate,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
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

