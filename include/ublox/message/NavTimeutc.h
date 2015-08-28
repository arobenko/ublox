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

#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

enum
{
    NavTimeutcField_valid_validTOW,
    NavTimeutcField_valid_validWKN,
    NavTimeutcField_valid_validUTC,
    NavTimeutcField_valid_numOfValues
};

using NavTimeutcField_iTOW = field::nav::iTOW;
using NavTimeutcField_tAcc = field::nav::tAcc;
using NavTimeutcField_nano = field::nav::nano;
using NavTimeutcField_year = field::nav::year;
using NavTimeutcField_month = field::nav::month;
using NavTimeutcField_day = field::nav::day;
using NavTimeutcField_hour = field::nav::hour;
using NavTimeutcField_min = field::nav::min;
using NavTimeutcField_sec = field::nav::sec;
using NavTimeutcField_valid = field::common::X1T<comms::option::BitmaskReservedBits<0xf8, 0> >;

using NavTimeutcFields = std::tuple<
    NavTimeutcField_iTOW,
    NavTimeutcField_tAcc,
    NavTimeutcField_nano,
    NavTimeutcField_year,
    NavTimeutcField_month,
    NavTimeutcField_day,
    NavTimeutcField_hour,
    NavTimeutcField_min,
    NavTimeutcField_sec,
    NavTimeutcField_valid
>;

template <typename TMsgBase = Message>
class NavTimeutc : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMEUTC>,
        comms::option::FieldsImpl<NavTimeutcFields>,
        comms::option::DispatchImpl<NavTimeutc<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMEUTC>,
        comms::option::FieldsImpl<NavTimeutcFields>,
        comms::option::DispatchImpl<NavTimeutc<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_iTOW,
        FieldIdx_tAcc,
        FieldIdx_nano,
        FieldIdx_year,
        FieldIdx_month,
        FieldIdx_day,
        FieldIdx_hour,
        FieldIdx_min,
        FieldIdx_sec,
        FieldIdx_valid,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    NavTimeutc() = default;
    NavTimeutc(const NavTimeutc&) = default;
    NavTimeutc(NavTimeutc&& other) = default;
    virtual ~NavTimeutc() = default;

    NavTimeutc& operator=(const NavTimeutc&) = default;
    NavTimeutc& operator=(NavTimeutc&&) = default;
};


}  // namespace message

}  // namespace ublox





