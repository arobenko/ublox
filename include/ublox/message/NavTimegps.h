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

using NavTimegpsFields = std::tuple<
    field::nav::ITOW,
    field::nav::Frac,
    field::nav::week,
    field::nav::LeapS,
    field::nav::TimeValid,
    field::nav::Tacc
>;


template <typename TMsgBase = Message>
class NavTimegps : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMEGPS>,
        comms::option::FieldsImpl<NavTimegpsFields>,
        comms::option::DispatchImpl<NavTimegps<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMEGPS>,
        comms::option::FieldsImpl<NavTimegpsFields>,
        comms::option::DispatchImpl<NavTimegps<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_Itow,
        FieldIdx_Frac,
        FieldIdx_Week,
        FieldIdx_LeapS,
        FieldIdx_Valid,
        FieldIdx_Tacc,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    NavTimegps() = default;
    NavTimegps(const NavTimegps&) = default;
    NavTimegps(NavTimegps&& other)
    {
    }
    virtual ~NavTimegps() = default;

    NavTimegps& operator=(const NavTimegps&) = default;
    NavTimegps& operator=(NavTimegps&&) = default;
};


}  // namespace message

}  // namespace ublox





