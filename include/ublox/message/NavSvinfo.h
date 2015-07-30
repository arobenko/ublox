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

enum NavSvinfoIndex
{
    NavSvinfoIndex_Chn,
    NavSvinfoIndex_Svid,
    NavSvinfoIndex_Flags,
    NavSvinfoIndex_Qi,
    NavSvinfoIndex_Cno,
    NavSvinfoIndex_Elev,
    NavSvinfoIndex_Azim,
    NavSvinfoIndex_Prres,
    NavSvinfoIndex_NumOfValues
};

using NavSvinfoElement =
    comms::field::Bundle<
        std::tuple<
            field::nav::chn,
            field::nav::SVID,
            field::nav::InfoFlags,
            field::nav::QI,
            field::nav::CNO,
            field::nav::Elev,
            field::nav::Azim,
            field::nav::PRRes
        >
    >;

using NavSvinfoFields = std::tuple<
    field::nav::ITOW,
    field::nav::NCH,
    field::common::res1,
    field::common::res2,
    comms::field::ArrayList<
        field::common::FieldBase,
        NavSvinfoElement,
        comms::option::SequenceSizeForcingEnabled
    >
>;


template <typename TMsgBase = Message>
class NavSvinfo : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SVINFO>,
        comms::option::FieldsImpl<NavSvinfoFields>,
        comms::option::DispatchImpl<NavSvinfo<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SVINFO>,
        comms::option::FieldsImpl<NavSvinfoFields>,
        comms::option::DispatchImpl<NavSvinfo<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_Itow,
        FieldIdx_Nch,
        FieldIdx_Res1,
        FieldIdx_Res2,
        FieldIdx_Info,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    NavSvinfo() = default;
    NavSvinfo(const NavSvinfo&) = default;
    NavSvinfo(NavSvinfo&& other) = default;
    virtual ~NavSvinfo() = default;

    NavSvinfo& operator=(const NavSvinfo&) = default;
    NavSvinfo& operator=(NavSvinfo&&) = default;

protected:
    virtual comms::ErrorStatus readImpl(
        typename Base::ReadIterator& iter,
        std::size_t len) override
    {
        auto es = Base::template readFieldsUntil<FieldIdx_Info>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& nchField = std::get<FieldIdx_Nch>(allFields);
        auto& infoField = std::get<FieldIdx_Info>(allFields);
        infoField.forceReadElemCount(nchField.value());

        return Base::template readFieldsFrom<FieldIdx_Info>(iter, len);
    }

    virtual bool validImpl() const override
    {
        if (!Base::validImpl()) {
            return false;
        }

        auto& allFields = Base::fields();
        auto& nchField = std::get<FieldIdx_Nch>(allFields);
        auto& infoField = std::get<FieldIdx_Info>(allFields);
        for (auto& bundleField : infoField.value()) {
            auto& members = bundleField.value();
            auto& chNumField = std::get<NavSvinfoIndex_Chn>(members);
            if (nchField.value() <= chNumField.value()) {
                return false;
            }
        }

        return true;
    }

    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& nchField = std::get<FieldIdx_Nch>(allFields);
        auto& infoField = std::get<FieldIdx_Info>(allFields);
        if (nchField.value() == infoField.value().size()) {
            return false;
        }

        nchField.value() = infoField.value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





