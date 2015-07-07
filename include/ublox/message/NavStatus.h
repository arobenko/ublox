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

using NavStatusFields = std::tuple<
    field::nav::ITOW,
    field::nav::GPSfix,
    field::nav::Flags,
    field::nav::DiffS,
    field::common::res1,
    field::nav::TTFF,
    field::nav::MSSS
>;


template <typename TMsgBase = Message>
class NavStatus : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_STATUS>,
        comms::option::FieldsImpl<NavStatusFields>,
        comms::option::DispatchImpl<NavStatus<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_STATUS>,
        comms::option::FieldsImpl<NavStatusFields>,
        comms::option::DispatchImpl<NavStatus<TMsgBase> >
    > Base;
public:
    enum FieldIdx
    {
        FieldIdx_Itow,
        FieldIdx_GpsFix,
        FieldIdx_Flags,
        FieldIdx_DiffS,
        FieldIdx_Res,
        FieldIdx_Ttff,
        FieldIdx_Msss,
        FieldIdx_NumOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_NumOfValues,
        "Number of fields is incorrect");

    NavStatus() = default;
    NavStatus(const NavStatus&) = default;
    NavStatus(NavStatus&& other)
    {
    }
    virtual ~NavStatus() = default;

    NavStatus& operator=(const NavStatus&) = default;
    NavStatus& operator=(NavStatus&&) = default;
};


}  // namespace message

}  // namespace ublox





