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

namespace ublox
{

namespace message
{

enum
{
    CfgNmeaField_filter_posFilt,
    CfgNmeaField_filter_mskPosFilt,
    CfgNmeaField_filter_timeFilt,
    CfgNmeaField_filter_dateFilt,
    CfgNmeaField_filter_gpsOnlyFilter,
    CfgNmeaField_filter_trackFilt,
    CfgNmeaField_filter_numOfValues
};

enum class CfgNmea_NmeaVersion : std::uint8_t
{
    v21 = 0x21,
    v23 = 0x23
};

struct CfgNmea_NmeaVersionValidator
{
    template <typename TField>
    bool operator()(const TField& field) const
    {
        auto value = field.value();
        return ((value == CfgNmea_NmeaVersion::v21) ||
                (value == CfgNmea_NmeaVersion::v23));
    }
};

enum
{
    CfgNmeaField_flags_compat,
    CfgNmeaField_flags_consider,
    CfgNmeaField_flags_numOfValues
};

using CfgNmeaField_filter =
    field::common::X1T<
        comms::option::BitmaskReservedBits<0xc0, 0>
    >;
using CfgNmeaField_nmeaVersion =
    field::common::EnumT<
        CfgNmea_NmeaVersion,
        comms::option::ContentsValidator<CfgNmea_NmeaVersionValidator>,
        comms::option::DefaultNumValue<(int)CfgNmea_NmeaVersion::v23>
    >;
using CfgNmeaField_numSV = field::common::U1;
using CfgNmeaField_flags =
    field::common::X1T<
        comms::option::BitmaskReservedBits<0xfc, 0>
    >;

using CfgNmeaFields = std::tuple<
    CfgNmeaField_filter,
    CfgNmeaField_nmeaVersion,
    CfgNmeaField_numSV,
    CfgNmeaField_flags
>;

template <typename TMsgBase = Message>
class CfgNmea : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NMEA>,
        comms::option::FieldsImpl<CfgNmeaFields>,
        comms::option::DispatchImpl<CfgNmea<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NMEA>,
        comms::option::FieldsImpl<CfgNmeaFields>,
        comms::option::DispatchImpl<CfgNmea<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_filter,
        FieldIdx_nmeaVersion,
        FieldIdx_numSV,
        FieldIdx_flags,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgNmea() = default;

    /// @brief Copy constructor
    CfgNmea(const CfgNmea&) = default;

    /// @brief Move constructor
    CfgNmea(CfgNmea&& other) = default;

    /// @brief Destructor
    virtual ~CfgNmea() = default;

    /// @brief Copy assignment
    CfgNmea& operator=(const CfgNmea&) = default;

    /// @brief Move assignment
    CfgNmea& operator=(CfgNmea&&) = default;
};


}  // namespace message

}  // namespace ublox

