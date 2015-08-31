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
    NavAopstatusField_aopCfg_useAOP,
    NavAopstatusField_aopCfg_numOfValues
};


using NavAopstatusField_iTOW = field::nav::iTOW;
using NavAopstatusField_aopCfg =
    field::common::X1T<comms::option::BitmaskReservedBits<0xfe, 0> >;
using NavAopstatusField_status = field::common::U1;
using NavAopstatusField_reserved0 = field::common::res1;
using NavAopstatusField_reserved1 = field::common::res1;
using NavAopstatusField_availGPS = field::common::X4;
using NavAopstatusField_reserved2 = field::common::res4;
using NavAopstatusField_reserved3 = field::common::res4;

using NavAopstatusFields = std::tuple<
    NavAopstatusField_iTOW,
    NavAopstatusField_aopCfg,
    NavAopstatusField_status,
    NavAopstatusField_reserved0,
    NavAopstatusField_reserved1,
    NavAopstatusField_availGPS,
    NavAopstatusField_reserved2,
    NavAopstatusField_reserved3
>;


template <typename TMsgBase = Message>
class NavAopstatus : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_AOPSTATUS>,
        comms::option::FieldsImpl<NavAopstatusFields>,
        comms::option::DispatchImpl<NavAopstatus<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_AOPSTATUS>,
        comms::option::FieldsImpl<NavAopstatusFields>,
        comms::option::DispatchImpl<NavAopstatus<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_iTOW,
        FieldIdx_aopCfg,
        FieldIdx_status,
        FieldIdx_reserved0,
        FieldIdx_reserved1,
        FieldIdx_availGPS,
        FieldIdx_reserved2,
        FieldIdx_reserved3,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    NavAopstatus() = default;
    NavAopstatus(const NavAopstatus&) = default;
    NavAopstatus(NavAopstatus&& other) = default;
    virtual ~NavAopstatus() = default;

    NavAopstatus& operator=(const NavAopstatus&) = default;
    NavAopstatus& operator=(NavAopstatus&&) = default;
};


}  // namespace message

}  // namespace ublox





