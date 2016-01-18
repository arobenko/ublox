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

#include <iterator>

#include "comms/Message.h"
#include "ublox/Message.h"

namespace ublox
{

namespace message
{

using CfgPrtPollFields = std::tuple<>;

template <typename TMsgBase = Message>
class CfgPrtPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtPollFields>,
        comms::option::DispatchImpl<CfgPrtPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_PRT>,
        comms::option::FieldsImpl<CfgPrtPollFields>,
        comms::option::DispatchImpl<CfgPrtPoll<TMsgBase> >
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
    CfgPrtPoll() = default;

    /// @brief Copy constructor
    CfgPrtPoll(const CfgPrtPoll&) = default;

    /// @brief Move constructor
    CfgPrtPoll(CfgPrtPoll&& other) = default;

    /// @brief Destructor
    virtual ~CfgPrtPoll() = default;

    /// @brief Copy assignment
    CfgPrtPoll& operator=(const CfgPrtPoll&) = default;

    /// @brief Move assignment
    CfgPrtPoll& operator=(CfgPrtPoll&&) = default;

};


}  // namespace message

}  // namespace ublox





