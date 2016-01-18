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
#include "ublox/field/MsgId.h"

namespace ublox
{

namespace message
{

using CfgRxmPollFields = std::tuple<>;

template <typename TMsgBase = Message>
class CfgRxmPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RXM>,
        comms::option::FieldsImpl<CfgRxmPollFields>,
        comms::option::DispatchImpl<CfgRxmPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_RXM>,
        comms::option::FieldsImpl<CfgRxmPollFields>,
        comms::option::DispatchImpl<CfgRxmPoll<TMsgBase> >
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
    CfgRxmPoll() = default;

    /// @brief Copy constructor
    CfgRxmPoll(const CfgRxmPoll&) = default;

    /// @brief Move constructor
    CfgRxmPoll(CfgRxmPoll&& other) = default;

    /// @brief Destructor
    virtual ~CfgRxmPoll() = default;

    /// @brief Copy assignment
    CfgRxmPoll& operator=(const CfgRxmPoll&) = default;

    /// @brief Move assignment
    CfgRxmPoll& operator=(CfgRxmPoll&&) = default;
};


}  // namespace message

}  // namespace ublox

