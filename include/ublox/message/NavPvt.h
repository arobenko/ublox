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

enum
{
    NavPvtField_valid_validDate,
    NavPvtField_valid_validTime,
    NavPvtField_valid_fullyResolved,
    NavPvtField_valid_numOfValues
};

enum
{
    NavPvtField_flags_flags,
    NavPvtField_flags_psmState,
    NavPvtField_flags_numOfValues
};

enum
{
    NavPvtField_flags_flags_gnssFixOK,
    NavPvtField_flags_flags_diffSoln,
    NavPvtField_flags_flags_numOfValues
};

using NavPvt_FixType = field::nav::GpsFix;

enum class NavPvt_PsmState : std::uint8_t
{
    Invalid,
    Enabled,
    Acquisition,
    Tracking,
    PowerOptimisedTracking,
    Inactive,
    NumOfValues
};

using NavPvtField_iTOW = field::nav::iTOW;
using NavPvtField_year = field::nav::year;
using NavPvtField_month = field::nav::month;
using NavPvtField_day = field::nav::day;
using NavPvtField_hour = field::nav::hour;
using NavPvtField_min = field::nav::min;
using NavPvtField_sec = field::nav::sec;
using NavPvtField_valid =
    field::common::X1T<
        comms::option::BitmaskReservedBits<0xf8, 0> >;
using NavPvtField_tAcc = field::nav::tAcc;
using NavPvtField_nano = field::nav::nano;
using NavPvtField_fixType = field::nav::gpsFix;
using NavPvtField_flags =
    comms::field::Bitfield<
        field::common::FieldBase,
        std::tuple<
            field::common::X1T<comms::option::FixedBitLength<2> >,
            comms::field::EnumValue<
                field::common::FieldBase,
                NavPvt_PsmState,
                comms::option::FixedBitLength<6>
            >
        >
    >;

using NavPvtField_reserved1 = field::common::res1;
using NavPvtField_numSV = field::nav::numSV;
using NavPvtField_lon = field::nav::lon;
using NavPvtField_lat = field::nav::lat;
using NavPvtField_height = field::nav::height;
using NavPvtField_hMSL = field::nav::hMSL;
using NavPvtField_hAcc = field::nav::hAcc;
using NavPvtField_vAcc = field::nav::vAcc;
using NavPvtField_velN = field::common::I4T<field::common::Scaling_mm2m>;
using NavPvtField_velE = NavPvtField_velN;
using NavPvtField_velD = NavPvtField_velN;
using NavPvtField_gSpeed = field::common::I4T<field::common::Scaling_mm2m>;
using NavPvtField_heading = field::nav::heading;
using NavPvtField_sAcc = field::common::U4T<field::common::Scaling_mm2m>;
using NavPvtField_headingAcc = field::common::U4T<comms::option::ScalingRatio<1, 100000> >;
using NavPvtField_pDOP = field::nav::pDOP;
using NavPvtField_reserved2 = field::common::res2;
using NavPvtField_reserved3 = field::common::res4;

using NavPvtFields = std::tuple<
    NavPvtField_iTOW,
    NavPvtField_year,
    NavPvtField_month,
    NavPvtField_day,
    NavPvtField_hour,
    NavPvtField_min,
    NavPvtField_sec,
    NavPvtField_valid,
    NavPvtField_tAcc,
    NavPvtField_nano,
    NavPvtField_fixType,
    NavPvtField_flags,
    NavPvtField_reserved1,
    NavPvtField_numSV,
    NavPvtField_lon,
    NavPvtField_lat,
    NavPvtField_height,
    NavPvtField_hMSL,
    NavPvtField_hAcc,
    NavPvtField_vAcc,
    NavPvtField_velN,
    NavPvtField_velE,
    NavPvtField_velD,
    NavPvtField_gSpeed,
    NavPvtField_heading,
    NavPvtField_sAcc,
    NavPvtField_headingAcc,
    NavPvtField_pDOP,
    NavPvtField_reserved2,
    NavPvtField_reserved3
>;

template <typename TMsgBase = Message>
class NavPvt : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_PVT>,
        comms::option::FieldsImpl<NavPvtFields>,
        comms::option::DispatchImpl<NavPvt<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_PVT>,
        comms::option::FieldsImpl<NavPvtFields>,
        comms::option::DispatchImpl<NavPvt<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_iTOW,
        FieldIdx_year,
        FieldIdx_month,
        FieldIdx_day,
        FieldIdx_hour,
        FieldIdx_min,
        FieldIdx_sec,
        FieldIdx_valid,
        FieldIdx_tAcc,
        FieldIdx_nano,
        FieldIdx_fixType,
        FieldIdx_flags,
        FieldIdx_reserved1,
        FieldIdx_numSV,
        FieldIdx_lon,
        FieldIdx_lat,
        FieldIdx_height,
        FieldIdx_hMSL,
        FieldIdx_hAcc,
        FieldIdx_vAcc,
        FieldIdx_velN,
        FieldIdx_velE,
        FieldIdx_velD,
        FieldIdx_gSpeed,
        FieldIdx_heading,
        FieldIdx_sAcc,
        FieldIdx_headingAcc,
        FieldIdx_pDOP,
        FieldIdx_reserved2,
        FieldIdx_reserved3,
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





