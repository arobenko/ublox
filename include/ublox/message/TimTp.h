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
    TimTpField_flags_timeBase,
    TimTpField_flags_utc,
    TimTpField_flags_numOfValues
};

using TimTpField_towMS = field::common::U4T<field::common::Scaling_ms2s>;
using TimTpField_towSubMS = field::common::U4T<comms::option::ScalingRatio<1, 0x20> >;
using TimTpField_qErr = field::common::I4;
using TimTpField_week = field::common::U2;
using TimTpField_flags =
    field::common::X1T<
        comms::option::BitmaskReservedBits<0xfc, 0>
    >;
using TimTpField_reserved = field::common::res1;

using TimTpFields = std::tuple<
    TimTpField_towMS,
    TimTpField_towSubMS,
    TimTpField_qErr,
    TimTpField_week,
    TimTpField_flags,
    TimTpField_reserved
>;

template <typename TMsgBase = Message>
class TimTp : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_TP>,
        comms::option::FieldsImpl<TimTpFields>,
        comms::option::DispatchImpl<TimTp<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_TP>,
        comms::option::FieldsImpl<TimTpFields>,
        comms::option::DispatchImpl<TimTp<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_towMS,
        FieldIdx_towSubMS,
        FieldIdx_qErr,
        FieldIdx_week,
        FieldIdx_flags,
        FieldIdx_reserved,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    TimTp() = default;
    TimTp(const TimTp&) = default;
    TimTp(TimTp&& other) = default;
    virtual ~TimTp() = default;

    TimTp& operator=(const TimTp&) = default;
    TimTp& operator=(TimTp&&) = default;
};


}  // namespace message

}  // namespace ublox

