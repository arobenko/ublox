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

    /// @brief Definition of "filter" field.
    struct filter : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xc0, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(posFilt, mskPosFilt, timeFilt, dateFilt, gpsOnlyFilter, trackFilt);
    };

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
    struct flags : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xfc, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(compat, consider);
    };

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        filter,
        nmeaVersion,
        numSV,
        flags
    >;
};

/// @brief Definition of CFG-NMEA message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgNmeaFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgNmea : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NMEA>,
        comms::option::FieldsImpl<CfgNmeaFields::All>,
        comms::option::MsgType<CfgNmea<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NMEA>,
        comms::option::FieldsImpl<CfgNmeaFields::All>,
        comms::option::MsgType<CfgNmea<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b filter for @ref CfgNmeaFields::filter field
    ///     @li @b nmeaVersion for @ref CfgNmeaFields::nmeaVersion field
    ///     @li @b numSV for @ref CfgNmeaFields::numSV field
    ///     @li @b flags for @ref CfgNmeaFields::flags field
    COMMS_MSG_FIELDS_ACCESS(Base, filter, nmeaVersion, numSV, flags);

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

