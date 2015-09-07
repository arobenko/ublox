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
#include "ublox/field/MsgId.h"
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

enum
{
    CfgRstField_navBbrMask_eph,
    CfgRstField_navBbrMask_alm,
    CfgRstField_navBbrMask_health,
    CfgRstField_navBbrMask_klob,
    CfgRstField_navBbrMask_pos,
    CfgRstField_navBbrMask_clkd,
    CfgRstField_navBbrMask_osc,
    CfgRstField_navBbrMask_utc,
    CfgRstField_navBbrMask_rtc,
    CfgRstField_navBbrMask_res0,
    CfgRstField_navBbrMask_res1,
    CfgRstField_navBbrMask_sfdr,
    CfgRstField_navBbrMask_vmon,
    CfgRstField_navBbrMask_tct,
    CfgRstField_navBbrMask_res2,
    CfgRstField_navBbrMask_aop,
    CfgRstField_navBbrMask_numOfValues
};

enum class CfgRst_ResetMode : std::uint8_t
{
    Hardware,
    Software,
    GnssOnly,
    HardwareAfterShutdown = 4,
    GnssStop = 8,
    GnssStart
};

struct CfgRst_ResetModeValidator
{
    template <typename TField>
    bool operator()(const TField& field) const
    {
        static const CfgRst_ResetMode Values[] =
        {
            CfgRst_ResetMode::Hardware,
            CfgRst_ResetMode::Software,
            CfgRst_ResetMode::GnssOnly,
            CfgRst_ResetMode::HardwareAfterShutdown,
            CfgRst_ResetMode::GnssStop,
            CfgRst_ResetMode::GnssStart
        };
        auto value = field.value();
        auto iter = std::lower_bound(std::begin(Values), std::end(Values), value);
        return (iter != std::end(Values)) && (*iter == value);
    }
};

using CfgRstField_navBbrMask = field::common::X2;
using CfgRstField_resetMode =
    comms::field::EnumValue<
        field::common::FieldBase,
        CfgRst_ResetMode,
        comms::option::ContentsValidator<CfgRst_ResetModeValidator>
    >;
using CfgRstField_reserved1 = field::common::res1;


using CfgRstFields = std::tuple<
    CfgRstField_navBbrMask,
    CfgRstField_resetMode,
    CfgRstField_reserved1
>;

template <typename TMsgBase = Message>
class CfgRst : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RST>,
        comms::option::FieldsImpl<CfgRstFields>,
        comms::option::DispatchImpl<CfgRst<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RST>,
        comms::option::FieldsImpl<CfgRstFields>,
        comms::option::DispatchImpl<CfgRst<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_navBbrMask,
        FieldIdx_resetMask,
        FieldIdx_reserved1,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    CfgRst() = default;
    CfgRst(const CfgRst&) = default;
    CfgRst(CfgRst&& other) = default;
    virtual ~CfgRst() = default;

    CfgRst& operator=(const CfgRst&) = default;
    CfgRst& operator=(CfgRst&&) = default;
};


}  // namespace message

}  // namespace ublox

