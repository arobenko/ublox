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

using NavPosecefField_iTOW = field::nav::iTOW;
using NavPosecefField_ecefX = field::nav::ecefX;
using NavPosecefField_ecefY = field::nav::ecefY;
using NavPosecefField_ecefZ = field::nav::ecefZ;
using NavPosecefField_pAcc = field::nav::pAcc;

using NavPosecefFields = std::tuple<
    NavPosecefField_iTOW,
    NavPosecefField_ecefX,
    NavPosecefField_ecefY,
    NavPosecefField_ecefZ,
    field::nav::Pacc
>;


template <typename TMsgBase = Message>
class NavPosecef : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_POSECEF>,
        comms::option::FieldsImpl<NavPosecefFields>,
        comms::option::DispatchImpl<NavPosecef<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_POSECEF>,
        comms::option::FieldsImpl<NavPosecefFields>,
        comms::option::DispatchImpl<NavPosecef<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_iTow,
        FieldIdx_ecefX,
        FieldIdx_ecefY,
        FieldIdx_ecefZ,
        FieldIdx_pAcc,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    NavPosecef() = default;
    NavPosecef(const NavPosecef&) = default;
    NavPosecef(NavPosecef&& other) = default;
    virtual ~NavPosecef() = default;

    NavPosecef& operator=(const NavPosecef&) = default;
    NavPosecef& operator=(NavPosecef&&) = default;
};


}  // namespace message

}  // namespace ublox





