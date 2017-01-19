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
/// @brief Contains definition of CFG-NMEA (@b extended) message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"
#include "CfgNmea.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-NMEA (@b extended) message fields.
/// @see CfgNmeaExt
struct CfgNmeaExtFields : public CfgNmeaFields
{
    /// @brief Value enumeration for @ref svNumbering field.
    enum class SvNumbering : std::uint8_t
    {
        Strict, ///< strict
        Extended, ///< extended
        NumOfValues ///< number of available values
    };

    /// @brief Value enumeration for @ref mainTalkerId field.
    enum class MainTalkerId : std::uint8_t
    {
        NotOverriden, ///< not overridden
        GP, ///< GP
        GL, ///< GL
        GN, ///< GN
        NumOfValues ///< number of available values
    };

    /// @brief Value enumeration for @ref gsvTalkerId field.
    enum class GsvTalkerId : std::uint8_t
    {
        GnssSpecific, ///<  use GNSS specific talker id
        Main, ///< use main talker id
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "gnssToFilter" field.
    struct gnssToFilter : public
        field::common::X4T<
            comms::option::BitmaskReservedBits<0xffffffcc, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(gps, sbas, qzss=4, glonass);
    };

    /// @brief Definition of "svNumbering" field.
    using svNumbering =
        field::common::EnumT<
            SvNumbering,
            comms::option::ValidNumValueRange<0, (int)SvNumbering::NumOfValues - 1>
        >;

    /// @brief Definition of "mainTalkerId" field.
    using mainTalkerId =
        field::common::EnumT<
            MainTalkerId,
            comms::option::ValidNumValueRange<0, (int)MainTalkerId::NumOfValues - 1>
        >;

    /// @brief Definition of "gsvTalkerId" field.
    using gsvTalkerId =
        field::common::EnumT<
            GsvTalkerId,
            comms::option::ValidNumValueRange<0, (int)GsvTalkerId::NumOfValues - 1>
        >;

    /// @brief Definition of "reserved" field.
    using reserved = field::common::res1;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        filter,
        nmeaVersion,
        numSV,
        flags,
        gnssToFilter,
        svNumbering,
        mainTalkerId,
        gsvTalkerId,
        reserved
    >;

};

/// @brief Definition of CFG-NMEA (@b extended) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgNmeaExtFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgNmeaExt : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NMEA>,
        comms::option::FieldsImpl<CfgNmeaExtFields::All>,
        comms::option::MsgType<CfgNmeaExt<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NMEA>,
        comms::option::FieldsImpl<CfgNmeaExtFields::All>,
        comms::option::MsgType<CfgNmeaExt<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b filter for @ref CfgNmeaFields::filter field
    ///     @li @b nmeaVersion for @ref CfgNmeaExtFields::nmeaVersion field
    ///     @li @b numSV for @ref CfgNmeaExtFields::numSV field
    ///     @li @b flags for @ref CfgNmeaFields::flags field
    ///     @li @b gnssToFilter for @ref CfgNmeaExtFields::gnssToFilter field
    ///     @li @b svNumbering for @ref CfgNmeaExtFields::svNumbering field
    ///     @li @b mainTalkerId for @ref CfgNmeaExtFields::mainTalkerId field
    ///     @li @b gsvTalkerId for @ref CfgNmeaExtFields::gsvTalkerId field
    ///     @li @b reserved for @ref CfgNmeaExtFields::reserved field
    COMMS_MSG_FIELDS_ACCESS(Base,
        filter,
        nmeaVersion,
        numSV,
        flags,
        gnssToFilter,
        svNumbering,
        mainTalkerId,
        gsvTalkerId,
        reserved
    );

    /// @brief Default constructor
    CfgNmeaExt() = default;

    /// @brief Copy constructor
    CfgNmeaExt(const CfgNmeaExt&) = default;

    /// @brief Move constructor
    CfgNmeaExt(CfgNmeaExt&& other) = default;

    /// @brief Destructor
    virtual ~CfgNmeaExt() = default;

    /// @brief Copy assignment
    CfgNmeaExt& operator=(const CfgNmeaExt&) = default;

    /// @brief Move assignment
    CfgNmeaExt& operator=(CfgNmeaExt&&) = default;
};


}  // namespace message

}  // namespace ublox

