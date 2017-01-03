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
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref TimTpFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class TimTp : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_TP>,
        comms::option::FieldsImpl<TimTpFields::All>,
        comms::option::MsgType<TimTp<TMsgBase> >,
        comms::option::DispatchImpl
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_TP>,
        comms::option::FieldsImpl<TimTpFields::All>,
        comms::option::MsgType<TimTp<TMsgBase> >,
        comms::option::DispatchImpl
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
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

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        TimTpFields::towMS& towMS; ///< @b towMS field, see @ref TimTpFields::towMS
        TimTpFields::towSubMS& towSubMS; ///< @b towSubMS field, see @ref TimTpFields::towSubMS
        TimTpFields::qErr& qErr; ///< @b qErr field, see @ref TimTpFields::qErr
        TimTpFields::week& week; ///< @b week field, see @ref TimTpFields::week
        TimTpFields::flags& flags; ///< @b flags field, see @ref TimTpFields::flags
        TimTpFields::reserved& reserved; ///< @b reserved field, see @ref TimTpFields::reserved
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const TimTpFields::towMS& towMS; ///< @b towMS field, see @ref TimTpFields::towMS
        const TimTpFields::towSubMS& towSubMS; ///< @b towSubMS field, see @ref TimTpFields::towSubMS
        const TimTpFields::qErr& qErr; ///< @b qErr field, see @ref TimTpFields::qErr
        const TimTpFields::week& week; ///< @b week field, see @ref TimTpFields::week
        const TimTpFields::flags& flags; ///< @b flags field, see @ref TimTpFields::flags
        const TimTpFields::reserved& reserved; ///< @b reserved field, see @ref TimTpFields::reserved
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, towMS, towSubMS, qErr, week, flags, reserved);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

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

