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
    CfgCfgField_mask_ioPort,
    CfgCfgField_mask_msgConf,
    CfgCfgField_mask_infMsg,
    CfgCfgField_mask_navConf,
    CfgCfgField_mask_rxmConf,
    CfgCfgField_mask_reserved0,
    CfgCfgField_mask_reserved1,
    CfgCfgField_mask_reserved2,
    CfgCfgField_mask_reserved3,
    CfgCfgField_mask_rinvConf,
    CfgCfgField_mask_antConf,
    CfgCfgField_mask_numOfValues
};

enum
{
    CfgCfgField_deviceMask_devBBR,
    CfgCfgField_deviceMask_devFlash,
    CfgCfgField_deviceMask_devEEPROM,
    CfgCfgField_deviceMask_reserved0,
    CfgCfgField_deviceMask_devSpiFlash,
    CfgCfgField_deviceMask_numOfValues
};


using CfgCfgField_mask =
    field::common::X4T<
        comms::option::BitmaskReservedBits<0xfffff9e0, 0>
    >;

using CfgCfgField_clearMask = CfgCfgField_mask;
using CfgCfgField_saveMask = CfgCfgField_mask;
using CfgCfgField_loadMask = CfgCfgField_mask;
using CfgCfgField_deviceMask =
    comms::field::Optional<
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xe8, 0>
        >
    >;

using CfgCfgFields = std::tuple<
    CfgCfgField_clearMask,
    CfgCfgField_saveMask,
    CfgCfgField_loadMask,
    CfgCfgField_deviceMask
>;

template <typename TMsgBase = Message>
class CfgCfg : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_CFG>,
        comms::option::FieldsImpl<CfgCfgFields>,
        comms::option::DispatchImpl<CfgCfg<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_CFG>,
        comms::option::FieldsImpl<CfgCfgFields>,
        comms::option::DispatchImpl<CfgCfg<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_clearMask,
        FieldIdx_saveMask,
        FieldIdx_loadMask,
        FieldIdx_deviceMask,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    CfgCfg() = default;
    CfgCfg(const CfgCfg&) = default;
    CfgCfg(CfgCfg&& other) = default;
    virtual ~CfgCfg() = default;

    CfgCfg& operator=(const CfgCfg&) = default;
    CfgCfg& operator=(CfgCfg&&) = default;
};


}  // namespace message

}  // namespace ublox

