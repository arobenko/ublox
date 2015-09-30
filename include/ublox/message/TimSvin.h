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

using TimSvinField_dur = field::common::U4;
using TimSvinField_meanX = field::common::I4T<field::common::Scaling_cm2m>;
using TimSvinField_meanY = TimSvinField_meanX;
using TimSvinField_meanZ = TimSvinField_meanX;
using TimSvinField_meanV = field::common::U4T<comms::option::ScalingRatio<1, 1000000L> >;
using TimSvinField_obs = field::common::U4;
using TimSvinField_valid = field::common::U1;
using TimSvinField_active = field::common::U1;
using TimSvinField_reserved = field::common::res2;

using TimSvinFields = std::tuple<
    TimSvinField_dur,
    TimSvinField_meanX,
    TimSvinField_meanY,
    TimSvinField_meanZ,
    TimSvinField_meanV,
    TimSvinField_obs,
    TimSvinField_valid,
    TimSvinField_active,
    TimSvinField_reserved
>;

template <typename TMsgBase = Message>
class TimSvin : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_SVIN>,
        comms::option::FieldsImpl<TimSvinFields>,
        comms::option::DispatchImpl<TimSvin<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_SVIN>,
        comms::option::FieldsImpl<TimSvinFields>,
        comms::option::DispatchImpl<TimSvin<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_dur,
        FieldIdx_meanX,
        FieldIdx_meanY,
        FieldIdx_meanZ,
        FieldIdx_meanV,
        FieldIdx_obs,
        FieldIdx_valid,
        FieldIdx_active,
        FieldIdx_reserved,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    TimSvin() = default;
    TimSvin(const TimSvin&) = default;
    TimSvin(TimSvin&& other) = default;
    virtual ~TimSvin() = default;

    TimSvin& operator=(const TimSvin&) = default;
    TimSvin& operator=(TimSvin&&) = default;
};


}  // namespace message

}  // namespace ublox

