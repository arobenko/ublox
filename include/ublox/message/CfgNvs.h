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
    CfgNvsField_mask_alm = 17,
    CfgNvsField_mask_aop = 29,
    CfgNvsField_mask_numOfValues
};

enum
{
    CfgNvsField_deviceMask_devBBR,
    CfgNvsField_deviceMask_devFlash,
    CfgNvsField_deviceMask_devEEPROM,
    CfgNvsField_deviceMask_reserved0,
    CfgNvsField_deviceMask_devSpiFlash,
    CfgNvsField_deviceMask_numOfValues
};


using CfgNvsField_mask =
    field::common::X4T<
        comms::option::BitmaskReservedBits<0xdffdffff, 0>
    >;

using CfgNvsField_clearMask = CfgNvsField_mask;
using CfgNvsField_saveMask = CfgNvsField_mask;
using CfgNvsField_loadMask = CfgNvsField_mask;
using CfgNvsField_deviceMask =
    field::common::X1T<
        comms::option::BitmaskReservedBits<0xe8, 0>
    >;

using CfgNvsFields = std::tuple<
    CfgNvsField_clearMask,
    CfgNvsField_saveMask,
    CfgNvsField_loadMask,
    CfgNvsField_deviceMask
>;

template <typename TMsgBase = Message>
class CfgNvs : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NVS>,
        comms::option::FieldsImpl<CfgNvsFields>,
        comms::option::DispatchImpl<CfgNvs<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NVS>,
        comms::option::FieldsImpl<CfgNvsFields>,
        comms::option::DispatchImpl<CfgNvs<TMsgBase> >
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

    CfgNvs() = default;
    CfgNvs(const CfgNvs&) = default;
    CfgNvs(CfgNvs&& other) = default;
    virtual ~CfgNvs() = default;

    CfgNvs& operator=(const CfgNvs&) = default;
    CfgNvs& operator=(CfgNvs&&) = default;
};


}  // namespace message

}  // namespace ublox

