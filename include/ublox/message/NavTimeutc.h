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

using NavTimeutcFields = std::tuple<
    field::nav::ITOW,
    field::nav::Tacc,
    field::nav::Nano,
    field::nav::Year,
    field::nav::Month,
    field::nav::Day,
    field::nav::Hour,
    field::nav::Min,
    field::nav::Sec,
    field::nav::TimeValid
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
        FieldIdx_Itow,
        FieldIdx_Tacc,
        FieldIdx_Nano,
        FieldIdx_Year,
        FieldIdx_Month,
        FieldIdx_Day,
        FieldIdx_Hour,
        FieldIdx_Min,
        FieldIdx_Sec,
        FieldIdx_Valid,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
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





