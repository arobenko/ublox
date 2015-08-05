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

namespace ublox
{

namespace message
{

enum CfgPrtDataIndex
{
    CfgPrtDataIndex_PortId,
    CfgPrtDataIndex_Res0,
    CfgPrtDataIndex_Res1,
    CfgPrtDataIndex_Mode,
    CfgPrtDataIndex_Baudrate,
    CfgPrtDataIndex_InProtoMask,
    CfgPrtDataIndex_OutProtoMask,
    CfgPrtDataIndex_Flags,
    CfgPrtDataIndex_Pad,
    CfgPrtDataIndex_NumOfValues
};

using CfgPrtElement =
    comms::field::Bundle<
        std::tuple<
            field::cfg::PortID,
            field::common::res1,
            field::common::res2,
            field::cfg::Mode,
            field::cfg::Baudrate,
            field::cfg::ProtoMask,
            field::cfg::ProtoMask,
            field::cfg::PrtFlags,
            field::common::res2
        >
    >;

using CfgPrtFields = std::tuple<
    comms::field::ArrayList<
        field::common::FieldBase,
        CfgPrtElement
    >
>;

template <typename TMsgBase = Message>
class CfgPrt : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtFields>,
        comms::option::DispatchImpl<CfgPrt<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtFields>,
        comms::option::DispatchImpl<CfgPrt<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_List,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    CfgPrt() = default;
    CfgPrt(const CfgPrt&) = default;
    CfgPrt(CfgPrt&& other) = default;
    virtual ~CfgPrt() = default;

    CfgPrt& operator=(const CfgPrt&) = default;
    CfgPrt& operator=(CfgPrt&&) = default;

};


}  // namespace message

}  // namespace ublox





