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
/// @brief Contains definition of CFG-TP message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-TP message fields.
/// @see CfgTp
struct CfgTpFields
{
    /// @b Value enumeration for @ref status field.
    enum class Status : std::int8_t
    {
        Negative = -1, ///< negative time pulse
        Off = 0, ///< time pulse is off
        Positive = 1 ///< positive time pulse
    };

    /// @b Value enumeration for @ref timeRef field.
    enum class TimeRef : std::uint8_t
    {
        Utc, ///< UTC time
        Gps, ///< GPS time
        Local, ///< Local time
        NumOfValues ///< number  of available values
    };

    /// @brief Bits access enumeration for @ref flags bitmask field.
    enum
    {
        flags_syncMode, ///< @b syncMode bit index
        flags_numOfValues ///< number of available bits
    };

    /// @brief Definition of "interval" field.
    using interval = field::common::U4T<field::common::Scaling_us2s>;

    /// @brief Definition of "length" field.
    using length = field::common::U4T<field::common::Scaling_us2s>;

    /// @brief Definition of "status" field.
    using status =
        field::common::EnumT<
            Status,
            comms::option::ValidNumValueRange<(int)Status::Negative, (int)Status::Positive>
        >;

    /// @brief Definition of "timeRef" field.
    using timeRef =
        field::common::EnumT<
            TimeRef,
            comms::option::ValidNumValueRange<0, (int)TimeRef::NumOfValues - 1>
        >;

    /// @brief Definition of "flags" field.
    using flags = field::common::X1T<comms::option::BitmaskReservedBits<0xfe, 0> >;

    /// @brief Definition of "res" field.
    using res = field::common::res1;

    /// @brief Definition of "antennaCableDelay" field.
    using antennaCableDelay = field::common::I2T<field::common::Scaling_ns2s>;

    /// @brief Definition of "rfGroupDelay" field.
    using rfGroupDelay = field::common::I2T<field::common::Scaling_ns2s>;

    /// @brief Definition of "userDelay" field.
    using userDelay = field::common::I4T<field::common::Scaling_ns2s>;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        interval,
        length,
        status,
        timeRef,
        flags,
        res,
        antennaCableDelay,
        rfGroupDelay,
        userDelay
    >;
};

/// @brief Definition of CFG-TP message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgTpFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgTp : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TP>,
        comms::option::FieldsImpl<CfgTpFields::All>,
        comms::option::MsgType<CfgTp<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TP>,
        comms::option::FieldsImpl<CfgTpFields::All>,
        comms::option::MsgType<CfgTp<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_interval, ///< @b interval field, see @ref CfgTpFields::interval
        FieldIdx_length, ///< @b length field, see @ref CfgTpFields::length
        FieldIdx_status, ///< @b status field, see @ref CfgTpFields::status
        FieldIdx_timeRef, ///< @b timeRef field, see @ref CfgTpFields::timeRef
        FieldIdx_flags, ///< @b flags field, see @ref CfgTpFields::flags
        FieldIdx_res, ///< @b res field, see @ref CfgTpFields::res
        FieldIdx_antennaCableDelay, ///< @b antennaCableDelay field, see @ref CfgTpFields::antennaCableDelay
        FieldIdx_rfGroupDelay, ///< @b rfGroupDelay field, see @ref CfgTpFields::rfGroupDelay
        FieldIdx_userDelay, ///< @b userDelay field, see @ref CfgTpFields::userDelay
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        CfgTpFields::interval& interval; ///< @b interval field, see @ref CfgTpFields::interval
        CfgTpFields::length& length; ///< @b length field, see @ref CfgTpFields::length
        CfgTpFields::status& status; ///< @b status field, see @ref CfgTpFields::status
        CfgTpFields::timeRef& timeRef; ///< @b timeRef field, see @ref CfgTpFields::timeRef
        CfgTpFields::flags& flags; ///< @b flags field, see @ref CfgTpFields::flags
        CfgTpFields::res& res; ///< @b res field, see @ref CfgTpFields::res
        CfgTpFields::antennaCableDelay& antennaCableDelay; ///< @b antennaCableDelay field, see @ref CfgTpFields::antennaCableDelay
        CfgTpFields::rfGroupDelay& rfGroupDelay; ///< @b rfGroupDelay field, see @ref CfgTpFields::rfGroupDelay
        CfgTpFields::userDelay& userDelay; ///< @b userDelay field, see @ref CfgTpFields::userDelay
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const CfgTpFields::interval& interval; ///< @b interval field, see @ref CfgTpFields::interval
        const CfgTpFields::length& length; ///< @b length field, see @ref CfgTpFields::length
        const CfgTpFields::status& status; ///< @b status field, see @ref CfgTpFields::status
        const CfgTpFields::timeRef& timeRef; ///< @b timeRef field, see @ref CfgTpFields::timeRef
        const CfgTpFields::flags& flags; ///< @b flags field, see @ref CfgTpFields::flags
        const CfgTpFields::res& res; ///< @b res field, see @ref CfgTpFields::res
        const CfgTpFields::antennaCableDelay& antennaCableDelay; ///< @b antennaCableDelay field, see @ref CfgTpFields::antennaCableDelay
        const CfgTpFields::rfGroupDelay& rfGroupDelay; ///< @b rfGroupDelay field, see @ref CfgTpFields::rfGroupDelay
        const CfgTpFields::userDelay& userDelay; ///< @b userDelay field, see @ref CfgTpFields::userDelay
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base,
        interval,
        length,
        status,
        timeRef,
        flags,
        res,
        antennaCableDelay,
        rfGroupDelay,
        userDelay
    );
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    CfgTp() = default;

    /// @brief Copy constructor
    CfgTp(const CfgTp&) = default;

    /// @brief Move constructor
    CfgTp(CfgTp&& other) = default;

    /// @brief Destructor
    virtual ~CfgTp() = default;

    /// @brief Copy assignment
    CfgTp& operator=(const CfgTp&) = default;

    /// @brief Move assignment
    CfgTp& operator=(CfgTp&&) = default;
};


}  // namespace message

}  // namespace ublox

