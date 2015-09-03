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

#include <iterator>

#include "comms/Message.h"
#include "ublox/Message.h"

#include "ublox/field/cfg.h"
#include "CfgPrt.h"

namespace ublox
{

namespace message
{

using CfgPrtDdc_PortId = CfgPrt_PortId;
using CfgPrtDdc_Polarity = field::cfg::Polarity;

enum
{
    CfgPrtDdcField_mode_reserved1,
    CfgPrtDdcField_mode_slaveAddr,
    CfgPrtDdcField_mode_reserved2,
    CfgPrtDdcField_mode_numOfValues
};

struct CfgPrtDdc_SlaveAddrValidator
{
    template <typename TField>
    bool operator()(const TField& field) const
    {
        auto value = field.value();
        return (0x7 < value) && (value < 0x78) && ((value & 0x1) == 0);
    }
};

using CfgPrtDdcField_portID =
    comms::field::EnumValue<
        field::common::FieldBase,
        CfgPrt_PortId,
        comms::option::ValidNumValueRange<(int)CfgPrt_PortId::DDC, (int)CfgPrt_PortId::DDC>,
        comms::option::DefaultNumValue<(int)CfgPrt_PortId::DDC>
    >;
using CfgPrtDdcField_reserved0 = field::common::res1;
using CfgPrtDdcField_txReady = field::cfg::txReady;
using CfgPrtDdcField_mode =
    comms::field::Bitfield<
        field::common::FieldBase,
        std::tuple<
            field::common::U1T<
                comms::option::FixedBitLength<1>,
                comms::option::BitmaskReservedBits<0xff, 0>
            >,
            field::common::U1T<
                comms::option::FixedBitLength<7>,
                comms::option::ContentsValidator<CfgPrtDdc_SlaveAddrValidator>
            >,
            field::common::U4T<
                comms::option::FixedBitLength<24>,
                comms::option::BitmaskReservedBits<0xffffffff, 0x0>
            >
        >
    >;
using CfgPrtDdcField_reserved3 = field::common::res4;
using CfgPrtDdcField_inProtoMask = field::cfg::inProtoMask;
using CfgPrtDdcField_outProtoMask = field::cfg::outProtoMask;
using CfgPrtDdcField_flags = field::cfg::prtFlags;
using CfgPrtDdcField_reserved5 = field::common::res2;

using CfgPrtDdcFields = std::tuple<
    CfgPrtDdcField_portID,
    CfgPrtDdcField_reserved0,
    CfgPrtDdcField_txReady,
    CfgPrtDdcField_mode,
    CfgPrtDdcField_reserved3,
    CfgPrtDdcField_inProtoMask,
    CfgPrtDdcField_outProtoMask,
    CfgPrtDdcField_flags,
    CfgPrtDdcField_reserved5
>;

template <typename TMsgBase = Message>
class CfgPrtDdc : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtDdcFields>,
        comms::option::DispatchImpl<CfgPrtDdc<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtDdcFields>,
        comms::option::DispatchImpl<CfgPrtDdc<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_portID,
        FieldIdx_reserved0,
        FieldIdx_txReady,
        FieldIdx_mode,
        FieldIdx_reserved3,
        FieldIdx_inProtoMask,
        FieldIdx_outProtoMask,
        FieldIdx_flags,
        FieldIdx_reserved5,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    CfgPrtDdc() = default;
    CfgPrtDdc(const CfgPrtDdc&) = default;
    CfgPrtDdc(CfgPrtDdc&& other) = default;
    virtual ~CfgPrtDdc() = default;

    CfgPrtDdc& operator=(const CfgPrtDdc&) = default;
    CfgPrtDdc& operator=(CfgPrtDdc&&) = default;

protected:
    virtual comms::ErrorStatus readImpl(
        typename Base::ReadIterator& iter,
        std::size_t len) override
    {
        auto es = Base::template readFieldsUntil<FieldIdx_reserved0>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& portIdField = std::get<FieldIdx_portID>(allFields);
        if (portIdField.value() != CfgPrt_PortId::DDC) {
            return comms::ErrorStatus::InvalidMsgData;
        }

        return Base::template readFieldsFrom<FieldIdx_reserved0>(iter, len);
    }

    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& portIdField = std::get<FieldIdx_portID>(allFields);
        if (portIdField.value() == CfgPrt_PortId::DDC) {
            return false;
        }

        portIdField.value() = CfgPrt_PortId::DDC;
        return true;
    }

};


}  // namespace message

}  // namespace ublox





