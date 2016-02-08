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
    /// @brief Bits access enumeration for bits in @ref flags bitmask field.
    enum
    {
        flags_timeBase, ///< @b timeBase bit index
        flags_utc, ///< @b utc bit index
        flags_numOfValues ///< number of available bits
    };

    /// @brief Definition of "towMS" field.
    using towMS = field::common::U4T<field::common::Scaling_ms2s>;

    /// @brief Definition of "towSubMS" field.
    using towSubMS = field::common::U4T<comms::option::ScalingRatio<1, 0x20> >;

    /// @brief Definition of "qErr" field.
    using qErr = field::common::I4;

    /// @brief Definition of "week" field.
    using week = field::common::U2;

    /// @brief Definition of "flags" field.
    using flags =
        field::common::X1T<
            comms::option::BitmaskReservedBits<0xfc, 0>
        >;

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
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref TimTpFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class TimTp : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_TP>,
        comms::option::FieldsImpl<TimTpFields::All>,
        comms::option::DispatchImpl<TimTp<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_TP>,
        comms::option::FieldsImpl<TimTpFields::All>,
        comms::option::DispatchImpl<TimTp<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_towMS, ///< @b towMS field, see @ref TimTpFields::towMS
        FieldIdx_towSubMS, ///< @b towSubMS field, see @ref TimTpFields::towSubMS
        FieldIdx_qErr, ///< @b qErr field, see @ref TimTpFields::qErr
        FieldIdx_week, ///< @b week field, see @ref TimTpFields::week
        FieldIdx_flags, ///< @b flags field, see @ref TimTpFields::flags
        FieldIdx_reserved, ///< @b reserved field, see @ref TimTpFields::reserved
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

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

