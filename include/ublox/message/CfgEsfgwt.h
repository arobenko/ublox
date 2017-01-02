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
    /// @brief Bits access enumerator for @ref flags bitmask field.
    enum
    {
        flags_setVehicle = 12,  ///< @b setVehicle bit index
        flags_setTime, ///< @b setTime bit index
        flags_setWt, ///< @b setWt bit index
        flags_numOfValues ///< upper limit of available bits
    };

    /// @brief Definition of "flags" field.
    using flags =
        field::common::X2T<
            comms::option::BitmaskReservedBits<0x8fff, 0>
        >;

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
///     See @ref CfgEsfgwtFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgEsfgwt : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_ESFGWT>,
        comms::option::FieldsImpl<CfgEsfgwtFields::All>,
        comms::option::MsgType<CfgEsfgwt<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_ESFGWT>,
        comms::option::FieldsImpl<CfgEsfgwtFields::All>,
        comms::option::MsgType<CfgEsfgwt<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_flags, ///< @b flags field, see @ref CfgEsfgwtFields::flags
        FieldIdx_id, ///< @b id field, see @ref CfgEsfgwtFields::id
        FieldIdx_wtFactor, ///< @b wtFactor field, see @ref CfgEsfgwtFields::wtFactor
        FieldIdx_reserved1, ///< @b reserved1 field, see @ref CfgEsfgwtFields::reserved1
        FieldIdx_wtQuantError, ///< @b wtQuantError field, see @ref CfgEsfgwtFields::wtQuantError
        FieldIdx_timeTagFactor, ///< @b timeTagFactor field, see @ref CfgEsfgwtFields::timeTagFactor
        FieldIdx_wtCountMax, ///< @b wtCountMax field, see @ref CfgEsfgwtFields::wtCountMax
        FieldIdx_timeTagMax, ///< @b timeTagMax field, see @ref CfgEsfgwtFields::timeTagMax
        FieldIdx_wtLatency, ///< @b wtLatency field, see @ref CfgEsfgwtFields::wtLatency
        FieldIdx_reserved2, ///< @b reserved2 field, see @ref CfgEsfgwtFields::reserved2
        FieldIdx_wtFrequency, ///< @b wtFrequency field, see @ref CfgEsfgwtFields::wtFrequency
        FieldIdx_reserved3, ///< @b reserved3 field, see @ref CfgEsfgwtFields::reserved3
        FieldIdx_speedDeadBand, ///< @b speedDeadBand field, see @ref CfgEsfgwtFields::speedDeadBand
        FieldIdx_reserved4, ///< @b reserved4 field, see @ref CfgEsfgwtFields::reserved4
        FieldIdx_reserved5, ///< @b reserved5 field, see @ref CfgEsfgwtFields::reserved5
        FieldIdx_numOfValues ///< number of available fields
    };


    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        CfgEsfgwtFields::flags& flags; ///< @b flags field, see @ref CfgEsfgwtFields::flags
        CfgEsfgwtFields::id& id; ///< @b id field, see @ref CfgEsfgwtFields::id
        CfgEsfgwtFields::wtFactor& wtFactor; ///< @b wtFactor field, see @ref CfgEsfgwtFields::wtFactor
        CfgEsfgwtFields::reserved1& reserved1; ///< @b reserved1 field, see @ref CfgEsfgwtFields::reserved1
        CfgEsfgwtFields::wtQuantError& wtQuantError; ///< @b wtQuantError field, see @ref CfgEsfgwtFields::wtQuantError
        CfgEsfgwtFields::timeTagFactor& timeTagFactor; ///< @b timeTagFactor field, see @ref CfgEsfgwtFields::timeTagFactor
        CfgEsfgwtFields::wtCountMax& wtCountMax; ///< @b wtCountMax field, see @ref CfgEsfgwtFields::wtCountMax
        CfgEsfgwtFields::timeTagMax& timeTagMax; ///< @b timeTagMax field, see @ref CfgEsfgwtFields::timeTagMax
        CfgEsfgwtFields::wtLatency& wtLatency; ///< @b wtLatency field, see @ref CfgEsfgwtFields::wtLatency
        CfgEsfgwtFields::reserved2& reserved2; ///< @b reserved2 field, see @ref CfgEsfgwtFields::reserved2
        CfgEsfgwtFields::wtFrequency& wtFrequency; ///< @b wtFrequency field, see @ref CfgEsfgwtFields::wtFrequency
        CfgEsfgwtFields::reserved3& reserved3; ///< @b reserved3 field, see @ref CfgEsfgwtFields::reserved3
        CfgEsfgwtFields::speedDeadBand& speedDeadBand; ///< @b speedDeadBand field, see @ref CfgEsfgwtFields::speedDeadBand
        CfgEsfgwtFields::reserved4& reserved4; ///< @b reserved4 field, see @ref CfgEsfgwtFields::reserved4
        CfgEsfgwtFields::reserved5& reserved5; ///< @b reserved5 field, see @ref CfgEsfgwtFields::reserved5
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const CfgEsfgwtFields::flags& flags; ///< @b flags field, see @ref CfgEsfgwtFields::flags
        const CfgEsfgwtFields::id& id; ///< @b id field, see @ref CfgEsfgwtFields::id
        const CfgEsfgwtFields::wtFactor& wtFactor; ///< @b wtFactor field, see @ref CfgEsfgwtFields::wtFactor
        const CfgEsfgwtFields::reserved1& reserved1; ///< @b reserved1 field, see @ref CfgEsfgwtFields::reserved1
        const CfgEsfgwtFields::wtQuantError& wtQuantError; ///< @b wtQuantError field, see @ref CfgEsfgwtFields::wtQuantError
        const CfgEsfgwtFields::timeTagFactor& timeTagFactor; ///< @b timeTagFactor field, see @ref CfgEsfgwtFields::timeTagFactor
        const CfgEsfgwtFields::wtCountMax& wtCountMax; ///< @b wtCountMax field, see @ref CfgEsfgwtFields::wtCountMax
        const CfgEsfgwtFields::timeTagMax& timeTagMax; ///< @b timeTagMax field, see @ref CfgEsfgwtFields::timeTagMax
        const CfgEsfgwtFields::wtLatency& wtLatency; ///< @b wtLatency field, see @ref CfgEsfgwtFields::wtLatency
        const CfgEsfgwtFields::reserved2& reserved2; ///< @b reserved2 field, see @ref CfgEsfgwtFields::reserved2
        const CfgEsfgwtFields::wtFrequency& wtFrequency; ///< @b wtFrequency field, see @ref CfgEsfgwtFields::wtFrequency
        const CfgEsfgwtFields::reserved3& reserved3; ///< @b reserved3 field, see @ref CfgEsfgwtFields::reserved3
        const CfgEsfgwtFields::speedDeadBand& speedDeadBand; ///< @b speedDeadBand field, see @ref CfgEsfgwtFields::speedDeadBand
        const CfgEsfgwtFields::reserved4& reserved4; ///< @b reserved4 field, see @ref CfgEsfgwtFields::reserved4
        const CfgEsfgwtFields::reserved5& reserved5; ///< @b reserved5 field, see @ref CfgEsfgwtFields::reserved5
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base,
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
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    CfgEsfgwt() = default;

    /// @brief Copy constructor
    CfgEsfgwt(const CfgEsfgwt&) = default;

    /// @brief Move constructor
    CfgEsfgwt(CfgEsfgwt&& other) = default;

    /// @brief Destructor
    virtual ~CfgEsfgwt() = default;

    /// @brief Copy assignment
    CfgEsfgwt& operator=(const CfgEsfgwt&) = default;

    /// @brief Move assignment
    CfgEsfgwt& operator=(CfgEsfgwt&&) = default;
};


}  // namespace message

}  // namespace ublox

