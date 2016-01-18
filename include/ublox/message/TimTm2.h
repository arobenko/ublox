//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
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


#pragma once

#include "comms/Message.h"
#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

enum class TimTm2_TimeBase : std::uint8_t
{
    ReceiverTime,
    GPS,
    UTC,
    NumOfValues
};

enum
{
    TimTm2Field_flags_low,
    TimTm2Field_flags_timeBase,
    TimTm2Field_flags_high,
    TimTm2Field_flags_numOfValues
};

enum
{
    TimTm2Field_flags_low_mode,
    TimTm2Field_flags_low_run,
    TimTm2Field_flags_low_newFallingEdge,
    TimTm2Field_flags_low_numOfValues
};

enum
{
    TimTm2Field_flags_high_utc,
    TimTm2Field_flags_high_time,
    TimTm2Field_flags_high_newRisingEdge,
    TimTm2Field_flags_high_numOfValues
};

using TimTm2Field_ch =
    field::common::U1T<
        comms::option::ValidNumValueRange<0, 1>
    >;
using TimTm2Field_flags =
    comms::field::Bitfield<
        field::common::FieldBase,
        std::tuple<
            field::common::X1T<
                comms::option::FixedBitLength<3>,
                comms::option::BitmaskReservedBits<0xf8, 0>
            >,
            comms::field::EnumValue<
                field::common::FieldBase,
                TimTm2_TimeBase,
                comms::option::FixedBitLength<2>,
                comms::option::ValidNumValueRange<0, (int)TimTm2_TimeBase::NumOfValues - 1>
            >,
            field::common::X1T<
            comms::option::FixedBitLength<3>,
            comms::option::BitmaskReservedBits<0xf8, 0>
            >
        >
    >;
using TimTm2Field_count = field::common::U2;
using TimTm2Field_wnR = field::common::U2;
using TimTm2Field_wnF = field::common::U2;
using TimTm2Field_towMsR = field::common::U4T<field::common::Scaling_ms2s>;
using TimTm2Field_towSubMsR = field::common::U4T<field::common::Scaling_ns2s>;
using TimTm2Field_towMsF = field::common::U4T<field::common::Scaling_ms2s>;
using TimTm2Field_towSubMsF = field::common::U4T<field::common::Scaling_ns2s>;
using TimTm2Field_accEst = field::common::U4T<field::common::Scaling_ns2s>;

using TimTm2Fields = std::tuple<
    TimTm2Field_ch,
    TimTm2Field_flags,
    TimTm2Field_count,
    TimTm2Field_wnR,
    TimTm2Field_wnF,
    TimTm2Field_towMsR,
    TimTm2Field_towSubMsR,
    TimTm2Field_towMsF,
    TimTm2Field_towSubMsF,
    TimTm2Field_accEst
>;

template <typename TMsgBase = Message>
class TimTm2 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_TM2>,
        comms::option::FieldsImpl<TimTm2Fields>,
        comms::option::DispatchImpl<TimTm2<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_TM2>,
        comms::option::FieldsImpl<TimTm2Fields>,
        comms::option::DispatchImpl<TimTm2<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_ch,
        FieldIdx_flags,
        FieldIdx_count,
        FieldIdx_wnR,
        FieldIdx_wnF,
        FieldIdx_towMsR,
        FieldIdx_towSubMsR,
        FieldIdx_towMsF,
        FieldIdx_towSubMsF,
        FieldIdx_accEst,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    TimTm2() = default;

    /// @brief Copy constructor
    TimTm2(const TimTm2&) = default;

    /// @brief Move constructor
    TimTm2(TimTm2&& other) = default;

    /// @brief Destructor
    virtual ~TimTm2() = default;

    /// @brief Copy assignment
    TimTm2& operator=(const TimTm2&) = default;

    /// @brief Move assignment
    TimTm2& operator=(TimTm2&&) = default;
};


}  // namespace message

}  // namespace ublox

