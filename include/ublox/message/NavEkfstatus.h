//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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

/// @file
/// @brief Contains definition of NAV-EKFSTATUS message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-EKFSTATUS message fields.
/// @see NavEkfstatus
struct NavEkfstatusFields
{
    /// @brief Valid enumeration for @ref calibTacho, @ref calibGyro, and
    ///     @ref calibGyroB fields.
    enum class CalibStatus : std::uint8_t
    {
        NoCalibration, ///< no calibration
        Calibrating, ///< calibrating
        CoarseCalibration, ///< coarse calibration
        FineCalibration, ///< find calibration
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "pulses" field.
    using pulses = field::common::I4;

    /// @brief Definition of "period" field.
    using period = field::common::I4T<comms::option::UnitsMilliseconds>;

    /// @brief Definition of "gyroMean" field.
    using gyroMean = field::common::U4T<comms::option::ScalingRatio<1, 100> >;

    /// @brief Definition of "temperature" field.
    using temperature = field::common::I2T<comms::option::ScalingRatio<1, 0x100> >;

    /// @brief Definition of "direction" field.
    using direction = field::common::I1;

    /// @brief Definition of "calibTacho" member field of @ref calibStatus bitfield.
    using calibTacho =
        field::common::EnumT<
            CalibStatus,
            comms::option::FixedBitLength<2>,
            comms::option::ValidNumValueRange<0, (int)CalibStatus::NumOfValues - 1>
        >;

    /// @brief Definition of "calibGyro" member field of @ref calibStatus bitfield
    using calibGyro = calibTacho;

    /// @brief Definition of "calibGyroB" member field of @ref calibStatus bitfield
    using calibGyroB = calibTacho;

    /// @brief Definition of "calibStatus" field.
    struct calibStatus : public
        field::common::BitfieldT<
            std::tuple<
                calibTacho,
                calibGyro,
                calibGyroB,
                field::common::res1T<comms::option::FixedBitLength<2> >
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(calibTacho, calibGyro, calibGyroB, reserved);
    };

    /// @brief Definition of "pulseScale" field.
    using pulseScale = field::common::I4T<comms::option::ScalingRatio<1, 100000> >;

    /// @brief Definition of "gyroBias" field.
    using gyroBias = field::common::I4T<comms::option::ScalingRatio<1, 100000> >;

    /// @brief Definition of "gyroScale" field.
    using gyroScale = field::common::I4T<comms::option::ScalingRatio<1, 100000> >;

    /// @brief Definition of "accPulseScale" field.
    using accPulseScale = field::common::I2T<comms::option::ScalingRatio<1, 10000> >;

    /// @brief Definition of "accGyroBias" field.
    using accGyroBias = field::common::I2T<comms::option::ScalingRatio<1, 10000> >;

    /// @brief Definition of "accGyroScale" field.
    using accGyroScale = field::common::I2T<comms::option::ScalingRatio<1, 10000> >;

    /// @brief Definition of "measUsed" field.
    struct measUsed : public field::common::X1
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(pulse, direction, gyro, temp, pos, vel, errGyro, errPulse);
    };

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res1;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        pulses,
        period,
        gyroMean,
        temperature,
        direction,
        calibStatus,
        pulseScale,
        gyroBias,
        gyroScale,
        accPulseScale,
        accGyroBias,
        accGyroScale,
        measUsed,
        reserved2
    >;
};

/// @brief Definition of NAV-EKFSTATUS message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavEkfstatusFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavEkfstatus : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_EKFSTATUS>,
        comms::option::FieldsImpl<NavEkfstatusFields::All>,
        comms::option::MsgType<NavEkfstatus<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b pulses for @ref NavEkfstatusFields::pulses field
    ///     @li @b period for @ref NavEkfstatusFields::period field
    ///     @li @b gyroMean for @ref NavEkfstatusFields::gyroMean field
    ///     @li @b temperature for @ref NavEkfstatusFields::temperature field
    ///     @li @b direction for @ref NavEkfstatusFields::direction field
    ///     @li @b calibStatus for @ref NavEkfstatusFields::calibStatus field
    ///     @li @b pulseScale for @ref NavEkfstatusFields::pulseScale field
    ///     @li @b gyroBias for @ref NavEkfstatusFields::gyroBias field
    ///     @li @b gyroScale for @ref NavEkfstatusFields::gyroScale field
    ///     @li @b accPulseScale for @ref NavEkfstatusFields::accPulseScale field
    ///     @li @b accGyroBias for @ref NavEkfstatusFields::accGyroBias field
    ///     @li @b accGyroScale for @ref NavEkfstatusFields::accGyroScale field
    ///     @li @b measUsed for @ref NavEkfstatusFields::measUsed field
    ///     @li @b reserved2 for @ref NavEkfstatusFields::reserved2 field
    COMMS_MSG_FIELDS_ACCESS(
        pulses,
        period,
        gyroMean,
        temperature,
        direction,
        calibStatus,
        pulseScale,
        gyroBias,
        gyroScale,
        accPulseScale,
        accGyroBias,
        accGyroScale,
        measUsed,
        reserved2
    );

    /// @brief Default constructor
    NavEkfstatus() = default;

    /// @brief Copy constructor
    NavEkfstatus(const NavEkfstatus&) = default;

    /// @brief Move constructor
    NavEkfstatus(NavEkfstatus&& other) = default;

    /// @brief Destructor
    ~NavEkfstatus() = default;

    /// @brief Copy assignment
    NavEkfstatus& operator=(const NavEkfstatus&) = default;

    /// @brief Move assignment
    NavEkfstatus& operator=(NavEkfstatus&&) = default;
};


}  // namespace message

}  // namespace ublox





