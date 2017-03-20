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
/// @brief Contains definition of CFG-ESFGWT message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-ESFGWT message fields.
/// @see CfgEsfgwt
struct CfgEsfgwtFields
{
    /// @brief Definition of "flags" field.
    struct flags : public
        field::common::X2T<
            comms::option::BitmaskReservedBits<0x8fff, 0>
        >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(setVehicle=12, setTime, setWt);
    };

    /// @brief Definition of "id" field.
    using id = field::common::U2;

    /// @brief Definition of "wtFactor" field.
    using wtFactor =
        field::common::U4T<
            comms::option::ScalingRatio<1, 1000000L>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res4;

    /// @brief Definition of "wtQuantError" field.
    using wtQuantError =
        field::common::U4T<
            comms::option::ScalingRatio<1, 1000000L>
        >;

    /// @brief Definition of "timeTagFactor" field.
    using timeTagFactor =
        field::common::U4T<
            comms::option::ScalingRatio<1, 1000000L>
        >;

    /// @brief Definition of "wtCountMax" field.
    using wtCountMax = field::common::U4;

    /// @brief Definition of "timeTagMax" field.
    using timeTagMax = field::common::U4;

    /// @brief Definition of "wtLantency" field.
    using wtLatency =
        field::common::U2T<
            field::common::Scaling_ms2s
        >;

    /// @brief Definition of "reserved" field.
    using reserved2 = field::common::res2;

    /// @brief Definition of "wtFrequency" field.
    using wtFrequency = field::common::U1;

    /// @brief Definition of "reserved3" field.
    using reserved3 = field::common::res1;

    /// @brief Definition of "speedDeadBand" field.
    using speedDeadBand =
        field::common::U2T<
            field::common::Scaling_cm2m
        >;

    /// @brief Definition of "reserved4" field.
    using reserved4 = field::common::res4;

    /// @brief Definition of "reserved5" field.
    using reserved5 = field::common::res4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        flags,
        id,
        wtFactor,
        reserved1,
        wtQuantError,
        timeTagFactor,
        wtCountMax,
        timeTagMax,
        wtLatency,
        reserved2,
        wtFrequency,
        reserved3,
        speedDeadBand,
        reserved4,
        reserved5
    >;
};

/// @brief Definition of CFG-ESFGWT message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgEsfgwtFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgEsfgwt : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_ESFGWT>,
        comms::option::FieldsImpl<CfgEsfgwtFields::All>,
        comms::option::MsgType<CfgEsfgwt<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_ESFGWT>,
        comms::option::FieldsImpl<CfgEsfgwtFields::All>,
        comms::option::MsgType<CfgEsfgwt<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b flags for @ref CfgEsfgwtFields::flags field
    ///     @li @b id for @ref CfgEsfgwtFields::id field
    ///     @li @b wtFactor for @ref CfgEsfgwtFields::wtFactor field
    ///     @li @b reserved1 for @ref CfgEsfgwtFields::reserved1 field
    ///     @li @b wtQuantError for @ref CfgEsfgwtFields::wtQuantError field
    ///     @li @b timeTagFactor for @ref CfgEsfgwtFields::timeTagFactor field
    ///     @li @b wtCountMax for @ref CfgEsfgwtFields::wtCountMax field
    ///     @li @b timeTagMax for @ref CfgEsfgwtFields::timeTagMax field
    ///     @li @b wtLatency for @ref CfgEsfgwtFields::wtLatency field
    ///     @li @b reserved2 for @ref CfgEsfgwtFields::reserved2 field
    ///     @li @b wtFrequency for @ref CfgEsfgwtFields::wtFrequency field
    ///     @li @b reserved3 for @ref CfgEsfgwtFields::reserved3 field
    ///     @li @b speedDeadBand for @ref CfgEsfgwtFields::speedDeadBand field
    ///     @li @b reserved4 for @ref CfgEsfgwtFields::reserved4 field
    ///     @li @b reserved5 for @ref CfgEsfgwtFields::reserved5 field
    COMMS_MSG_FIELDS_ACCESS(
        flags,
        id,
        wtFactor,
        reserved1,
        wtQuantError,
        timeTagFactor,
        wtCountMax,
        timeTagMax,
        wtLatency,
        reserved2,
        wtFrequency,
        reserved3,
        speedDeadBand,
        reserved4,
        reserved5
    );

    /// @brief Default constructor
    CfgEsfgwt() = default;

    /// @brief Copy constructor
    CfgEsfgwt(const CfgEsfgwt&) = default;

    /// @brief Move constructor
    CfgEsfgwt(CfgEsfgwt&& other) = default;

    /// @brief Destructor
    ~CfgEsfgwt() = default;

    /// @brief Copy assignment
    CfgEsfgwt& operator=(const CfgEsfgwt&) = default;

    /// @brief Move assignment
    CfgEsfgwt& operator=(CfgEsfgwt&&) = default;
};


}  // namespace message

}  // namespace ublox

