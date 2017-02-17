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
/// @brief Contains definition of CFG-NMEA (@b extended @b v1) message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"
#include "CfgNmeaExt.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-NMEA (@b extended @b v1) message fields.
/// @see CfgNmeaExtV1
struct CfgNmeaExtV1Fields : public CfgNmeaExtFields
{
    /// @brief Value enumeration for @ref nmeaVersion field.
    enum class NmeaVersion : std::uint8_t
    {
        v21 = 0x21, ///< NMEA version 2.1
        v23 = 0x23, ///< NMEA version 2.3
        v40 = 0x40, ///< NMEA version 4.0
        v41 = 0x41, ///< NMEA version 4.1
    };

    /// @brief Custom validator class for @ref nmeaVersion field
    struct NmeaVersionValidator
    {
        template <typename TField>
        bool operator()(const TField& field) const
        {
            auto value = field.value();
            return ((value == NmeaVersion::v21) ||
                    (value == NmeaVersion::v23) ||
                    (value == NmeaVersion::v40) ||
                    (value == NmeaVersion::v41));
        }
    };

    /// @brief Definition of "nmeaVersion" field.
    using nmeaVersion =
        field::common::EnumT<
            NmeaVersion,
            comms::option::ContentsValidator<NmeaVersionValidator>,
            comms::option::DefaultNumValue<(int)NmeaVersion::v41>
        >;

    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xf8, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(compat, consider, limit82);
    };


    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<1, 1>,
            comms::option::DefaultNumValue<1>,
            comms::option::FailOnInvalid
        >;

    /// @brief Definition of "bdsTalkerId" field.
    /// @tparam TOpt Extra options for string field
    template <typename TOpt = comms::option::EmptyOption>
    using bdsTalkerId =
        field::common::StringT<
            comms::option::SequenceFixedSize<2>,
            TOpt
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res2;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res4;


    /// @brief All the fields bundled in std::tuple.
    /// @tparam TOpt Extra options for @ref bdsTalkerId field
    template <typename TOpt>
    using All = std::tuple<
        filter,
        nmeaVersion,
        numSV,
        flags,
        gnssToFilter,
        svNumbering,
        mainTalkerId,
        gsvTalkerId,
        version,
        bdsTalkerId<TOpt>,
        reserved1,
        reserved2
    >;
};

/// @brief Definition of CFG-NMEA (@b extended) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgNmeaExtV1Fields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TBdsTalkerIdOpt Extra option(s) for @b bdsTalkerId field
template <typename TMsgBase = Message, typename TBdsTalkerIdOpt = comms::option::EmptyOption>
class CfgNmeaExtV1 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NMEA>,
        comms::option::FieldsImpl<CfgNmeaExtV1Fields::All<TBdsTalkerIdOpt> >,
        comms::option::MsgType<CfgNmeaExtV1<TMsgBase, TBdsTalkerIdOpt> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b filter for @ref CfgNmeaFields::filter field
    ///     @li @b nmeaVersion for @ref CfgNmeaExtV1Fields::nmeaVersion field
    ///     @li @b numSV for @ref CfgNmeaExtFields::numSV field
    ///     @li @b flags for @ref CfgNmeaExtV1Fields::flags field
    ///     @li @b gnssToFilter for @ref CfgNmeaExtFields::gnssToFilter field
    ///     @li @b svNumbering for @ref CfgNmeaExtFields::svNumbering field
    ///     @li @b mainTalkerId for @ref CfgNmeaExtFields::mainTalkerId field
    ///     @li @b gsvTalkerId for @ref CfgNmeaExtFields::gsvTalkerId field
    ///     @li @b version for @ref CfgNmeaExtV1Fields::version field
    ///     @li @b bdsTalkerId for @ref CfgNmeaExtV1Fields::bdsTalkerId field
    ///     @li @b reserved1 for @ref CfgNmeaExtV1Fields::reserved1 field
    ///     @li @b reserved2 for @ref CfgNmeaExtV1Fields::reserved2 field
    COMMS_MSG_FIELDS_ACCESS(
        filter,
        nmeaVersion,
        numSV,
        flags,
        gnssToFilter,
        svNumbering,
        mainTalkerId,
        gsvTalkerId,
        version,
        bdsTalkerId,
        reserved1,
        reserved2
    );

    /// @brief Default constructor
    CfgNmeaExtV1() = default;

    /// @brief Copy constructor
    CfgNmeaExtV1(const CfgNmeaExtV1&) = default;

    /// @brief Move constructor
    CfgNmeaExtV1(CfgNmeaExtV1&& other) = default;

    /// @brief Destructor
    virtual ~CfgNmeaExtV1() = default;

    /// @brief Copy assignment
    CfgNmeaExtV1& operator=(const CfgNmeaExtV1&) = default;

    /// @brief Move assignment
    CfgNmeaExtV1& operator=(CfgNmeaExtV1&&) = default;
};


}  // namespace message

}  // namespace ublox

