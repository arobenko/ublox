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

#include <algorithm>

#include "comms/Message.h"
#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

enum class TimVrfy_Src : std::uint8_t
{
    None,
    Rtc = 2,
    AidIni = 3
};

struct TimVrfy_SrcValidator
{
    template <typename TField>
    bool operator()(const TField& field) const
    {
        auto value = field.value();
        static const TimVrfy_Src Values[] = {
            TimVrfy_Src::None,
            TimVrfy_Src::Rtc,
            TimVrfy_Src::AidIni
        };

        auto iter = std::lower_bound(std::begin(Values), std::end(Values), value);
        return (iter != std::end(Values)) && (*iter == value);
    }
};

using TimVrfyField_itow = field::common::I4T<field::common::Scaling_ms2s>;
using TimVrfyField_frac = field::common::I4T<field::common::Scaling_ns2s>;
using TimVrfyField_deltaMS = field::common::I4T<field::common::Scaling_ms2s>;
using TimVrfyField_deltaNS = field::common::I4T<field::common::Scaling_ns2s>;
using TimVrfyField_wno = field::common::U2;
using TimVrfyField_flags =
    comms::field::EnumValue<
        field::common::FieldBase,
        TimVrfy_Src,
        comms::option::ContentsValidator<TimVrfy_SrcValidator>
    >;
using TimVrfyField_reserved1 = field::common::res1;

using TimVrfyFields = std::tuple<
    TimVrfyField_itow,
    TimVrfyField_frac,
    TimVrfyField_deltaMS,
    TimVrfyField_deltaNS,
    TimVrfyField_wno,
    TimVrfyField_flags,
    TimVrfyField_reserved1
>;

template <typename TMsgBase = Message>
class TimVrfy : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_VRFY>,
        comms::option::FieldsImpl<TimVrfyFields>,
        comms::option::DispatchImpl<TimVrfy<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_TIM_VRFY>,
        comms::option::FieldsImpl<TimVrfyFields>,
        comms::option::DispatchImpl<TimVrfy<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_itow,
        FieldIdx_frac,
        FieldIdx_deltaMS,
        FieldIdx_deltaNS,
        FieldIdx_wno,
        FieldIdx_flags,
        FieldIdx_reserved1,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    TimVrfy() = default;
    TimVrfy(const TimVrfy&) = default;
    TimVrfy(TimVrfy&& other) = default;
    virtual ~TimVrfy() = default;

    TimVrfy& operator=(const TimVrfy&) = default;
    TimVrfy& operator=(TimVrfy&&) = default;
};


}  // namespace message

}  // namespace ublox

