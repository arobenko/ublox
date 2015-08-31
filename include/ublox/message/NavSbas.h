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

#include <iterator>

#include "comms/Message.h"
#include "ublox/Message.h"

#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

enum class NavSbas_Mode : std::uint8_t
{
    Disabled,
    EnabledIntegrity,
    EnabledTestmode = 3
};

enum class NavSbas_Sys : std::int8_t
{
    Unknown = -1,
    WAAS = 0,
    EGNOS = 1,
    MSAS = 2,
    GPS = 16,
};

enum
{
    NavSbas_service_Ranging,
    NavSbas_service_Corrections,
    NavSbas_service_Integrity,
    NavSbas_service_Testmode,
    NavSbas_service_NumOfValues
};

struct NavSbas_ModeValidator
{
    template <typename TField>
    bool operator()(const TField& field) const
    {
        auto value = field.value();
        return
            (value == NavSbas_Mode::Disabled) ||
            (value == NavSbas_Mode::EnabledIntegrity) ||
            (value == NavSbas_Mode::EnabledTestmode);
    }
};

struct NavSbas_SysValidator
{
    template <typename TField>
    bool operator()(const TField& field) const
    {
        static const NavSbas_Sys Values[] = {
            NavSbas_Sys::Unknown,
            NavSbas_Sys::WAAS,
            NavSbas_Sys::EGNOS,
            NavSbas_Sys::MSAS,
            NavSbas_Sys::GPS,
        };

        auto value = field.value();
        auto iter = std::lower_bound(std::begin(Values), std::end(Values), value);
        return (iter != std::end(Values)) && (*iter == value);
    }
};

using NavSbasField_iTOW = field::nav::iTOW;
using NavSbasField_geo = field::common::U1;
using NavSbasField_mode =
    comms::field::EnumValue<
        field::common::FieldBase,
        NavSbas_Mode,
        comms::option::ContentsValidator<NavSbas_ModeValidator>
    >;
using NavSbasField_sys =
    comms::field::EnumValue<
        field::common::FieldBase,
        NavSbas_Sys,
        comms::option::ContentsValidator<NavSbas_SysValidator>
    >;
using NavSbasField_service =
    field::common::X1T<
        comms::option::BitmaskReservedBits<0xf0, 0>
    >;
using NavSbasField_cnt = field::common::U1;
using NavSbasField_reserved0 = field::common::res3;

using NavSbasField_svid = field::nav::svid;
using NavSbasField_flags = field::common::U1;
using NavSbasField_udre = field::common::U1;
using NavSbasField_svSys = NavSbasField_sys;
using NavSbasField_svService = NavSbasField_service;
using NavSbasField_reserved1 = field::common::res1;
using NavSbasField_prc = field::common::U2T<field::common::Scaling_cm2m>;
using NavSbasField_reserved2 = field::common::res2;
using NavSbasField_ic = field::common::U2T<field::common::Scaling_cm2m>;

using NavSbasField_data =
    comms::field::ArrayList<
        field::common::FieldBase,
        comms::field::Bundle<
            std::tuple<
                NavSbasField_svid,
                NavSbasField_flags,
                NavSbasField_udre,
                NavSbasField_svSys,
                NavSbasField_svService,
                NavSbasField_reserved1,
                NavSbasField_prc,
                NavSbasField_reserved2,
                NavSbasField_ic
            >
        >,
        comms::option::SequenceSizeForcingEnabled
    >;


using NavSbasFields = std::tuple<
    NavSbasField_iTOW,
    NavSbasField_geo,
    NavSbasField_mode,
    NavSbasField_sys,
    NavSbasField_service,
    NavSbasField_cnt,
    NavSbasField_reserved0,
    NavSbasField_data
>;

template <typename TMsgBase = Message>
class NavSbas : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SBAS>,
        comms::option::FieldsImpl<NavSbasFields>,
        comms::option::DispatchImpl<NavSbas<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SBAS>,
        comms::option::FieldsImpl<NavSbasFields>,
        comms::option::DispatchImpl<NavSbas<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_iTOW,
        FieldIdx_geo,
        FieldIdx_mode,
        FieldIdx_sys,
        FieldIdx_service,
        FieldIdx_cnt,
        FieldIdx_reserved0,
        FieldIdx_data,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    NavSbas() = default;
    NavSbas(const NavSbas&) = default;
    NavSbas(NavSbas&& other) = default;
    virtual ~NavSbas() = default;

    NavSbas& operator=(const NavSbas&) = default;
    NavSbas& operator=(NavSbas&&) = default;

protected:
    virtual comms::ErrorStatus readImpl(
        typename Base::ReadIterator& iter,
        std::size_t len) override
    {
        auto es = Base::template readFieldsUntil<FieldIdx_data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& cntField = std::get<FieldIdx_cnt>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        dataField.forceReadElemCount(cntField.value());

        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& cntField = std::get<FieldIdx_cnt>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        if (cntField.value() == dataField.value().size()) {
            return false;
        }

        cntField.value() = dataField.value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





