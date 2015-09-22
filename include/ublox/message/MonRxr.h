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
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

enum
{
    MonRxrField_flags_awake,
    MonRxrField_data_numOfValues
};

using MonRxrField_flags =
    field::common::X1T<
        comms::option::BitmaskReservedBits<0xfe, 0>
    >;

using MonRxrFields = std::tuple<
    MonRxrField_flags
>;


template <typename TMsgBase = Message>
class MonRxr : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_RXR>,
        comms::option::FieldsImpl<MonRxrFields>,
        comms::option::DispatchImpl<MonRxr<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_RXR>,
        comms::option::FieldsImpl<MonRxrFields>,
        comms::option::DispatchImpl<MonRxr<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_flags,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    MonRxr() = default;
    MonRxr(const MonRxr&) = default;
    MonRxr(MonRxr&& other) = default;
    virtual ~MonRxr() = default;

    MonRxr& operator=(const MonRxr&) = default;
    MonRxr& operator=(MonRxr&&) = default;
};


}  // namespace message

}  // namespace ublox

