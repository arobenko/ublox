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

enum NavSbasIndex
{
    NavSbasIndex_Svid,
    NavSbasIndex_Flags,
    NavSbasIndex_Udre,
    NavSbasIndex_Sys,
    NavSbasIndex_Service,
    NavSbasIndex_Res0,
    NavSbasIndex_Prc,
    NavSbasIndex_Res1,
    NavSbasIndex_Ic,
    NavSbasIndex_NumOfValues
};

using NavSbasElement =
    comms::field::Bundle<
        std::tuple<
            field::nav::SVID,
            field::nav::InfoFlags,
            field::nav::UDRE,
            field::nav::SYS,
            field::nav::SERVICE,
            field::common::res1,
            field::nav::PRCcm,
            field::common::res2,
            field::nav::IC
        >
    >;

using NavSbasFields = std::tuple<
    field::nav::ITOW,
    field::nav::GEO,
    field::nav::MODE,
    field::nav::SYS,
    field::nav::SERVICE,
    field::nav::CNT,
    field::common::res3,
    comms::field::ArrayList<
        field::common::FieldBase,
        NavSbasElement,
        comms::option::SequenceSizeForcingEnabled
    >
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
        FieldIdx_Itow,
        FieldIdx_Geo,
        FieldIdx_Mode,
        FieldIdx_Sys,
        FieldIdx_Service,
        FieldIdx_Cnt,
        FieldIdx_Res,
        FieldIdx_Data,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    NavSbas() = default;
    NavSbas(const NavSbas&) = default;
    NavSbas(NavSbas&& other)
    {
    }
    virtual ~NavSbas() = default;

    NavSbas& operator=(const NavSbas&) = default;
    NavSbas& operator=(NavSbas&&) = default;

protected:
    virtual comms::ErrorStatus readImpl(
        typename Base::ReadIterator& iter,
        std::size_t len) override
    {
        auto es = Base::template readFieldsUntil<FieldIdx_Data>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& cntField = std::get<FieldIdx_Cnt>(allFields);
        auto& dataField = std::get<FieldIdx_Data>(allFields);
        dataField.forceReadElemCount(cntField.value());

        return Base::template readFieldsFrom<FieldIdx_Data>(iter, len);
    }

    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& cntField = std::get<FieldIdx_Cnt>(allFields);
        auto& dataField = std::get<FieldIdx_Data>(allFields);
        if (cntField.value() == dataField.value().size()) {
            return false;
        }

        cntField.value() = dataField.value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





