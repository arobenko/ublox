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

using CfgFxnFields = std::tuple<
    ublox::field::cfg::fxn_flags,
    ublox::field::cfg::t_reacq,
    ublox::field::cfg::t_acq,
    ublox::field::cfg::t_reacq_off,
    ublox::field::cfg::t_acq_off,
    ublox::field::cfg::t_on,
    ublox::field::cfg::t_off,
    ublox::field::common::res4,
    ublox::field::cfg::base_tow
>;

template <typename TMsgBase = Message>
class CfgFxn : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_FXN>,
        comms::option::FieldsImpl<CfgFxnFields>,
        comms::option::DispatchImpl<CfgFxn<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_FXN>,
        comms::option::FieldsImpl<CfgFxnFields>,
        comms::option::DispatchImpl<CfgFxn<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_Flags,
        FieldIdx_Treacq,
        FieldIdx_Tacq,
        FieldIdx_TreacqOff,
        FieldIdx_TacqOff,
        FieldIdx_Ton,
        FieldIdx_Toff,
        FieldIdx_Res,
        FieldIdx_BaseTow,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    CfgFxn() = default;
    CfgFxn(const CfgFxn&) = default;
    CfgFxn(CfgFxn&& other) = default;
    virtual ~CfgFxn() = default;

    CfgFxn& operator=(const CfgFxn&) = default;
    CfgFxn& operator=(CfgFxn&&) = default;
};


}  // namespace message

}  // namespace ublox

