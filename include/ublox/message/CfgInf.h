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

using CfgInfFields = std::tuple<
    comms::field::ArrayList<
        field::common::FieldBase,
        comms::field::Bundle<
            std::tuple<
                field::cfg::ProtocolID,
                field::common::res1,
                field::common::res1,
                field::cfg::INFMSG_mask,
                field::cfg::INFMSG_mask,
                field::cfg::INFMSG_mask,
                field::cfg::INFMSG_mask_res
            >
        >
    >
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
        FieldIdx_List,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
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

