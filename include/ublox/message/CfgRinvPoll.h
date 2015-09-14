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

namespace ublox
{

namespace message
{

using CfgRinvPollFields = std::tuple<>;

template <typename TMsgBase = Message>
class CfgRinvPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RINV>,
        comms::option::FieldsImpl<CfgRinvPollFields>,
        comms::option::DispatchImpl<CfgRinvPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RINV>,
        comms::option::FieldsImpl<CfgRinvPollFields>,
        comms::option::DispatchImpl<CfgRinvPoll<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    CfgRinvPoll() = default;
    CfgRinvPoll(const CfgRinvPoll&) = default;
    CfgRinvPoll(CfgRinvPoll&& other) = default;
    virtual ~CfgRinvPoll() = default;

    CfgRinvPoll& operator=(const CfgRinvPoll&) = default;
    CfgRinvPoll& operator=(CfgRinvPoll&&) = default;
};


}  // namespace message

}  // namespace ublox

