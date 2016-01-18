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

enum
{
    RxmRawField_data_cpMes,
    RxmRawField_data_prMes,
    RxmRawField_data_doMes,
    RxmRawField_data_sv,
    RxmRawField_data_mesQI,
    RxmRawField_data_cno,
    RxmRawField_data_lli,
    RxmRawField_data_numOfValues
};

using RxmRawField_rcvTow = field::common::I4T<field::common::Scaling_ms2s>;
using RxmRawField_week = field::rxm::week;
using RxmRawField_numSV = field::rxm::numSV;
using RxmRawField_reserved1 = field::common::res1;

using RxmRawField_cpMes = field::common::R8;
using RxmRawField_prMes = field::common::R8;
using RxmRawField_doMes = field::common::R4;
using RxmRawField_sv = field::common::U1;
using RxmRawField_mesQI = field::common::I1;
using RxmRawField_cno = field::common::I1;
using RxmRawField_lli = field::common::U1;

using RxmRawField_data =
    field::common::ListT<
        comms::field::Bundle<
            std::tuple<
                RxmRawField_cpMes,
                RxmRawField_prMes,
                RxmRawField_doMes,
                RxmRawField_sv,
                RxmRawField_mesQI,
                RxmRawField_cno,
                RxmRawField_lli
            >
        >,
        comms::option::SequenceSizeForcingEnabled
    >;

using RxmRawFields = std::tuple<
    RxmRawField_rcvTow,
    RxmRawField_week,
    RxmRawField_numSV,
    RxmRawField_reserved1,
    RxmRawField_data
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
        FieldIdx_rcvTow,
        FieldIdx_week,
        FieldIdx_numSV,
        FieldIdx_reserved1,
        FieldIdx_data,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    RxmRaw() = default;
    RxmRaw(const RxmRaw&) = default;
    RxmRaw(RxmRaw&& other) = default;
    virtual ~RxmRaw() = default;

    RxmRaw& operator=(const RxmRaw&) = default;
    RxmRaw& operator=(RxmRaw&&) = default;

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
        auto& numSvField = std::get<FieldIdx_numSV>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        dataField.forceReadElemCount(numSvField.value());

        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& numSvField = std::get<FieldIdx_numSV>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        if (numSvField.value() == dataField.value().size()) {
            return false;
        }

        numSvField.value() = dataField.value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox





