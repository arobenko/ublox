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

using NavDopFields = std::tuple<
    field::nav::ITOW,
    field::nav::GDOP,
    field::nav::PDOP,
    field::nav::TDOP,
    field::nav::VDOP,
    field::nav::HDOP,
    field::nav::NDOP,
    field::nav::EDOP
>;


template <typename TMsgBase = Message>
class NavDop : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_DOP>,
        comms::option::FieldsImpl<NavDopFields>,
        comms::option::DispatchImpl<NavDop<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_DOP>,
        comms::option::FieldsImpl<NavDopFields>,
        comms::option::DispatchImpl<NavDop<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_Itow,
        FieldIdx_Gdop,
        FieldIdx_Pdop,
        FieldIdx_Tdop,
        FieldIdx_Vdop,
        FieldIdx_Hdop,
        FieldIdx_Ndop,
        FieldIdx_Edop,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    NavDop() = default;
    NavDop(const NavDop&) = default;
    NavDop(NavDop&& other)
    {
    }
    virtual ~NavDop() = default;

    NavDop& operator=(const NavDop&) = default;
    NavDop& operator=(NavDop&&) = default;
};


}  // namespace message

}  // namespace ublox





