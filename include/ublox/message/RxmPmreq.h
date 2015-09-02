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

#include "ublox/field/rxm.h"

namespace ublox
{

namespace message
{

enum
{
    RxmPmreqField_flags_backup = 1
};

using RxmPmreqField_duration = field::common::U4T<field::common::Scaling_ms2s>;
using RxmPmreqField_flags =
    field::common::X4T<
        comms::option::BitmaskReservedBits<0xfffffffd, 0>
    >;

using RxmPmreqFields = std::tuple<
    RxmPmreqField_duration,
    RxmPmreqField_flags
>;


template <typename TMsgBase = Message>
class RxmPmreq : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_PMREQ>,
        comms::option::FieldsImpl<RxmPmreqFields>,
        comms::option::DispatchImpl<RxmPmreq<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_PMREQ>,
        comms::option::FieldsImpl<RxmPmreqFields>,
        comms::option::DispatchImpl<RxmPmreq<TMsgBase> >
    > Base;
public:

    enum FieldIdx
    {
        FieldIdx_duration,
        FieldIdx_flags,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    RxmPmreq() = default;
    RxmPmreq(const RxmPmreq&) = default;
    RxmPmreq(RxmPmreq&& other) = default;
    virtual ~RxmPmreq() = default;

    RxmPmreq& operator=(const RxmPmreq&) = default;
    RxmPmreq& operator=(RxmPmreq&&) = default;
};


}  // namespace message

}  // namespace ublox





