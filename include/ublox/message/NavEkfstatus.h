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

#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

using NavEkfstatusFields = std::tuple<
    field::nav::pulses,
    field::nav::period,
    field::nav::gyromean,
    field::nav::temperature,
    field::nav::direction,
    field::nav::calib_status,
    field::nav::pulse_scale,
    field::nav::gyro_bias,
    field::nav::gyro_scale,
    field::nav::acc_pulse_scale,
    field::nav::acc_gyro_bias,
    field::nav::acc_gyro_scale,
    field::nav::meas_used,
    field::common::res1
>;


template <typename TMsgBase = Message>
class NavEkfstatus : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_EKFSTATUS>,
        comms::option::FieldsImpl<NavEkfstatusFields>,
        comms::option::DispatchImpl<NavEkfstatus<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_EKFSTATUS>,
        comms::option::FieldsImpl<NavEkfstatusFields>,
        comms::option::DispatchImpl<NavEkfstatus<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_Pulses,
        FieldIdx_Period,
        FieldIdx_Gyromean,
        FieldIdx_Temperature,
        FieldIdx_Direction,
        FieldIdx_CalibStatus,
        FieldIdx_PulseScale,
        FieldIdx_GyroBias,
        FieldIdx_GyroScale,
        FieldIdx_AccPulseScale,
        FieldIdx_AccGyroBias,
        FieldIdx_AccGyroScale,
        FieldIdx_MeasUsed,
        FieldIdx_Res,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    NavEkfstatus() = default;
    NavEkfstatus(const NavEkfstatus&) = default;
    NavEkfstatus(NavEkfstatus&& other) = default;
    virtual ~NavEkfstatus() = default;

    NavEkfstatus& operator=(const NavEkfstatus&) = default;
    NavEkfstatus& operator=(NavEkfstatus&&) = default;
};


}  // namespace message

}  // namespace ublox





