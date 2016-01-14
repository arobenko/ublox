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

/// @brief Definition of the fields for ACK-ACK message.
/// @see AckAck
using AckAckFields = std::tuple<
    ublox::field::MsgId
>;

/// @brief Definition of ACK-ACK message
/// @details Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref AckAckFields for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AckAck : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_ACK_ACK>,
        comms::option::FieldsImpl<AckAckFields>,
        comms::option::DispatchImpl<AckAck<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_ACK_ACK>,
        comms::option::FieldsImpl<AckAckFields>,
        comms::option::DispatchImpl<AckAck<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_id, ///< id field
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    AckAck() = default;

    /// @brief Copy constructor
    AckAck(const AckAck&) = default;

    /// @brief Move constructor
    AckAck(AckAck&& other) = default;

    /// @brief Destructor
    virtual ~AckAck() = default;

    /// @brief Copy assignment
    AckAck& operator=(const AckAck&) = default;

    /// @brief Move assignment
    AckAck& operator=(AckAck&&) = default;
};


}  // namespace message

}  // namespace ublox

