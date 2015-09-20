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
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

enum
{
    CfgUsbField_flags_reEnum,
    CfgUsbField_flags_powerMode,
    CfgUsbField_flags_numOfValues
};

using CfgUsbField_vendorID = field::common::U2;
using CfgUsbField_productID = field::common::U2;
using CfgUsbField_reserved1 = field::common::res2;
using CfgUsbField_reserved2 =
    field::common::U2T<
        comms::option::DefaultNumValue<1>,
        comms::option::ValidNumValueRange<1, 1>
    >;
using CfgUsbField_powerConsumption = field::common::U2;
using CfgUsbField_flags =
    field::common::X2T<
        comms::option::BitmaskReservedBits<0xfffc, 0>
    >;
using CfgUsbField_vendorString = field::common::ZString<32>;
using CfgUsbField_productString = field::common::ZString<32>;
using CfgUsbField_serialNumber = field::common::ZString<32>;

using CfgUsbFields = std::tuple<
    CfgUsbField_vendorID,
    CfgUsbField_productID,
    CfgUsbField_reserved1,
    CfgUsbField_reserved2,
    CfgUsbField_powerConsumption,
    CfgUsbField_flags,
    CfgUsbField_vendorString,
    CfgUsbField_productString,
    CfgUsbField_serialNumber
>;

template <typename TMsgBase = Message>
class CfgUsb : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_USB>,
        comms::option::FieldsImpl<CfgUsbFields>,
        comms::option::DispatchImpl<CfgUsb<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_USB>,
        comms::option::FieldsImpl<CfgUsbFields>,
        comms::option::DispatchImpl<CfgUsb<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_vendorID,
        FieldIdx_productID,
        FieldIdx_reserved1,
        FieldIdx_reserved2,
        FieldIdx_powerConsumption,
        FieldIdx_flags,
        FieldIdx_vendorString,
        FieldIdx_productString,
        FieldIdx_serialNumber,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    CfgUsb() = default;
    CfgUsb(const CfgUsb&) = default;
    CfgUsb(CfgUsb&& other) = default;
    virtual ~CfgUsb() = default;

    CfgUsb& operator=(const CfgUsb&) = default;
    CfgUsb& operator=(CfgUsb&&) = default;
};


}  // namespace message

}  // namespace ublox

