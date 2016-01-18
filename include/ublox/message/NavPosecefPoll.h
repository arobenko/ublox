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

using NavPosecefPollFields = std::tuple<>;


template <typename TMsgBase = Message>
class NavPosecefPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_POSECEF>,
        comms::option::FieldsImpl<NavPosecefPollFields>,
        comms::option::DispatchImpl<NavPosecefPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_POSECEF>,
        comms::option::FieldsImpl<NavPosecefPollFields>,
        comms::option::DispatchImpl<NavPosecefPoll<TMsgBase> >
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
    NavPosecefPoll() = default;

    /// @brief Copy constructor
    NavPosecefPoll(const NavPosecefPoll&) = default;

    /// @brief Move constructor
    NavPosecefPoll(NavPosecefPoll&& other) = default;

    /// @brief Destructor
    virtual ~NavPosecefPoll() = default;

    /// @brief Copy assignment
    NavPosecefPoll& operator=(const NavPosecefPoll&) = default;

    /// @brief Move assignment
    NavPosecefPoll& operator=(NavPosecefPoll&&) = default;
};


}  // namespace message

}  // namespace ublox





