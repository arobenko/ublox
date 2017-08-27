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
/// @brief Contains definition of HNR-PVT message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the HNR-PVT message fields.
/// @see HnrPvt
struct HnrPvtFields
{
    /// @brief Definition of "iTOW" field.
    using iTOW = field::common::iTOW;

    /// @brief Definition of "year" field.
    using year = field::nav::year;

    /// @brief Definition of "month" field.
    using month = field::nav::month;

    /// @brief Definition of "day" field.
    using day = field::nav::day;

    /// @brief Definition of "hour" field.
    using hour = field::nav::hour;

    /// @brief Definition of "min" field.
    using min = field::nav::min;

    /// @brief Definition of "sec" field.
    using sec = field::nav::sec;

    /// @brief Definition of "valid" field.
    struct validBits : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xf8, 0> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(validDate, validTime, fullyResolved);
    };

    /// @brief Definition of "nano" field.
    using nano = field::nav::nano;

    /// @brief Value enumeration for @ref gpsFix field.
    using GpsFix = field::nav::GpsFix;

    /// @brief Definition of "gpsFix" field.
    using gpsFix = field::nav::gpsFix;

    /// @brief Definition of two first bits (@b gnssFixOn and @b diffSoln) in
    ///     @ref flags bitfield as separate bitmask member field.
    struct flags : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xe0, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS_SEQ macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS_SEQ(gnssFixOK, diffSoln, WKNSET, TOWSET, headVehValid);
    };

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "lon" field.
    using lon = field::nav::lon;

    /// @brief Definition of "lat" field.
    using lat = field::nav::lat;

    /// @brief Definition of "height" field.
    using height = field::nav::height;

    /// @brief Definition of "hMSL" field.
    using hMSL = field::nav::hMSL;

    /// @brief Definition of "gSpeed" field.
    using gSpeed = field::common::I4T<comms::option::UnitsMillimetersPerSecond>;

    /// @brief Definition of "gSpeed" field.
    using speed = gSpeed;

    /// @brief Definition of "headMot" field.
    using headMot = field::nav::heading;

    /// @brief Definition of "headVeh" field.
    using headVeh = field::nav::heading;

    /// @brief Definition of "hAcc" field.
    using hAcc = field::nav::hAcc;

    /// @brief Definition of "vAcc" field.
    using vAcc = field::nav::vAcc;

    /// @brief Definition of "sAcc" field.
    using sAcc = field::common::U4T<comms::option::UnitsMillimetersPerSecond>;

    /// @brief Definition of "headAcc" field.
    using headAcc =
        field::common::U4T<
            comms::option::ScalingRatio<1, 100000>,
            comms::option::UnitsDegrees
        >;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        iTOW,
        year,
        month,
        day,
        hour,
        min,
        sec,
        validBits,
        nano,
        gpsFix,
        flags,
        reserved1,
        lon,
        lat,
        height,
        hMSL,
        gSpeed,
        speed,
        headMot,
        headVeh,
        hAcc,
        vAcc,
        sAcc,
        headAcc,
        reserved2
    >;
};

/// @brief Definition of HNR-PVT message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref HnrPvtFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class HnrPvt : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_HNR_PVT>,
        comms::option::FieldsImpl<HnrPvtFields::All>,
        comms::option::MsgType<HnrPvt<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref HnrPvtFields::iTOW field
    ///     @li @b year for @ref HnrPvtFields::year field
    ///     @li @b month for @ref HnrPvtFields::month field
    ///     @li @b day for @ref HnrPvtFields::day field
    ///     @li @b hour for @ref HnrPvtFields::hour field
    ///     @li @b min for @ref HnrPvtFields::min field
    ///     @li @b sec for @ref HnrPvtFields::sec field
    ///     @li @b valid for @ref HnrPvtFields::validBits field
    ///     @li @b nano for @ref HnrPvtFields::nano field
    ///     @li @b gpsFix for @ref HnrPvtFields::gpsFix field
    ///     @li @b flags for @ref HnrPvtFields::flags field
    ///     @li @b reserved1 for @ref HnrPvtFields::reserved1 field
    ///     @li @b lon for @ref HnrPvtFields::lon field
    ///     @li @b lat for @ref HnrPvtFields::lat field
    ///     @li @b height for @ref HnrPvtFields::height field
    ///     @li @b hMSL for @ref HnrPvtFields::hMSL field
    ///     @li @b gSpeed for @ref HnrPvtFields::gSpeed field
    ///     @li @b speed for @ref HnrPvtFields::speed field
    ///     @li @b headMot for @ref HnrPvtFields::headMot field
    ///     @li @b headVeh for @ref HnrPvtFields::headVeh field
    ///     @li @b hAcc for @ref HnrPvtFields::hAcc field
    ///     @li @b vAcc for @ref HnrPvtFields::vAcc field
    ///     @li @b sAcc for @ref HnrPvtFields::sAcc field
    ///     @li @b headAcc for @ref HnrPvtFields::headAcc field
    ///     @li @b reserved2 for @ref HnrPvtFields::reserved2 field
    COMMS_MSG_FIELDS_ACCESS(
        iTOW,
        year,
        month,
        day,
        hour,
        min,
        sec,
        validBits,
        nano,
        gpsFix,
        flags,
        reserved1,
        lon,
        lat,
        height,
        hMSL,
        gSpeed,
        speed,
        headMot,
        headVeh,
        hAcc,
        vAcc,
        sAcc,
        headAcc,
        reserved2);

    /// @brief Default constructor
    HnrPvt() = default;

    /// @brief Copy constructor
    HnrPvt(const HnrPvt&) = default;

    /// @brief Move constructor
    HnrPvt(HnrPvt&& other) = default;

    /// @brief Destructor
    ~HnrPvt() = default;

    /// @brief Copy assignment
    HnrPvt& operator=(const HnrPvt&) = default;

    /// @brief Move assignment
    HnrPvt& operator=(HnrPvt&&) = default;
};


}  // namespace message

}  // namespace ublox





