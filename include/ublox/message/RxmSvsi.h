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

#include "ublox/field/rxm.h"

namespace ublox
{

namespace message
{

enum RxmSvsiIndex
{
    RxmSvsiIndex_Svsi,
    RxmSvsiIndex_SVFlag,
    RxmSvsiIndex_Azim,
    RxmSvsiIndex_Elev,
    RxmSvsiIndex_Age,
    RxmSvsiIndex_NumOfValues
};

using RxmSvsiElement =
    comms::field::Bundle<
        std::tuple<
            field::rxm::SVID,
            field::rxm::StatusInfoSvFlag,
            field::rxm::Azim,
            field::rxm::Elev,
            field::rxm::Age
        >
    >;

using RxmSvsiFields = std::tuple<
    field::rxm::ITOW,
    field::rxm::Week,
    field::rxm::NumVis,
    field::rxm::NumSv,
    comms::field::ArrayList<
        field::common::FieldBase,
        RxmSvsiElement,
        comms::option::SequenceSizeForcingEnabled
    >
>;

template <typename TMsgBase = Message>
class RxmSvsi : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_SVSI>,
        comms::option::FieldsImpl<RxmSvsiFields>,
        comms::option::DispatchImpl<RxmSvsi<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_SVSI>,
        comms::option::FieldsImpl<RxmSvsiFields>,
        comms::option::DispatchImpl<RxmSvsi<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_Itow,
        FieldIdx_Week,
        FieldIdx_NumVis,
        FieldIdx_NumSv,
        FieldIdx_Data,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    RxmSvsi() = default;
    RxmSvsi(const RxmSvsi&) = default;
    RxmSvsi(RxmSvsi&& other)
    {
    }
    virtual ~RxmSvsi() = default;

    RxmSvsi& operator=(const RxmSvsi&) = default;
    RxmSvsi& operator=(RxmSvsi&&) = default;

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
        auto& nsvField = std::get<FieldIdx_NumSv>(allFields);
        auto& dataField = std::get<FieldIdx_Data>(allFields);
        dataField.forceReadElemCount(nsvField.value());

        return Base::template readFieldsFrom<FieldIdx_Data>(iter, len);
    }

    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& nsvField = std::get<FieldIdx_NumSv>(allFields);
        auto& dataField = std::get<FieldIdx_Data>(allFields);
        if (nsvField.value() == dataField.value().size()) {
            return false;
        }

        nsvField.value() = dataField.value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





