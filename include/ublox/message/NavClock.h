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

using NavClockField_iTOW = field::nav::iTOW;
using NavClockField_clkB = field::common::I4T<field::common::Scaling_ns2s>;
using NavClockField_clkD = field::common::I4T<field::common::Scaling_ns2s>;
using NavClockField_tAcc = field::nav::tAcc;
using NavClockField_fAcc = field::common::U4;

using NavClockFields = std::tuple<
    NavClockField_iTOW,
    NavClockField_clkB,
    NavClockField_clkD,
    NavClockField_tAcc,
    NavClockField_fAcc
>;


template <typename TMsgBase = Message>
class NavClock : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_CLOCK>,
        comms::option::FieldsImpl<NavClockFields>,
        comms::option::DispatchImpl<NavClock<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_CLOCK>,
        comms::option::FieldsImpl<NavClockFields>,
        comms::option::DispatchImpl<NavClock<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_iTOW,
        FieldIdx_clkB,
        FieldIdx_clkD,
        FieldIdx_tAcc,
        FieldIdx_fAcc,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    NavClock() = default;
    NavClock(const NavClock&) = default;
    NavClock(NavClock&& other) = default;
    virtual ~NavClock() = default;

    NavClock& operator=(const NavClock&) = default;
    NavClock& operator=(NavClock&&) = default;
};


}  // namespace message

}  // namespace ublox





