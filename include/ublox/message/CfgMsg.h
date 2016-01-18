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

using CfgMsgField_id = ublox::field::MsgId;
using CfgMsgField_rate =
    field::common::ListT<
        field::cfg::rate,
        comms::option::SequenceFixedSize<6>
    >;

using CfgMsgFields = std::tuple<
    CfgMsgField_id,
    CfgMsgField_rate
>;


template <typename TMsgBase = Message>
class CfgMsg : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_MSG>,
        comms::option::FieldsImpl<CfgMsgFields>,
        comms::option::DispatchImpl<CfgMsg<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_MSG>,
        comms::option::FieldsImpl<CfgMsgFields>,
        comms::option::DispatchImpl<CfgMsg<TMsgBase> >
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
    CfgMsg() = default;

    /// @brief Copy constructor
    CfgMsg(const CfgMsg&) = default;

    /// @brief Move constructor
    CfgMsg(CfgMsg&& other) = default;

    /// @brief Destructor
    virtual ~CfgMsg() = default;

    /// @brief Copy assignment
    CfgMsg& operator=(const CfgMsg&) = default;

    /// @brief Move assignment
    CfgMsg& operator=(CfgMsg&&) = default;
};


}  // namespace message

}  // namespace ublox

