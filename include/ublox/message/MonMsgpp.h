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
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

using CfgMsgppField_msg1 =
    field::common::ListT<
        field::common::U2,
        comms::option::SequenceFixedSize<8>
    >;
using CfgMsgppField_msg2 = CfgMsgppField_msg1;
using CfgMsgppField_msg3 = CfgMsgppField_msg1;
using CfgMsgppField_msg4 = CfgMsgppField_msg1;
using CfgMsgppField_msg5 = CfgMsgppField_msg1;
using CfgMsgppField_msg6 = CfgMsgppField_msg1;
using CfgMsgppField_skipped =
    field::common::ListT<
        field::common::U4,
        comms::option::SequenceFixedSize<6>
    >;

using MonMsgppFields = std::tuple<
    CfgMsgppField_msg1,
    CfgMsgppField_msg2,
    CfgMsgppField_msg3,
    CfgMsgppField_msg4,
    CfgMsgppField_msg5,
    CfgMsgppField_msg6,
    CfgMsgppField_skipped
>;


template <typename TMsgBase = Message>
class MonMsgpp : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_MSGPP>,
        comms::option::FieldsImpl<MonMsgppFields>,
        comms::option::DispatchImpl<MonMsgpp<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MON_MSGPP>,
        comms::option::FieldsImpl<MonMsgppFields>,
        comms::option::DispatchImpl<MonMsgpp<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_msg1,
        FieldIdx_msg2,
        FieldIdx_msg3,
        FieldIdx_msg4,
        FieldIdx_msg5,
        FieldIdx_msg6,
        FieldIdx_skipped,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    MonMsgpp() = default;

    /// @brief Copy constructor
    MonMsgpp(const MonMsgpp&) = default;

    /// @brief Move constructor
    MonMsgpp(MonMsgpp&& other) = default;

    /// @brief Destructor
    virtual ~MonMsgpp() = default;

    /// @brief Copy assignment
    MonMsgpp& operator=(const MonMsgpp&) = default;

    /// @brief Move assignment
    MonMsgpp& operator=(MonMsgpp&&) = default;
};


}  // namespace message

}  // namespace ublox

