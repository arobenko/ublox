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

using NavSbasPollFields = std::tuple<>;


template <typename TMsgBase = Message>
class NavSbasPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SBAS>,
        comms::option::FieldsImpl<NavSbasPollFields>,
        comms::option::DispatchImpl<NavSbasPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_SBAS>,
        comms::option::FieldsImpl<NavSbasPollFields>,
        comms::option::DispatchImpl<NavSbasPoll<TMsgBase> >
    > Base;
public:

    static_assert(std::tuple_size<typename Base::AllFields>::value == 0U,
        "Number of fields is incorrect");

    NavSbasPoll() = default;
    NavSbasPoll(const NavSbasPoll&) = default;
    NavSbasPoll(NavSbasPoll&& other) = default;
    virtual ~NavSbasPoll() = default;

    NavSbasPoll& operator=(const NavSbasPoll&) = default;
    NavSbasPoll& operator=(NavSbasPoll&&) = default;
};


}  // namespace message

}  // namespace ublox





