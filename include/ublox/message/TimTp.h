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
/// @brief Contains definition of TIM-TP message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the TIM-TP message fields.
/// @see TimTp
struct TimTpFields
{
    /// @brief Definition of "towMS" field.
    using towMS = field::common::U4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "towSubMS" field.
    using towSubMS = field::common::U4T<comms::option::ScalingRatio<1, 0x20> >;

    /// @brief Definition of "qErr" field.
    using qErr = field::common::I4;

    /// @brief Definition of "week" field.
    using week = field::common::U2;

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
        COMMS_BITMASK_BITS(timeBase, utc);
    };

    /// @brief Definition of "reserved" field.
    using reserved = field::common::res1;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        towMS,
        towSubMS,
        qErr,
        week,
        flags,
        reserved
    >;
};

/// @brief Definition of TIM-TP message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref TimTpFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class TimTp : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_TP>,
        comms::option::FieldsImpl<TimTpFields::All>,
        comms::option::MsgType<TimTp<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_TP>,
        comms::option::FieldsImpl<TimTpFields::All>,
        comms::option::MsgType<TimTp<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b towMS for @ref TimTpFields::towMS field
    ///     @li @b towSubMS for @ref TimTpFields::towSubMS field
    ///     @li @b qErr for @ref TimTpFields::qErr field
    ///     @li @b week for @ref TimTpFields::week field
    ///     @li @b flags for @ref TimTpFields::flags field
    ///     @li @b reserved for @ref TimTpFields::reserved field
    COMMS_MSG_FIELDS_ACCESS(towMS, towSubMS, qErr, week, flags, reserved);

    /// @brief Default constructor
    TimTp() = default;

    /// @brief Copy constructor
    TimTp(const TimTp&) = default;

    /// @brief Move constructor
    TimTp(TimTp&& other) = default;

    /// @brief Destructor
    virtual ~TimTp() = default;

    /// @brief Copy assignment
    TimTp& operator=(const TimTp&) = default;

    /// @brief Move assignment
    TimTp& operator=(TimTp&&) = default;
};


}  // namespace message

}  // namespace ublox

