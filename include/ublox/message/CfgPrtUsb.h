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

using CfgPrtUsb_PortId = CfgPrt_PortId;
using CfgPrtUsb_Polarity = field::cfg::Polarity;

using CfgPrtUsbField_portID =
    comms::field::EnumValue<
        field::common::FieldBase,
        CfgPrt_PortId,
        comms::option::ValidNumValueRange<(int)CfgPrt_PortId::USB, (int)CfgPrt_PortId::USB>,
        comms::option::DefaultNumValue<(int)CfgPrt_PortId::USB>
    >;
using CfgPrtUsbField_reserved0 = field::common::res1;
using CfgPrtUsbField_txReady = field::cfg::txReady;
using CfgPrtUsbField_reserved2 = field::common::res4;
using CfgPrtUsbField_reserved3 = field::common::res4;
using CfgPrtUsbField_inProtoMask = field::cfg::inProtoMask;
using CfgPrtUsbField_outProtoMask = field::cfg::outProtoMask;
using CfgPrtUsbField_reserved4 = field::common::res2;
using CfgPrtUsbField_reserved5 = field::common::res2;

using CfgPrtUsbFields = std::tuple<
    CfgPrtUsbField_portID,
    CfgPrtUsbField_reserved0,
    CfgPrtUsbField_txReady,
    CfgPrtUsbField_reserved2,
    CfgPrtUsbField_reserved3,
    CfgPrtUsbField_inProtoMask,
    CfgPrtUsbField_outProtoMask,
    CfgPrtUsbField_reserved4,
    CfgPrtUsbField_reserved5
>;

template <typename TMsgBase = Message>
class CfgPrtUsb : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtUsbFields>,
        comms::option::DispatchImpl<CfgPrtUsb<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtUsbFields>,
        comms::option::DispatchImpl<CfgPrtUsb<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_portID,
        FieldIdx_reserved0,
        FieldIdx_txReady,
        FieldIdx_reserved2,
        FieldIdx_reserved3,
        FieldIdx_inProtoMask,
        FieldIdx_outProtoMask,
        FieldIdx_reserved4,
        FieldIdx_reserved5,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgPrtUsb() = default;

    /// @brief Copy constructor
    CfgPrtUsb(const CfgPrtUsb&) = default;

    /// @brief Move constructor
    CfgPrtUsb(CfgPrtUsb&& other) = default;

    /// @brief Destructor
    virtual ~CfgPrtUsb() = default;

    /// @brief Copy assignment
    CfgPrtUsb& operator=(const CfgPrtUsb&) = default;

    /// @brief Move assignment
    CfgPrtUsb& operator=(CfgPrtUsb&&) = default;

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
        if (portIdField.value() != CfgPrt_PortId::USB) {
            return comms::ErrorStatus::InvalidMsgData;
        }

        return Base::template readFieldsFrom<FieldIdx_reserved0>(iter, len);
    }

    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& portIdField = std::get<FieldIdx_portID>(allFields);
        if (portIdField.value() == CfgPrt_PortId::USB) {
            return false;
        }

        portIdField.value() = CfgPrt_PortId::USB;
        return true;
    }

};


}  // namespace message

}  // namespace ublox





