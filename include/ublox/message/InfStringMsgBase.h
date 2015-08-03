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

#include "comms/comms.h"
#include "ublox/Message.h"
#include "ublox/field/MsgId.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

using InfStringMsgFields = std::tuple<
    comms::field::String<field::common::FieldBase>
>;


template <MsgId TId, typename TMsgBase = Message>
class InfStringMsgBase : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<TId>,
        comms::option::FieldsImpl<InfStringMsgFields>,
        comms::option::DispatchImpl<InfStringMsgBase<TId, TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<TId>,
        comms::option::FieldsImpl<InfStringMsgFields>,
        comms::option::DispatchImpl<InfStringMsgBase<TId, TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_String,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    InfStringMsgBase() = default;
    InfStringMsgBase(const InfStringMsgBase&) = default;
    InfStringMsgBase(InfStringMsgBase&& other) = default;
    virtual ~InfStringMsgBase() = default;

    InfStringMsgBase& operator=(const InfStringMsgBase&) = default;
    InfStringMsgBase& operator=(InfStringMsgBase&&) = default;
};


}  // namespace message

}  // namespace ublox

