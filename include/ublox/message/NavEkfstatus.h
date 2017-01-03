//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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

    /// @brief Use this enumeration to access member fields of @ref calibStatus bitfield.
    enum
    {
        calibStatus_calibTacho, ///< index of @ref calibTacho member field
        calibStatus_calibGyro, ///< index of @ref calibGyro member field
        calibStatus_calibGyroB, ///< index of @ref calibGyroB member field
        calibStatus_numOfValues = calibStatus_calibGyroB + 2 ///< number of available member fields
    };

    /// @brief Bits access enumeration for bits in @b measUsed bitmask field.
    enum
    {
        measUsed_pulse, ///< @b pulse bit index
        measUsed_direction, ///< @b directin bit index
        measUsed_gyro, ///< @b gyro bit index
        measUsed_temp, ///< @b temp bit index
        measUsed_pos, ///< @b pos bit index
        measUsed_vel, ///< @b vel bit index
        measUsed_errGyro, ///< @b errGyro bit index
        measUsed_errPulse, ///< @b errPulse bit index
        measUsed_numOfValues ///< number of available bits
    };

    /// @brief Definition of "pulses" field.
    using pulses = field::common::I4;

    /// @brief Definition of "period" field.
    using period = field::common::I4T<field::common::Scaling_ms2s>;

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
    using calibStatus =
        field::common::BitfieldT<
            std::tuple<
                calibTacho,
                calibGyro,
                calibGyroB,
                field::common::res1T<comms::option::FixedBitLength<2> >
            >
        >;

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
    using measUsed = field::common::X1;

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
///     See @ref NavEkfstatusFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavEkfstatus : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_EKFSTATUS>,
        comms::option::FieldsImpl<NavEkfstatusFields::All>,
        comms::option::MsgType<NavEkfstatus<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_EKFSTATUS>,
        comms::option::FieldsImpl<NavEkfstatusFields::All>,
        comms::option::MsgType<NavEkfstatus<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_pulses, ///< @b pulses field, see @ref NavEkfstatusFields::pulses
        FieldIdx_period, ///< @b period field, see @ref NavEkfstatusFields::period
        FieldIdx_gyroMean, ///< @b gyroMean field, see @ref NavEkfstatusFields::gyroMean
        FieldIdx_temperature, ///< @b temperature field, see @ref NavEkfstatusFields::temperature
        FieldIdx_direction, ///< @b direction field, see @ref NavEkfstatusFields::direction
        FieldIdx_calibStatus, ///< @b calibStatus field, see @ref NavEkfstatusFields::calibStatus
        FieldIdx_pulseScale, ///< @b pulseScale field, see @ref NavEkfstatusFields::pulseScale
        FieldIdx_gyroBias, ///< @b gyroBias field, see @ref NavEkfstatusFields::gyroBias
        FieldIdx_gyroScale, ///< @b gyroScale field, see @ref NavEkfstatusFields::gyroScale
        FieldIdx_accPulseScale, ///< @b accPulseScale field, see @ref NavEkfstatusFields::accPulseScale
        FieldIdx_accGyroBias, ///< @b accGyroBias field, see @ref NavEkfstatusFields::accGyroBias
        FieldIdx_accGyroScale, ///< @b accGyroScale field, see @ref NavEkfstatusFields::accGyroScale
        FieldIdx_measUsed, ///< @b measUsed field, see @ref NavEkfstatusFields::measUsed
        FieldIdx_reserved2, ///< @b reserved2 field, see @ref NavEkfstatusFields::reserved2
        FieldIdx_numOfValues ///< number of available fields
    };


    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        NavEkfstatusFields::pulses& pulses; ///< @b pulses field, see @ref NavEkfstatusFields::pulses
        NavEkfstatusFields::period& period; ///< @b period field, see @ref NavEkfstatusFields::period
        NavEkfstatusFields::gyroMean& gyroMean; ///< @b gyroMean field, see @ref NavEkfstatusFields::gyroMean
        NavEkfstatusFields::temperature& temperature; ///< @b temperature field, see @ref NavEkfstatusFields::temperature
        NavEkfstatusFields::direction& direction; ///< @b direction field, see @ref NavEkfstatusFields::direction
        NavEkfstatusFields::calibStatus& calibStatus; ///< @b calibStatus field, see @ref NavEkfstatusFields::calibStatus
        NavEkfstatusFields::pulseScale& pulseScale; ///< @b pulseScale field, see @ref NavEkfstatusFields::pulseScale
        NavEkfstatusFields::gyroBias& gyroBias; ///< @b gyroBias field, see @ref NavEkfstatusFields::gyroBias
        NavEkfstatusFields::gyroScale& gyroScale; ///< @b gyroScale field, see @ref NavEkfstatusFields::gyroScale
        NavEkfstatusFields::accPulseScale& accPulseScale; ///< @b accPulseScale field, see @ref NavEkfstatusFields::accPulseScale
        NavEkfstatusFields::accGyroBias& accGyroBias; ///< @b accGyroBias field, see @ref NavEkfstatusFields::accGyroBias
        NavEkfstatusFields::accGyroScale& accGyroScale; ///< @b accGyroScale field, see @ref NavEkfstatusFields::accGyroScale
        NavEkfstatusFields::measUsed& measUsed; ///< @b measUsed field, see @ref NavEkfstatusFields::measUsed
        NavEkfstatusFields::reserved2& reserved2; ///< @b reserved2 field, see @ref NavEkfstatusFields::reserved2
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const NavEkfstatusFields::pulses& pulses; ///< @b pulses field, see @ref NavEkfstatusFields::pulses
        const NavEkfstatusFields::period& period; ///< @b period field, see @ref NavEkfstatusFields::period
        const NavEkfstatusFields::gyroMean& gyroMean; ///< @b gyroMean field, see @ref NavEkfstatusFields::gyroMean
        const NavEkfstatusFields::temperature& temperature; ///< @b temperature field, see @ref NavEkfstatusFields::temperature
        const NavEkfstatusFields::direction& direction; ///< @b direction field, see @ref NavEkfstatusFields::direction
        const NavEkfstatusFields::calibStatus& calibStatus; ///< @b calibStatus field, see @ref NavEkfstatusFields::calibStatus
        const NavEkfstatusFields::pulseScale& pulseScale; ///< @b pulseScale field, see @ref NavEkfstatusFields::pulseScale
        const NavEkfstatusFields::gyroBias& gyroBias; ///< @b gyroBias field, see @ref NavEkfstatusFields::gyroBias
        const NavEkfstatusFields::gyroScale& gyroScale; ///< @b gyroScale field, see @ref NavEkfstatusFields::gyroScale
        const NavEkfstatusFields::accPulseScale& accPulseScale; ///< @b accPulseScale field, see @ref NavEkfstatusFields::accPulseScale
        const NavEkfstatusFields::accGyroBias& accGyroBias; ///< @b accGyroBias field, see @ref NavEkfstatusFields::accGyroBias
        const NavEkfstatusFields::accGyroScale& accGyroScale; ///< @b accGyroScale field, see @ref NavEkfstatusFields::accGyroScale
        const NavEkfstatusFields::measUsed& measUsed; ///< @b measUsed field, see @ref NavEkfstatusFields::measUsed
        const NavEkfstatusFields::reserved2& reserved2; ///< @b reserved2 field, see @ref NavEkfstatusFields::reserved2
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base,
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
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

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





