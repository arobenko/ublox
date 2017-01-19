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
    struct flags : public field::common::X1T<comms::option::BitmaskReservedBits<0xfe, 0> >
    {
        /// @brief Provide names for internal bits.
        /// @details See definition of @b COMMS_BITMASK_BITS macro
        ///     related to @b comms::field::BitmaskValue class from COMMS library
        ///     for details.
        COMMS_BITMASK_BITS(syncMode);
    };

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
///     See @ref CfgTpFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgTp : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TP>,
        comms::option::FieldsImpl<CfgTpFields::All>,
        comms::option::MsgType<CfgTp<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TP>,
        comms::option::FieldsImpl<CfgTpFields::All>,
        comms::option::MsgType<CfgTp<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b interval for @ref CfgTpFields::interval field
    ///     @li @b length for @ref CfgTpFields::length field
    ///     @li @b status for @ref CfgTpFields::status field
    ///     @li @b timeRef for @ref CfgTpFields::timeRef field
    ///     @li @b flags for @ref CfgTpFields::flags field
    ///     @li @b res for @ref CfgTpFields::res field
    ///     @li @b antennaCableDelay for @ref CfgTpFields::antennaCableDelay field
    ///     @li @b rfGroupDelay for @ref CfgTpFields::rfGroupDelay field
    ///     @li @b userDelay for @ref CfgTpFields::userDelay field
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

