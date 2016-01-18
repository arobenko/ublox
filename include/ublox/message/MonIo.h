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
    MonIoField_data_rxBytes,
    MonIoField_data_txBytes,
    MonIoField_data_parityErrs,
    MonIoField_data_framingErrs,
    MonIoField_data_overrunErrs,
    MonIoField_data_breakCond,
    MonIoField_data_rxBusy,
    MonIoField_data_txBusy,
    MonIoField_data_reserved1,
    MonIoField_data_numOfValues
};

using MonIoField_rxBytes = field::common::U4;
using MonIoField_txBytes = field::common::U4;
using MonIoField_parityErrs = field::common::U2;
using MonIoField_framingErrs = field::common::U2;
using MonIoField_overrunErrs = field::common::U2;
using MonIoField_breakCond = field::common::U2;
using MonIoField_rxBusy = field::common::U1;
using MonIoField_txBusy = field::common::U1;
using MonIoField_reserved1 = field::common::U2;

using MonIoField_dataListElem =
    comms::field::Bundle<
        std::tuple<
            MonIoField_rxBytes,
            MonIoField_txBytes,
            MonIoField_parityErrs,
            MonIoField_framingErrs,
            MonIoField_overrunErrs,
            MonIoField_breakCond,
            MonIoField_rxBusy,
            MonIoField_txBusy,
            MonIoField_reserved1
        >
    >;

using MonIoField_data =
    field::common::ListT<MonIoField_dataListElem>;

using MonIoFields = std::tuple<
    MonIoField_data
>;


template <typename TMsgBase = Message>
class MonIo : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_IO>,
        comms::option::FieldsImpl<MonIoFields>,
        comms::option::DispatchImpl<MonIo<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_IO>,
        comms::option::FieldsImpl<MonIoFields>,
        comms::option::DispatchImpl<MonIo<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_data,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    MonIo() = default;
    MonIo(const MonIo&) = default;
    MonIo(MonIo&& other) = default;
    virtual ~MonIo() = default;

    MonIo& operator=(const MonIo&) = default;
    MonIo& operator=(MonIo&&) = default;
};


}  // namespace message

}  // namespace ublox

