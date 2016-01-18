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

using NavTimeutcPollFields = std::tuple<>;


template <typename TMsgBase = Message>
class NavTimeutcPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMEUTC>,
        comms::option::FieldsImpl<NavTimeutcPollFields>,
        comms::option::DispatchImpl<NavTimeutcPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMEUTC>,
        comms::option::FieldsImpl<NavTimeutcPollFields>,
        comms::option::DispatchImpl<NavTimeutcPoll<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    NavTimeutcPoll() = default;

    /// @brief Copy constructor
    NavTimeutcPoll(const NavTimeutcPoll&) = default;

    /// @brief Move constructor
    NavTimeutcPoll(NavTimeutcPoll&& other) = default;

    /// @brief Destructor
    virtual ~NavTimeutcPoll() = default;

    /// @brief Copy assignment
    NavTimeutcPoll& operator=(const NavTimeutcPoll&) = default;

    /// @brief Move assignment
    NavTimeutcPoll& operator=(NavTimeutcPoll&&) = default;
};


}  // namespace message

}  // namespace ublox





