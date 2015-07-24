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

enum RxmRawIndex
{
    RxmRawIndex_CPMes,
    RxmRawIndex_PRMes,
    RxmRawIndex_DOMes,
    RxmRawIndex_Sv,
    RxmRawIndex_MesQI,
    RxmRawIndex_Cno,
    RxmRawIndex_Lli,
    RxmRawIndex_NumOfValues
};

using RxmRawElement =
    comms::field::Bundle<
        std::tuple<
            field::rxm::CPMes,
            field::rxm::PRMes,
            field::rxm::DOMes,
            field::rxm::SV,
            field::rxm::MesQI,
            field::rxm::CNO,
            field::rxm::LLI
        >
    >;

using RxmRawFields = std::tuple<
    field::rxm::ITOW,
    field::rxm::Week,
    field::rxm::NSV,
    field::common::res1,
    comms::field::ArrayList<
        field::common::FieldBase,
        RxmRawElement,
        comms::option::SequenceSizeForcingEnabled
    >
>;

template <typename TMsgBase = Message>
class RxmRaw : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_RAW>,
        comms::option::FieldsImpl<RxmRawFields>,
        comms::option::DispatchImpl<RxmRaw<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_RAW>,
        comms::option::FieldsImpl<RxmRawFields>,
        comms::option::DispatchImpl<RxmRaw<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_Itow,
        FieldIdx_Week,
        FieldIdx_Nsv,
        FieldIdx_Res,
        FieldIdx_Data,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    RxmRaw() = default;
    RxmRaw(const RxmRaw&) = default;
    RxmRaw(RxmRaw&& other)
    {
    }
    virtual ~RxmRaw() = default;

    RxmRaw& operator=(const RxmRaw&) = default;
    RxmRaw& operator=(RxmRaw&&) = default;

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
        auto& nsvField = std::get<FieldIdx_Nsv>(allFields);
        auto& dataField = std::get<FieldIdx_Data>(allFields);
        dataField.forceReadElemCount(nsvField.value());

        return Base::template readFieldsFrom<FieldIdx_Data>(iter, len);
    }

    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& nsvField = std::get<FieldIdx_Nsv>(allFields);
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





