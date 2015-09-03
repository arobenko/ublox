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

using CfgPrtUart_PortId = CfgPrt_PortId;
using CfgPrtUart_Polarity = field::cfg::Polarity;

enum class CfgPrtUart_BitLength : std::uint8_t
{
    Bits_5,
    Bits_6,
    Bits_7,
    Bits_8,
    NumOfValues
};

enum class CfgPrtUart_Parity : std::uint8_t
{
    Even,
    Odd,
    NoParity = 4,
    NoParity2
};

enum class CfgPrtUart_StopBits : std::uint8_t
{
    One,
    OneAndHalf,
    Two,
    Half,
    NumOfValues
};

struct CfgPrtUart_ParityValidator
{
    template <typename TField>
    bool operator()(const TField& field) const
    {
        auto value = field.value();
        return
            (value == CfgPrtUart_Parity::Even) ||
            (value == CfgPrtUart_Parity::Odd) ||
            (value == CfgPrtUart_Parity::NoParity) ||
            (value == CfgPrtUart_Parity::NoParity2);
    }
};

enum
{
    CfgPrtUartField_mode_reserved1,
    CfgPrtUartField_mode_charLen,
    CfgPrtUartField_mode_reserved2,
    CfgPrtUartField_mode_parity,
    CfgPrtUartField_mode_nStopBits,
    CfgPrtUartField_mode_reserved3,
    CfgPrtUartField_mode_numOfValues
};

using CfgPrtUartField_portID =
    comms::field::EnumValue<
        field::common::FieldBase,
        CfgPrt_PortId,
        comms::option::ValidNumValueRange<(int)CfgPrt_PortId::UART, (int)CfgPrt_PortId::UART>,
        comms::option::DefaultNumValue<(int)CfgPrt_PortId::UART>
    >;
using CfgPrtUartField_reserved0 = field::common::res1;
using CfgPrtUartField_txReady = field::cfg::txReady;
using CfgPrtUartField_mode =
    comms::field::Bitfield<
        field::common::FieldBase,
        std::tuple<
            field::common::U1T<
                comms::option::FixedBitLength<6>,
                comms::option::BitmaskReservedBits<0xff, 0x10>,
                comms::option::DefaultNumValue<0x10>
            >,
            comms::field::EnumValue<
                field::common::FieldBase,
                CfgPrtUart_BitLength,
                comms::option::FixedBitLength<2>,
                comms::option::ValidNumValueRange<0, (int)CfgPrtUart_BitLength::NumOfValues - 1>,
                comms::option::DefaultNumValue<(int)CfgPrtUart_BitLength::Bits_8>
            >,
            field::common::U1T<
                comms::option::FixedBitLength<1>,
                comms::option::BitmaskReservedBits<0xff, 0x0>
            >,
            comms::field::EnumValue<
                field::common::FieldBase,
                CfgPrtUart_Parity,
                comms::option::FixedBitLength<3>,
                comms::option::ContentsValidator<CfgPrtUart_ParityValidator>
            >,
            comms::field::EnumValue<
                field::common::FieldBase,
                CfgPrtUart_StopBits,
                comms::option::FixedBitLength<2>,
                comms::option::ValidNumValueRange<0, (int)CfgPrtUart_StopBits::NumOfValues - 1>
            >,
            field::common::U4T<
                comms::option::FixedBitLength<18>,
                comms::option::BitmaskReservedBits<0xffffffff, 0x0>
            >
        >
    >;
using CfgPrtUartField_baudRate = field::common::U4;
using CfgPrtUartField_inProtoMask = field::cfg::inProtoMask;
using CfgPrtUartField_outProtoMask = field::cfg::outProtoMask;
using CfgPrtUartField_flags = field::cfg::prtFlags;
using CfgPrtUartField_reserved5 = field::common::res2;

using CfgPrtUartFields = std::tuple<
    CfgPrtUartField_portID,
    CfgPrtUartField_reserved0,
    CfgPrtUartField_txReady,
    CfgPrtUartField_mode,
    CfgPrtUartField_baudRate,
    CfgPrtUartField_inProtoMask,
    CfgPrtUartField_outProtoMask,
    CfgPrtUartField_flags,
    CfgPrtUartField_reserved5
>;

template <typename TMsgBase = Message>
class CfgPrtUart : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtUartFields>,
        comms::option::DispatchImpl<CfgPrtUart<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtUartFields>,
        comms::option::DispatchImpl<CfgPrtUart<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_portID,
        FieldIdx_reserved0,
        FieldIdx_txReady,
        FieldIdx_mode,
        FieldIdx_baudRate,
        FieldIdx_inProtoMask,
        FieldIdx_outProtoMask,
        FieldIdx_flags,
        FieldIdx_reserved5,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    CfgPrtUart() = default;
    CfgPrtUart(const CfgPrtUart&) = default;
    CfgPrtUart(CfgPrtUart&& other) = default;
    virtual ~CfgPrtUart() = default;

    CfgPrtUart& operator=(const CfgPrtUart&) = default;
    CfgPrtUart& operator=(CfgPrtUart&&) = default;

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
        if (portIdField.value() != CfgPrt_PortId::UART) {
            return comms::ErrorStatus::InvalidMsgData;
        }

        return Base::template readFieldsFrom<FieldIdx_reserved0>(iter, len);
    }

    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& portIdField = std::get<FieldIdx_portID>(allFields);
        if (portIdField.value() == CfgPrt_PortId::UART) {
            return false;
        }

        portIdField.value() = CfgPrt_PortId::UART;
        return true;
    }

};


}  // namespace message

}  // namespace ublox





