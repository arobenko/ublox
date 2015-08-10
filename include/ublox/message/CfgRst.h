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
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

using CfgRstFields = std::tuple<
    ublox::field::cfg::nav_bbr,
    ublox::field::cfg::Reset,
    ublox::field::common::res1
>;

template <typename TMsgBase = Message>
class CfgRst : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RST>,
        comms::option::FieldsImpl<CfgRstFields>,
        comms::option::DispatchImpl<CfgRst<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RST>,
        comms::option::FieldsImpl<CfgRstFields>,
        comms::option::DispatchImpl<CfgRst<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_NavBbr,
        FieldIdx_Reset,
        FieldIdx_Res,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    CfgRst() = default;
    CfgRst(const CfgRst&) = default;
    CfgRst(CfgRst&& other) = default;
    virtual ~CfgRst() = default;

    CfgRst& operator=(const CfgRst&) = default;
    CfgRst& operator=(CfgRst&&) = default;
};


}  // namespace message

}  // namespace ublox

