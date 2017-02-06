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
/// @brief Contains definition of NAV-PVT message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-PVT message fields.
/// @see NavPvt
struct NavPvtFields
{
    /// @brief Value enumeration for @ref psmState field.
    enum class PsmState : std::uint8_t
    {
        Invalid, ///< invalid
        Enabled, ///< enabled
        Acquisition, ///< acquisition
        Tracking, ///< tracking
        PowerOptimisedTracking, ///< power optimised tracking
        Inactive, ///< inactive
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "iTOW" field.
    using iTOW = field::nav::iTOW;

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
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(validDate, validTime, fullyResolved);
    };

    /// @brief Definition of "tAcc" field.
    using tAcc = field::nav::tAcc;

    /// @brief Definition of "nano" field.
    using nano = field::nav::nano;

    /// @brief Definition of "fixType" field.
    using fixType = field::nav::gpsFix;

    /// @brief Definition of two first bits (@b gnssFixOn and @b diffSoln) in
    ///     @ref flags bitfield as separate bitmask member field.
    struct flagsBits : public
        field::common::X1T<comms::option::FixedBitLength<2> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(gnssFixOK, diffSoln);
    };

    /// @brief Definition of "psmState" member field in @ref flags bitmask field.
    using psmState =
        field::common::EnumT<
            PsmState,
            comms::option::FixedBitLength<6>,
            comms::option::ValidNumValueRange<0, (int)PsmState::NumOfValues - 1>
        >;

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::BitfieldT<
            std::tuple<
                flagsBits,
                psmState
            >
        >
    {
        /// @brief Allow access to internal fields.
        /// @details See definition of @b COMMS_FIELD_MEMBERS_ACCESS macro
        ///     related to @b comms::field::Bitfield class from COMMS library
        ///     for details.
        COMMS_FIELD_MEMBERS_ACCESS(flagsBits, psmState);
    };

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "numSV" field.
    using numSV = field::nav::numSV;

    /// @brief Definition of "lon" field.
    using lon = field::nav::lon;

    /// @brief Definition of "lat" field.
    using lat = field::nav::lat;

    /// @brief Definition of "height" field.
    using height = field::nav::height;

    /// @brief Definition of "hMSL" field.
    using hMSL = field::nav::hMSL;

    /// @brief Definition of "hAcc" field.
    using hAcc = field::nav::hAcc;

    /// @brief Definition of "vAcc" field.
    using vAcc = field::nav::vAcc;

    /// @brief Definition of "velN" field.
    using velN = field::common::I4T<field::common::Scaling_mm2m>;

    /// @brief Definition of "velE" field.
    using velE = velN;

    /// @brief Definition of "velD" field.
    using velD = velN;

    /// @brief Definition of "gSpeed" field.
    using gSpeed = field::common::I4T<field::common::Scaling_mm2m>;

    /// @brief Definition of "heading" field.
    using heading = field::nav::heading;

    /// @brief Definition of "sAcc" field.
    using sAcc = field::common::U4T<field::common::Scaling_mm2m>;

    /// @brief Definition of "headingAcc" field.
    using headingAcc = field::common::U4T<comms::option::ScalingRatio<1, 100000> >;

    /// @brief Definition of "pDOP" field.
    using pDOP = field::nav::pDOP;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res2;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res4;

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
        tAcc,
        nano,
        fixType,
        flags,
        reserved1,
        numSV,
        lon,
        lat,
        height,
        hMSL,
        hAcc,
        vAcc,
        velN,
        velE,
        velD,
        gSpeed,
        heading,
        sAcc,
        headingAcc,
        pDOP,
        reserved2,
        reserved3
    >;
};

/// @brief Definition of NAV-PVT message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavPvtFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavPvt : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_PVT>,
        comms::option::FieldsImpl<NavPvtFields::All>,
        comms::option::MsgType<NavPvt<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_PVT>,
        comms::option::FieldsImpl<NavPvtFields::All>,
        comms::option::MsgType<NavPvt<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b iTOW for @ref NavPvtFields::iTOW field
    ///     @li @b year for @ref NavPvtFields::year field
    ///     @li @b month for @ref NavPvtFields::month field
    ///     @li @b day for @ref NavPvtFields::day field
    ///     @li @b hour for @ref NavPvtFields::hour field
    ///     @li @b min for @ref NavPvtFields::min field
    ///     @li @b sec for @ref NavPvtFields::sec field
    ///     @li @b valid for @ref NavPvtFields::validBits field
    ///     @li @b tAcc for @ref NavPvtFields::tAcc field
    ///     @li @b nano for @ref NavPvtFields::nano field
    ///     @li @b fixType for @ref NavPvtFields::fixType field
    ///     @li @b flags for @ref NavPvtFields::flags field
    ///     @li @b reserved1 for @ref NavPvtFields::reserved1 field
    ///     @li @b numSV for @ref NavPvtFields::numSV field
    ///     @li @b lon for @ref NavPvtFields::lon field
    ///     @li @b lat for @ref NavPvtFields::lat field
    ///     @li @b height for @ref NavPvtFields::height field
    ///     @li @b hMSL for @ref NavPvtFields::hMSL field
    ///     @li @b hAcc for @ref NavPvtFields::hAcc field
    ///     @li @b vAcc for @ref NavPvtFields::vAcc field
    ///     @li @b velN for @ref NavPvtFields::velN field
    ///     @li @b velE for @ref NavPvtFields::velE field
    ///     @li @b velD for @ref NavPvtFields::velD field
    ///     @li @b gSpeed for @ref NavPvtFields::gSpeed field
    ///     @li @b heading for @ref NavPvtFields::heading field
    ///     @li @b headingAcc for @ref NavPvtFields::headingAcc field
    ///     @li @b pDOP for @ref NavPvtFields::pDOP field
    ///     @li @b reserved2 for @ref NavPvtFields::reserved2 field
    ///     @li @b reserved3 for @ref NavPvtFields::reserved3 field
    COMMS_MSG_FIELDS_ACCESS(
        iTOW,
        year,
        month,
        day,
        hour,
        min,
        sec,
        valid,
        tAcc,
        nano,
        fixType,
        flags,
        reserved1,
        numSV,
        lon,
        lat,
        height,
        hMSL,
        hAcc,
        vAcc,
        velN,
        velE,
        velD,
        gSpeed,
        heading,
        sAcc,
        headingAcc,
        pDOP,
        reserved2,
        reserved3
    );

    /// @brief Default constructor
    NavPvt() = default;

    /// @brief Copy constructor
    NavPvt(const NavPvt&) = default;

    /// @brief Move constructor
    NavPvt(NavPvt&& other) = default;

    /// @brief Destructor
    virtual ~NavPvt() = default;

    /// @brief Copy assignment
    NavPvt& operator=(const NavPvt&) = default;

    /// @brief Move assignment
    NavPvt& operator=(NavPvt&&) = default;
};


}  // namespace message

}  // namespace ublox





