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

#include <algorithm>

#include "comms/Message.h"
#include "ublox/Message.h"
#include "ublox/field/MsgId.h"
#include "ublox/field/common.h"
#include "CfgNmea.h"

namespace ublox
{

namespace message
{

enum
{
    CfgNmeaField_gnssToFilter_gps,
    CfgNmeaField_gnssToFilter_sbas,
    CfgNmeaField_gnssToFilter_reserved0,
    CfgNmeaField_gnssToFilter_reserved1,
    CfgNmeaField_gnssToFilter_qzss,
    CfgNmeaField_gnssToFilter_glonass,
    CfgNmeaField_gnssToFilter_numOfValues
};

enum class CfgNmea_SvNumbering : std::uint8_t
{
    String,
    Extended,
    NumOfValues
};

enum class CfgNmea_MainTalkerId : std::uint8_t
{
    NotOverriden,
    GP,
    GL,
    GN,
    NumOfValues
};

enum class CfgNmea_GsvTalkerId : std::uint8_t
{
    GnssSpecific,
    Main,
    NumOfValues
};

using CfgNmeaExtField_filter = CfgNmeaField_filter;
using CfgNmeaExtField_nmeaVersion = CfgNmeaField_nmeaVersion;
using CfgNmeaExtField_numSV = CfgNmeaField_numSV;
using CfgNmeaExtField_flags = CfgNmeaField_flags;
using CfgNmeaExtField_gnssToFilter =
    field::common::X4T<
        comms::option::BitmaskReservedBits<0xffffffcc, 0>
    >;
using CfgNmeaExtField_svNumbering =
    comms::field::EnumValue<
        field::common::FieldBase,
        CfgNmea_SvNumbering,
        comms::option::ValidNumValueRange<0, (int)CfgNmea_SvNumbering::NumOfValues - 1>
    >;
using CfgNmeaExtField_mainTalkerId =
    comms::field::EnumValue<
        field::common::FieldBase,
        CfgNmea_MainTalkerId,
        comms::option::ValidNumValueRange<0, (int)CfgNmea_MainTalkerId::NumOfValues - 1>
    >;
using CfgNmeaExtField_gsvTalkerId =
    comms::field::EnumValue<
        field::common::FieldBase,
        CfgNmea_GsvTalkerId,
        comms::option::ValidNumValueRange<0, (int)CfgNmea_GsvTalkerId::NumOfValues - 1>
    >;
using CfgNmeaExtField_reserved = field::common::res1;

using CfgNmeaExtFields = std::tuple<
    CfgNmeaExtField_filter,
    CfgNmeaExtField_nmeaVersion,
    CfgNmeaExtField_numSV,
    CfgNmeaExtField_flags,
    CfgNmeaExtField_gnssToFilter,
    CfgNmeaExtField_svNumbering,
    CfgNmeaExtField_mainTalkerId,
    CfgNmeaExtField_gsvTalkerId,
    CfgNmeaExtField_reserved
>;

template <typename TMsgBase = Message>
class CfgNmeaExt : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NMEA>,
        comms::option::FieldsImpl<CfgNmeaExtFields>,
        comms::option::DispatchImpl<CfgNmeaExt<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NMEA>,
        comms::option::FieldsImpl<CfgNmeaExtFields>,
        comms::option::DispatchImpl<CfgNmeaExt<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_filter,
        FieldIdx_nmeaVersion,
        FieldIdx_numSV,
        FieldIdx_flags,
        FieldIdx_gnssToFilter,
        FieldIdx_svNumbering,
        FieldIdx_mainTalkerId,
        FieldIdx_gsvTalkerId,
        FieldIdx_reserved,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    CfgNmeaExt() = default;
    CfgNmeaExt(const CfgNmeaExt&) = default;
    CfgNmeaExt(CfgNmeaExt&& other) = default;
    virtual ~CfgNmeaExt() = default;

    CfgNmeaExt& operator=(const CfgNmeaExt&) = default;
    CfgNmeaExt& operator=(CfgNmeaExt&&) = default;
};


}  // namespace message

}  // namespace ublox

