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

using MonRxbufField_pending =
    comms::field::ArrayList<
        field::common::FieldBase,
        field::common::U2,
        comms::option::SequenceFixedSize<6>
    >;
using MonRxbufField_usage =
    comms::field::ArrayList<
        field::common::FieldBase,
        field::common::U1,
        comms::option::SequenceFixedSize<6>
    >;
using MonRxbufField_peakUsage = MonRxbufField_usage;

using MonRxbufFields = std::tuple<
    MonRxbufField_pending,
    MonRxbufField_usage,
    MonRxbufField_peakUsage
>;


template <typename TMsgBase = Message>
class MonRxbuf : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_RXBUF>,
        comms::option::FieldsImpl<MonRxbufFields>,
        comms::option::DispatchImpl<MonRxbuf<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_RXBUF>,
        comms::option::FieldsImpl<MonRxbufFields>,
        comms::option::DispatchImpl<MonRxbuf<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_pending,
        FieldIdx_usage,
        FieldIdx_peakUsage,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    MonRxbuf() = default;
    MonRxbuf(const MonRxbuf&) = default;
    MonRxbuf(MonRxbuf&& other) = default;
    virtual ~MonRxbuf() = default;

    MonRxbuf& operator=(const MonRxbuf&) = default;
    MonRxbuf& operator=(MonRxbuf&&) = default;
};


}  // namespace message

}  // namespace ublox

