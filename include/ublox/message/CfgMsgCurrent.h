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

#include "ublox/Message.h"
#include "ublox/field/MsgId.h"
#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

using CfgMsgCurrentField_id = field::MsgId;
using CfgMsgCurrentField_rate = field::cfg::rate;

using CfgMsgCurrentFields =
    std::tuple<
        CfgMsgCurrentField_id,
        CfgMsgCurrentField_rate
    >;


template <typename TMsgBase = Message>
class CfgMsgCurrent : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_MSG>,
        comms::option::FieldsImpl<CfgMsgCurrentFields>,
        comms::option::DispatchImpl<CfgMsgCurrent<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_MSG>,
        comms::option::FieldsImpl<CfgMsgCurrentFields>,
        comms::option::DispatchImpl<CfgMsgCurrent<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_id,
        FieldIdx_rate,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    CfgMsgCurrent() = default;

    /// @brief Copy constructor
    CfgMsgCurrent(const CfgMsgCurrent&) = default;

    /// @brief Move constructor
    CfgMsgCurrent(CfgMsgCurrent&& other) = default;

    /// @brief Destructor
    virtual ~CfgMsgCurrent() = default;

    /// @brief Copy assignment
    CfgMsgCurrent& operator=(const CfgMsgCurrent&) = default;

    /// @brief Move assignment
    CfgMsgCurrent& operator=(CfgMsgCurrent&&) = default;
};


}  // namespace message

}  // namespace ublox

