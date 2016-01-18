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

enum class NavEkfstatus_CalibStatus : std::uint8_t
{
    NoCalibration,
    Calibrating,
    CoarseCalibration,
    FineCalibration,
    NumOfValues
};

enum
{
    NavEkfstatusField_calibStatus_calibTacho,
    NavEkfstatusField_calibStatus_calibGyro,
    NavEkfstatusField_calibStatus_calibGyroB,
    NavEkfstatusField_calibStatus_reserved,
    NavEkfstatusField_calibStatus_numOfValues
};

enum
{
    NavEkfstatusField_measUsed_pulse,
    NavEkfstatusField_measUsed_direction,
    NavEkfstatusField_measUsed_gyro,
    NavEkfstatusField_measUsed_temp,
    NavEkfstatusField_measUsed_pos,
    NavEkfstatusField_measUsed_vel,
    NavEkfstatusField_measUsed_errGyro,
    NavEkfstatusField_measUsed_errPulse,
    NavEkfstatusField_measUsed_numOfValues
};

using NavEkfstatusField_pulses = field::common::I4;
using NavEkfstatusField_period = field::common::I4T<field::common::Scaling_ms2s>;
using NavEkfstatusField_gyroMean = field::common::U4T<comms::option::ScalingRatio<1, 100> >;
using NavEkfstatusField_temperature = field::common::I2T<comms::option::ScalingRatio<1, 0x100> >;
using NavEkfstatusField_direction = field::common::I1;
using NavEkfstatusField_calibStatus_calib =
    comms::field::EnumValue<
        field::common::FieldBase,
        NavEkfstatus_CalibStatus,
        comms::option::FixedBitLength<2>,
        comms::option::ValidNumValueRange<0, (int)NavEkfstatus_CalibStatus::NumOfValues - 1>
    >;
using NavEkfstatusField_calibStatus =
    comms::field::Bitfield<
        field::common::FieldBase,
        std::tuple<
            NavEkfstatusField_calibStatus_calib,
            NavEkfstatusField_calibStatus_calib,
            NavEkfstatusField_calibStatus_calib,
            field::common::res1T<comms::option::FixedBitLength<2> >
        >
    >;
using NavEkfstatusField_pulseScale = field::common::I4T<comms::option::ScalingRatio<1, 100000> >;
using NavEkfstatusField_gyroBias = field::common::I4T<comms::option::ScalingRatio<1, 100000> >;
using NavEkfstatusField_gyroScale = field::common::I4T<comms::option::ScalingRatio<1, 100000> >;
using NavEkfstatusField_accPulseScale = field::common::I2T<comms::option::ScalingRatio<1, 10000> >;
using NavEkfstatusField_accGyroBias = field::common::I2T<comms::option::ScalingRatio<1, 10000> >;
using NavEkfstatusField_accGyroScale = field::common::I2T<comms::option::ScalingRatio<1, 10000> >;
using NavEkfstatusField_measUsed = field::common::X1;
using NavEkfstatusField_reserved2 = field::common::res1;

using NavEkfstatusFields = std::tuple<
    NavEkfstatusField_pulses,
    NavEkfstatusField_period,
    NavEkfstatusField_gyroMean,
    NavEkfstatusField_temperature,
    NavEkfstatusField_direction,
    NavEkfstatusField_calibStatus,
    NavEkfstatusField_pulseScale,
    NavEkfstatusField_gyroBias,
    NavEkfstatusField_gyroScale,
    NavEkfstatusField_accPulseScale,
    NavEkfstatusField_accGyroBias,
    NavEkfstatusField_accGyroScale,
    NavEkfstatusField_measUsed,
    NavEkfstatusField_reserved2
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

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_pulses,
        FieldIdx_period,
        FieldIdx_gyroMean,
        FieldIdx_temperature,
        FieldIdx_direction,
        FieldIdx_calibStatus,
        FieldIdx_pulseScale,
        FieldIdx_gyroBias,
        FieldIdx_gyroScale,
        FieldIdx_accPulseScale,
        FieldIdx_accGyroBias,
        FieldIdx_accGyroScale,
        FieldIdx_measUsed,
        FieldIdx_reserved2,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    NavEkfstatus() = default;

    /// @brief Copy constructor
    NavEkfstatus(const NavEkfstatus&) = default;

    /// @brief Move constructor
    NavEkfstatus(NavEkfstatus&& other) = default;

    /// @brief Destructor
    virtual ~NavEkfstatus() = default;

    /// @brief Copy assignment
    NavEkfstatus& operator=(const NavEkfstatus&) = default;

    /// @brief Move assignment
    NavEkfstatus& operator=(NavEkfstatus&&) = default;
};


}  // namespace message

}  // namespace ublox





