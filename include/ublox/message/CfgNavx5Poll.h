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

using CfgNavx5PollFields = std::tuple<>;

template <typename TMsgBase = Message>
class CfgNavx5Poll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NAVX5>,
        comms::option::FieldsImpl<CfgNavx5PollFields>,
        comms::option::DispatchImpl<CfgNavx5Poll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NAVX5>,
        comms::option::FieldsImpl<CfgNavx5PollFields>,
        comms::option::DispatchImpl<CfgNavx5Poll<TMsgBase> >
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
    CfgNavx5Poll() = default;

    /// @brief Copy constructor
    CfgNavx5Poll(const CfgNavx5Poll&) = default;

    /// @brief Move constructor
    CfgNavx5Poll(CfgNavx5Poll&& other) = default;

    /// @brief Destructor
    virtual ~CfgNavx5Poll() = default;

    /// @brief Copy assignment
    CfgNavx5Poll& operator=(const CfgNavx5Poll&) = default;

    /// @brief Move assignment
    CfgNavx5Poll& operator=(CfgNavx5Poll&&) = default;
};


}  // namespace message

}  // namespace ublox

