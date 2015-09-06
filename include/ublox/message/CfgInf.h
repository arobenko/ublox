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

#include "ublox/Message.h"
#include "ublox/field/MsgId.h"
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

using CfgInf_ProtocolId = field::cfg::ProtocolId;

enum
{
    CfgInfField_element_protocolID,
    CfgInfField_element_reserved0,
    CfgInfField_element_reserved1,
    CfgInfField_element_infMsgMask,
    CfgInfField_element_numOfValues
};

enum
{
    CfgInfField_element_infMsgMask_ddc,
    CfgInfField_element_infMsgMask_uart,
    CfgInfField_element_infMsgMask_uart2,
    CfgInfField_element_infMsgMask_usb,
    CfgInfField_element_infMsgMask_spi,
    CfgInfField_element_infMsgMask_reserved,
    CfgInfField_element_infMsgMask_numOfValues
};

using CfgInfField_protocolID = field::cfg::protocolID;
using CfgInfField_reserved0 = field::common::res1;
using CfgInfField_reserved1 = field::common::res2;
using CfgInfField_mask =
    field::common::X1T<comms::option::BitmaskReservedBits<0xe, 0> >;

using CfgInfField_infMsgMask =
    comms::field::ArrayList<
        field::common::FieldBase,
        CfgInfField_mask,
        comms::option::SequenceFixedSize<6>
    >;

using CfgInfField_element =
    comms::field::Bundle<
        std::tuple<
            CfgInfField_protocolID,
            CfgInfField_reserved0,
            CfgInfField_reserved1,
            CfgInfField_infMsgMask
        >
    >;

using CfgInfField_list =
    comms::field::ArrayList<
        field::common::FieldBase,
        CfgInfField_element
    >;


using CfgInfFields = std::tuple<
    CfgInfField_list
>;

template <typename TMsgBase = Message>
class CfgInf : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_INF>,
        comms::option::FieldsImpl<CfgInfFields>,
        comms::option::DispatchImpl<CfgInf<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_INF>,
        comms::option::FieldsImpl<CfgInfFields>,
        comms::option::DispatchImpl<CfgInf<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_list,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    CfgInf() = default;
    CfgInf(const CfgInf&) = default;
    CfgInf(CfgInf&& other) = default;
    virtual ~CfgInf() = default;

    CfgInf& operator=(const CfgInf&) = default;
    CfgInf& operator=(CfgInf&&) = default;
};


}  // namespace message

}  // namespace ublox

