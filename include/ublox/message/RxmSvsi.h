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

#include "ublox/field/rxm.h"

namespace ublox
{

namespace message
{

enum
{
    RxmSvsiField_svFlag_ura,
    RxmSvsiField_svFlag_flags,
    RxmSvsiField_svFlag_numOfValues
};

enum
{
    RxmSvsiField_data_svid,
    RxmSvsiField_data_svFlag,
    RxmSvsiField_data_azim,
    RxmSvsiField_data_elev,
    RxmSvsiField_data_age,
    RxmSvsiField_data_numOfValues
};

enum
{
    RxmSvsiField_svFlag_flags_healthy,
    RxmSvsiField_svFlag_flags_ephVal,
    RxmSvsiField_svFlag_flags_almVal,
    RxmSvsiField_svFlag_flags_notAvail,
    RxmSvsiField_svFlag_flags_numOfValues
};

enum
{
    RxmSvsiField_data_age_almAge,
    RxmSvsiField_data_age_ephAge,
    RxmSvsiField_data_age_numOfValues
};

using RxmSvsiField_iTOW = field::rxm::iTOW;
using RxmSvsiField_week = field::rxm::week;
using RxmSvsiField_numVis = field::common::U1;
using RxmSvsiField_numSV = field::rxm::numSV;

using RxmSvsiField_svid = field::rxm::svid;
using RxmSvsiField_svFlag =
    comms::field::Bitfield<
        field::common::FieldBase,
        std::tuple<
            field::common::U1T<
                comms::option::ValidNumValueRange<0, 15>,
                comms::option::FixedBitLength<4>
            >,
            field::common::X1T<
                comms::option::FixedBitLength<4>
            >
        >
    >;
using RxmSvsiField_azim = field::common::I2;
using RxmSvsiField_elev = field::common::I1;
using RxmSvsiField_age =
    comms::field::Bitfield<
        field::common::FieldBase,
        std::tuple<
            field::common::U1T<
                comms::option::FixedBitLength<4>,
                comms::option::ValidNumValueRange<0, 15>
            >,
            field::common::U1T<
                comms::option::FixedBitLength<4>,
                comms::option::ValidNumValueRange<0, 15>
            >
        >
    >;

using RxmSvsiField_data =
    field::common::ListT<
        comms::field::Bundle<
            std::tuple<
                RxmSvsiField_svid,
                RxmSvsiField_svFlag,
                RxmSvsiField_azim,
                RxmSvsiField_elev,
                RxmSvsiField_age
            >
        >,
        comms::option::SequenceSizeForcingEnabled
    >;


using RxmSvsiFields = std::tuple<
    RxmSvsiField_iTOW,
    RxmSvsiField_week,
    RxmSvsiField_numVis,
    RxmSvsiField_numSV,
    RxmSvsiField_data
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
        FieldIdx_iTOW,
        FieldIdx_week,
        FieldIdx_numVis,
        FieldIdx_numSV,
        FieldIdx_data,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    RxmSvsi() = default;
    RxmSvsi(const RxmSvsi&) = default;
    RxmSvsi(RxmSvsi&& other) = default;
    virtual ~RxmSvsi() = default;

    RxmSvsi& operator=(const RxmSvsi&) = default;
    RxmSvsi& operator=(RxmSvsi&&) = default;

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





