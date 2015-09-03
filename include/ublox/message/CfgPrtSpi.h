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

using CfgPrtSpi_PortId = CfgPrt_PortId;
using CfgPrtSpi_Polarity = field::cfg::Polarity;

enum class CfgPrtSpi_SpiMode : std::uint8_t
{
    Mode_0,
    Mode_1,
    Mode_2,
    Mode_3,
    NumOfValues
};

enum class CfgPrtSpi_FlowControl : std::uint8_t
{
    Disabled,
    Enabled,
    NumOfValues
};

enum
{
    CfgPrtSpiField_mode_reserved1,
    CfgPrtSpiField_mode_spiMode,
    CfgPrtSpiField_mode_reserved2,
    CfgPrtSpiField_mode_flowControl,
    CfgPrtSpiField_mode_reserved3,
    CfgPrtSpiField_mode_ffCnt,
    CfgPrtSpiField_mode_reserved4,
    CfgPrtSpiField_mode_numOfValues
};

using CfgPrtSpiField_portID =
    comms::field::EnumValue<
        field::common::FieldBase,
        CfgPrt_PortId,
        comms::option::ValidNumValueRange<(int)CfgPrt_PortId::SPI, (int)CfgPrt_PortId::SPI>,
        comms::option::DefaultNumValue<(int)CfgPrt_PortId::SPI>
    >;
using CfgPrtSpiField_reserved0 = field::common::res1;
using CfgPrtSpiField_txReady = field::cfg::txReady;
using CfgPrtSpiField_mode =
    comms::field::Bitfield<
        field::common::FieldBase,
        std::tuple<
            field::common::U1T<
                comms::option::FixedBitLength<1>,
                comms::option::BitmaskReservedBits<0xff, 0>
            >,
            comms::field::EnumValue<
                field::common::FieldBase,
                CfgPrtSpi_SpiMode,
                comms::option::FixedBitLength<2>,
                comms::option::ValidNumValueRange<0, (int)CfgPrtSpi_SpiMode::NumOfValues - 1>
            >,
            field::common::U1T<
                comms::option::FixedBitLength<3>,
                comms::option::BitmaskReservedBits<0xff, 0x0>
            >,
            comms::field::EnumValue<
                field::common::FieldBase,
                CfgPrtSpi_FlowControl,
                comms::option::FixedBitLength<1>,
                comms::option::ValidNumValueRange<0, (int)CfgPrtSpi_FlowControl::NumOfValues - 1>
            >,
            field::common::U1T<
                comms::option::FixedBitLength<1>,
                comms::option::BitmaskReservedBits<0xff, 0x0>
            >,
            field::common::U1T<
                comms::option::FixedBitLength<8>
            >,
            field::common::U4T<
                comms::option::FixedBitLength<16>,
                comms::option::BitmaskReservedBits<0xffff, 0x0>
            >
        >
    >;
using CfgPrtSpiField_reserved3 = field::common::res4;
using CfgPrtSpiField_inProtoMask = field::cfg::inProtoMask;
using CfgPrtSpiField_outProtoMask = field::cfg::outProtoMask;
using CfgPrtSpiField_flags = field::cfg::prtFlags;
using CfgPrtSpiField_reserved5 = field::common::res2;

using CfgPrtSpiFields = std::tuple<
    CfgPrtSpiField_portID,
    CfgPrtSpiField_reserved0,
    CfgPrtSpiField_txReady,
    CfgPrtSpiField_mode,
    CfgPrtSpiField_reserved3,
    CfgPrtSpiField_inProtoMask,
    CfgPrtSpiField_outProtoMask,
    CfgPrtSpiField_flags,
    CfgPrtSpiField_reserved5
>;

template <typename TMsgBase = Message>
class CfgPrtSpi : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtSpiFields>,
        comms::option::DispatchImpl<CfgPrtSpi<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtSpiFields>,
        comms::option::DispatchImpl<CfgPrtSpi<TMsgBase> >
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

    CfgPrtSpi() = default;
    CfgPrtSpi(const CfgPrtSpi&) = default;
    CfgPrtSpi(CfgPrtSpi&& other) = default;
    virtual ~CfgPrtSpi() = default;

    CfgPrtSpi& operator=(const CfgPrtSpi&) = default;
    CfgPrtSpi& operator=(CfgPrtSpi&&) = default;

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
        if (portIdField.value() != CfgPrt_PortId::SPI) {
            return comms::ErrorStatus::InvalidMsgData;
        }

        return Base::template readFieldsFrom<FieldIdx_reserved0>(iter, len);
    }

    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& portIdField = std::get<FieldIdx_portID>(allFields);
        if (portIdField.value() == CfgPrt_PortId::SPI) {
            return false;
        }

        portIdField.value() = CfgPrt_PortId::SPI;
        return true;
    }

};


}  // namespace message

}  // namespace ublox





