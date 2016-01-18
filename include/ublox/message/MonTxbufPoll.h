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

namespace ublox
{

namespace message
{

using MonTxbufPollFields = std::tuple<>;


template <typename TMsgBase = Message>
class MonTxbufPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_TXBUF>,
        comms::option::FieldsImpl<MonTxbufPollFields>,
        comms::option::DispatchImpl<MonTxbufPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_TXBUF>,
        comms::option::FieldsImpl<MonTxbufPollFields>,
        comms::option::DispatchImpl<MonTxbufPoll<TMsgBase> >
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
    MonTxbufPoll() = default;

    /// @brief Copy constructor
    MonTxbufPoll(const MonTxbufPoll&) = default;

    /// @brief Move constructor
    MonTxbufPoll(MonTxbufPoll&& other) = default;

    /// @brief Destructor
    virtual ~MonTxbufPoll() = default;

    /// @brief Copy assignment
    MonTxbufPoll& operator=(const MonTxbufPoll&) = default;

    /// @brief Move assignment
    MonTxbufPoll& operator=(MonTxbufPoll&&) = default;
};


}  // namespace message

}  // namespace ublox

