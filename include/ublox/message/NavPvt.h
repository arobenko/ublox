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
    /// @brief Bits access enumeration for bits in @b valid bitmask field
    enum
    {
        valid_validDate, ///< @b validDate bit index
        valid_validTime, ///< @b validTime bit index
        valid_fullyResolved, ///< @b fullyResolved bit index
        valid_numOfValues ///< number of available bits
    };

    /// @brief Use this enumeration to access member fields of @ref flags bitfield.
    enum
    {
        flags_bits, ///< index of @ref flagsBits member field
        flags_psmState, ///< index of @ref  psmState member field
        flags_numOfValues ///< number of available fields
    };

    /// @brief Bits access enumeration for bits in @b flagsBits member of
    ///     @ref flags bitfield field.
    enum
    {
        flagsBits_gnssFixOK, ///< @b gnssFixOK bit index
        flagsBits_diffSoln, ///< @b diffSoln bit index
        flagsBits_numOfValues ///< number of available bits
    };

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
    using valid =
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xf8, 0> >;

    /// @brief Definition of "tAcc" field.
    using tAcc = field::nav::tAcc;

    /// @brief Definition of "nano" field.
    using nano = field::nav::nano;

    /// @brief Definition of "fixType" field.
    using fixType = field::nav::gpsFix;

    /// @brief Definition of two first bits (@b gnssFixOn and @b diffSoln) in
    ///     @ref flags bitfield as separate bitmask member field.
    using flagsBits =
        field::common::X1T<comms::option::FixedBitLength<2> >;

    /// @brief Definition of "psmState" member field in @ref flags bitmask field.
    using psmState =
        field::common::EnumT<
            PsmState,
            comms::option::FixedBitLength<6>,
            comms::option::ValidNumValueRange<0, (int)PsmState::NumOfValues - 1>
        >;

    /// @brief Definition of "flags" field.
    using flags =
        field::common::BitfieldT<
            std::tuple<
                flagsBits,
                psmState
            >
        >;

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
    >;
};

/// @brief Definition of NAV-PVT message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref NavPvtFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavPvt : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_PVT>,
        comms::option::FieldsImpl<NavPvtFields::All>,
        comms::option::DispatchImpl<NavPvt<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_PVT>,
        comms::option::FieldsImpl<NavPvtFields::All>,
        comms::option::DispatchImpl<NavPvt<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_iTOW, ///< @b iTOW field, see @ref NavPvtFields::iTOW
        FieldIdx_year, ///< @b year field, see @ref NavPvtFields::year
        FieldIdx_month, ///< @b month field, see @ref NavPvtFields::month
        FieldIdx_day, ///< @b day field, see @ref NavPvtFields::day
        FieldIdx_hour, ///< @b hour field, see @ref NavPvtFields::hour
        FieldIdx_min, ///< @b min field, see @ref NavPvtFields::min
        FieldIdx_sec, ///< @b sec field, see @ref NavPvtFields::sec
        FieldIdx_valid, ///< @b valid field, see @ref NavPvtFields::valid
        FieldIdx_tAcc, ///< @b tAcc field, see @ref NavPvtFields::tAcc
        FieldIdx_nano, ///< @b nano field, see @ref NavPvtFields::nano
        FieldIdx_fixType, ///< @b fixType field, see @ref NavPvtFields::fixType
        FieldIdx_flags, ///< @b flags field, see @ref NavPvtFields::flags
        FieldIdx_reserved1, ///< @b reserved1 field, see @ref NavPvtFields::reserved1
        FieldIdx_numSV, ///< @b numSV field, see @ref NavPvtFields::numSV
        FieldIdx_lon, ///< @b lon field, see @ref NavPvtFields::lon
        FieldIdx_lat, ///< @b lat field, see @ref NavPvtFields::lat
        FieldIdx_height, ///< @b height field, see @ref NavPvtFields::height
        FieldIdx_hMSL, ///< @b hMSL field, see @ref NavPvtFields::hMSL
        FieldIdx_hAcc, ///< @b hAcc field, see @ref NavPvtFields::hAcc
        FieldIdx_vAcc, ///< @b vAcc field, see @ref NavPvtFields::vAcc
        FieldIdx_velN, ///< @b velN field, see @ref NavPvtFields::velN
        FieldIdx_velE, ///< @b velE field, see @ref NavPvtFields::velE
        FieldIdx_velD, ///< @b velD field, see @ref NavPvtFields::velD
        FieldIdx_gSpeed, ///< @b gSpeed field, see @ref NavPvtFields::gSpeed
        FieldIdx_heading, ///< @b heading field, see @ref NavPvtFields::heading
        FieldIdx_sAcc, ///< @b sAcc field, see @ref NavPvtFields::sAcc
        FieldIdx_headingAcc, ///< @b headingAcc field, see @ref NavPvtFields::headingAcc
        FieldIdx_pDOP, ///< @b pDOP field, see @ref NavPvtFields::pDOP
        FieldIdx_reserved2, ///< @b reserved2 field, see @ref NavPvtFields::reserved2
        FieldIdx_reserved3, ///< @b reserved3 field, see @ref NavPvtFields::reserved3
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

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





