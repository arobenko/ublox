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

using NavPosllhFields = std::tuple<
    field::nav::ITOW,
    field::nav::LON,
    field::nav::LAT,
    field::nav::HEIGHT,
    field::nav::HMSL,
    field::nav::Hacc,
    field::nav::Vacc
>;


template <typename TMsgBase = Message>
class NavPosllh : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_POSLLH>,
        comms::option::FieldsImpl<NavPosllhFields>,
        comms::option::DispatchImpl<NavPosllh<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_POSLLH>,
        comms::option::FieldsImpl<NavPosllhFields>,
        comms::option::DispatchImpl<NavPosllh<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_Itow,
        FieldIdx_Lon,
        FieldIdx_Lat,
        FieldIdx_Heght,
        FieldIdx_HeghtMeanSeaLevel,
        FieldIdx_Hacc,
        FieldIdx_Vacc,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    NavPosllh() = default;
    NavPosllh(const NavPosllh&) = default;
    NavPosllh(NavPosllh&& other)
    {
    }
    virtual ~NavPosllh() = default;

    NavPosllh& operator=(const NavPosllh&) = default;
    NavPosllh& operator=(NavPosllh&&) = default;
};


}  // namespace message

}  // namespace ublox





