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
/// @brief Contains definition of CFG-NMEA message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-NMEA message fields.
/// @see CfgNmea
struct CfgNmeaFields
{
    /// @brief Bits access enumeration for @ref filter bitmask field.
    enum
    {
        filter_posFilt, ///< @b posFilt bit index
        filter_mskPosFilt, ///< @b mskPosFilt bit index
        filter_timeFilt, ///< @b timeFilt bit index
        filter_dateFilt, ///< @b dateFilt bit index
        filter_gpsOnlyFilter, ///< @b gpsOnlyFilter bit index
        filter_trackFilt, ///< @b trackFilt bit index
        filter_numOfValues ///< number of available bits
    };

    /// @brief Value enumeration for @ref nmeaVersion field.
    enum class NmeaVersion : std::uint8_t
    {
        v21 = 0x21, ///< NMEA version 2.1
        v23 = 0x23 ///< NMEA version 2.3
    };

    /// @brief Custom validator class for @ref nmeaVersion field
    struct NmeaVersionValidator
    {
        template <typename TField>
        bool operator()(const TField& field) const
        {
            auto value = field.value();
            return ((value == NmeaVersion::v21) ||
                    (value == NmeaVersion::v23));
        }
    };

    /// @brief Bits access enumeration for @ref flags bitmask field.
    enum
    {
        flags_compat, ///< @b compat bit index
        flags_consider, ///< @b consider bit index
        flags_numOfValues ///< number of available bits
    };

    /// @brief Definition of "filter" field.
    using filter =
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xc0, 0>
        >;

    /// @brief Definition of "nmeaVersion" field.
    using nmeaVersion =
        field::common::EnumT<
            NmeaVersion,
            comms::option::ContentsValidator<NmeaVersionValidator>,
            comms::option::DefaultNumValue<(int)NmeaVersion::v23>
        >;

    /// @brief Definition of "numSV" field.
    using numSV = field::common::U1;

    /// @brief Definition of "flags" field.
    using flags =
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xfc, 0>
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        filter,
        nmeaVersion,
        numSV,
        flags
    >;
};

/// @brief Definition of CFG-NMEA message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref CfgNmeaFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgNmea : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NMEA>,
        comms::option::FieldsImpl<CfgNmeaFields::All>,
        comms::option::DispatchImpl<CfgNmea<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NMEA>,
        comms::option::FieldsImpl<CfgNmeaFields::All>,
        comms::option::DispatchImpl<CfgNmea<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_filter, ///< @b filter field, see @ref CfgNmeaFields::filter
        FieldIdx_nmeaVersion, ///< @b nmeaVersion field, see @ref CfgNmeaFields::nmeaVersion
        FieldIdx_numSV, ///< @b numSV field, see @ref CfgNmeaFields::numSV
        FieldIdx_flags, ///< @b flags field, see @ref CfgNmeaFields::flags
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

