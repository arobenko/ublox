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

enum class NavDgps_Status : std::uint8_t
{
    None,
    PR_PRR_Correction,
    NumOfValues
};

enum
{
    NavDgpsField_flags_channel,
    NavDgpsField_flags_bits,
    NavDgpsField_flags_numOfValues
};

enum
{
    NavDgpsField_flags_bits_dgpsUsed,
    NavDgpsField_flags_bits_numOfValues
};

enum
{
    NavDpgsField_data_svid,
    NavDgpsField_data_flags,
    NavDgpsField_data_ageC,
    NavDgpsField_data_prc,
    NavDgpsField_data_prrc,
    NavDgpsField_data_numOfValues
};


using NavDgpsField_iTOW = field::nav::iTOW;
using NavDgpsField_age = field::common::I4T<field::common::Scaling_ms2s>;
using NavDgpsField_baseId = field::common::I2;
using NavDgpsField_baseHealth = field::common::I2;
using NavDgpsField_numCh = field::nav::numCh;
using NavDgpsField_status =
    comms::field::EnumValue<
        field::common::FieldBase,
        NavDgps_Status,
        comms::option::ValidNumValueRange<0, (int)NavDgps_Status::NumOfValues - 1>
    >;
using NavDgpsField_reserved1 = field::common::res2;

using NavDgpsField_svid = field::nav::svid;
using NavDgpsField_flags =
    comms::field::Bitfield<
        field::common::FieldBase,
        std::tuple<
            field::common::U1T<
                comms::option::FixedBitLength<4>,
                comms::option::ValidNumValueRange<0, 15>
            >,
            field::common::X1T<
                comms::option::FixedBitLength<4>,
                comms::option::BitmaskReservedBits<0xfe, 0>
            >
        >
    >;

using NavDgpsField_ageC = field::common::U2T<field::common::Scaling_ms2s>;
using NavDgpsField_prc = field::common::R4;
using NavDgpsField_prrc = field::common::R4;

using NavDgpsField_data =
    comms::field::ArrayList<
        field::common::FieldBase,
        comms::field::Bundle<
            std::tuple<
                NavDgpsField_svid,
                NavDgpsField_flags,
                NavDgpsField_ageC,
                NavDgpsField_prc,
                NavDgpsField_prrc
            >
        >,
        comms::option::SequenceSizeForcingEnabled
    >;

using NavDgpsFields = std::tuple<
    NavDgpsField_iTOW,
    NavDgpsField_age,
    NavDgpsField_baseId,
    NavDgpsField_baseHealth,
    NavDgpsField_numCh,
    NavDgpsField_status,
    NavDgpsField_reserved1,
    NavDgpsField_data
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
        FieldIdx_iTOW,
        FieldIdx_age,
        FieldIdx_baseId,
        FieldIdx_baseHealth,
        FieldIdx_numCh,
        FieldIdx_status,
        FieldIdx_reserved1,
        FieldIdx_data,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    NavDgps() = default;
    NavDgps(const NavDgps&) = default;
    NavDgps(NavDgps&& other) = default;
    virtual ~NavDgps() = default;

    NavDgps& operator=(const NavDgps&) = default;
    NavDgps& operator=(NavDgps&&) = default;

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
        auto& numChField = std::get<FieldIdx_numCh>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        dataField.forceReadElemCount(numChField.value());

        return Base::template readFieldsFrom<FieldIdx_data>(iter, len);
    }

    virtual bool refreshImpl() override
    {
        auto& allFields = Base::fields();
        auto& numChField = std::get<FieldIdx_numCh>(allFields);
        auto& dataField = std::get<FieldIdx_data>(allFields);
        if (numChField.value() == dataField.value().size()) {
            return false;
        }

        numChField.value() = dataField.value().size();
        return true;
    }

};

}  // namespace message

}  // namespace ublox





