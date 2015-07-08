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

using NavVelecefFields = std::tuple<
    field::nav::ITOW,
    field::nav::ECEFVX,
    field::nav::ECEFVY,
    field::nav::ECEFVZ,
    field::nav::Sacc
>;


template <typename TMsgBase = Message>
class NavVelecef : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_VELECEF>,
        comms::option::FieldsImpl<NavVelecefFields>,
        comms::option::DispatchImpl<NavVelecef<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_VELECEF>,
        comms::option::FieldsImpl<NavVelecefFields>,
        comms::option::DispatchImpl<NavVelecef<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_Itow,
        FieldIdx_EcefVX,
        FieldIdx_EcefVY,
        FieldIdx_EcefVZ,
        FieldIdx_Sacc,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    NavVelecef() = default;
    NavVelecef(const NavVelecef&) = default;
    NavVelecef(NavVelecef&& other)
    {
    }
    virtual ~NavVelecef() = default;

    NavVelecef& operator=(const NavVelecef&) = default;
    NavVelecef& operator=(NavVelecef&&) = default;
};


}  // namespace message

}  // namespace ublox





