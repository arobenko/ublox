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

enum class MonHw_AStatus : std::uint8_t
{
    INIT,
    DONTKNOW,
    OK,
    SHORT,
    OPEN,
    NumOfValues
};

enum class MonHw_APower : std::uint8_t
{
    OFF,
    ON,
    DONTKNOW,
    NumOfValues
};

enum class MonHw_JammingState : std::uint8_t
{
    Unknown,
    Ok,
    Warning,
    Critical,
    NumOfValues
};

enum
{
    MonHwField_flags_flags,
    MonHwField_flags_jammingState,
    MonHwField_flags_reserved,
    MonHwField_flags_numOfValues
};

enum
{
    MonHwField_flags_flags_rtcCalib,
    MonHwField_flags_flags_safeBoot,
    MonHwField_flags_flags_numOfValues
};


using MonHwField_pinSel = field::common::X4;
using MonHwField_pinBank = field::common::X4;
using MonHwField_pinDir = field::common::X4;
using MonHwField_pinVal = field::common::X4;
using MonHwField_noisePerMS = field::common::U2;
using MonHwField_agcCnt = field::common::U2T<comms::option::ValidNumValueRange<0, 8191> >;
using MonHwField_aStatus =
    comms::field::EnumValue<
        field::common::FieldBase,
        MonHw_AStatus,
        comms::option::ValidNumValueRange<0, (int)MonHw_AStatus::NumOfValues - 1>
    >;
using MonHwField_aPower =
    comms::field::EnumValue<
        field::common::FieldBase,
        MonHw_APower,
        comms::option::ValidNumValueRange<0, (int)MonHw_APower::NumOfValues - 1>
    >;
using MonHwField_flags =
    comms::field::Bitfield<
        field::common::FieldBase,
        std::tuple<
            field::common::X1T<
                comms::option::FixedBitLength<2>
            >,
            comms::field::EnumValue<
                field::common::FieldBase,
                MonHw_JammingState,
                comms::option::ValidNumValueRange<0, (int)MonHw_JammingState::NumOfValues - 1>,
                comms::option::FixedBitLength<2>
            >,
            field::common::res1T<
                comms::option::FixedBitLength<4>
            >
        >
    >;
using MonHwField_reserved1 = field::common::res1;
using MonHwField_usedMask = field::common::X4;
using MonHwField_VP =
    field::common::ListT<
        field::common::U1,
        comms::option::SequenceFixedSize<17>
    >;
using MonHwField_jamInd = field::common::U1;
using MonHwField_reserved3 = field::common::res2;
using MonHwField_pinIrq = field::common::X4;
using MonHwField_pullH = field::common::X4;
using MonHwField_pullL = field::common::X4;

using MonHwFields = std::tuple<
    MonHwField_pinSel,
    MonHwField_pinBank,
    MonHwField_pinDir,
    MonHwField_pinVal,
    MonHwField_noisePerMS,
    MonHwField_agcCnt,
    MonHwField_aStatus,
    MonHwField_aPower,
    MonHwField_flags,
    MonHwField_reserved1,
    MonHwField_usedMask,
    MonHwField_VP,
    MonHwField_jamInd,
    MonHwField_reserved3,
    MonHwField_pinIrq,
    MonHwField_pullH,
    MonHwField_pullL
>;


template <typename TMsgBase = Message>
class MonHw : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_HW>,
        comms::option::FieldsImpl<MonHwFields>,
        comms::option::DispatchImpl<MonHw<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_HW>,
        comms::option::FieldsImpl<MonHwFields>,
        comms::option::DispatchImpl<MonHw<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_pinSel,
        FieldIdx_pinBank,
        FieldIdx_pinDir,
        FieldIdx_pinVal,
        FieldIdx_noisePerMS,
        FieldIdx_agcCnt,
        FieldIdx_aStatus,
        FieldIdx_aPower,
        FieldIdx_flags,
        FieldIdx_reserved1,
        FieldIdx_usedMask,
        FieldIdx_VP,
        FieldIdx_jamInd,
        FieldIdx_reserved3,
        FieldIdx_pinIrq,
        FieldIdx_pullH,
        FieldIdx_pullL,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    MonHw() = default;
    MonHw(const MonHw&) = default;
    MonHw(MonHw&& other) = default;
    virtual ~MonHw() = default;

    MonHw& operator=(const MonHw&) = default;
    MonHw& operator=(MonHw&&) = default;
};


}  // namespace message

}  // namespace ublox

