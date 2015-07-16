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

enum NavDgpsFlagsIndex
{
    NavDgpsFlagsIndex_Chn,
    NavDgpsFlagsIndex_UsedFlags,
    NavDgpsFlagsIndex_NumOfValues
};

enum NavDgpsIndex
{
    NavDgpsIndex_Svid,
    NavDgpsIndex_Flags,
    NavDgpsIndex_AgeCh,
    NavDgpsIndex_Prc,
    NavDgpsIndex_Prrc,
    NavDgpsIndex_NumOfValues
};

using NavDgpsDataElement =
    comms::field::Bundle<
        std::tuple<
            field::nav::SVID,
            comms::field::Bitfield<
                field::common::FieldBase,
                std::tuple<
                    field::nav::chnT<comms::option::FixedBitLength<4> >,
                    field::nav::DgpsFlagsT<comms::option::FixedBitLength<4> >
                >
            >,
            field::nav::AGECH,
            field::nav::PRC,
            field::nav::PRRC
        >
    >;

using NavDgpsFields = std::tuple<
    field::nav::ITOW,
    field::nav::AGE,
    field::nav::BASEID,
    field::nav::BASEHLTH,
    field::nav::NCH,
    field::nav::STATUS,
    field::common::res2,
    comms::field::ArrayList<
        field::common::FieldBase,
        NavDgpsDataElement,
        comms::option::SequenceSizeForcingEnabled
    >
>;


template <typename TMsgBase = Message>
class NavDgps : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_DGPS>,
        comms::option::FieldsImpl<NavDgpsFields>,
        comms::option::DispatchImpl<NavDgps<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_DGPS>,
        comms::option::FieldsImpl<NavDgpsFields>,
        comms::option::DispatchImpl<NavDgps<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_Itow,
        FieldIdx_Age,
        FieldIdx_BaseId,
        FieldIdx_BaseHealth,
        FieldIdx_Nch,
        FieldIdx_Status,
        FieldIdx_Res1,
        FieldIdx_Data,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    NavDgps() = default;
    NavDgps(const NavDgps&) = default;
    NavDgps(NavDgps&& other)
    {
    }
    virtual ~NavDgps() = default;

    NavDgps& operator=(const NavDgps&) = default;
    NavDgps& operator=(NavDgps&&) = default;

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
        auto& nchField = std::get<FieldIdx_Nch>(allFields);
        auto& dataField = std::get<FieldIdx_Data>(allFields);
        dataField.forceReadElemCount(nchField.value());

        return Base::template readFieldsFrom<FieldIdx_Data>(iter, len);
    }

    virtual bool validImpl() const override
    {
        if (!Base::validImpl()) {
            return false;
        }

        auto& allFields = Base::fields();
        auto& nchField = std::get<FieldIdx_Nch>(allFields);
        auto& dataField = std::get<FieldIdx_Data>(allFields);
        for (auto& bundleField : dataField.value()) {
            auto& members = bundleField.value();
            auto& flagsField = std::get<NavDgpsIndex_Flags>(members);
            auto& bundle = flagsField.value();
            auto& chNumField = std::get<NavDgpsFlagsIndex_Chn>(bundle);
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
        auto& dataField = std::get<FieldIdx_Data>(allFields);
        if (nchField.value() == dataField.value().size()) {
            return false;
        }

        nchField.value() = dataField.value().size();
        return true;
    }

};

}  // namespace message

}  // namespace ublox





