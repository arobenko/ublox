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

using AidReqFields = std::tuple<>;


template <typename TMsgBase = Message>
class AidReq : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_REQ>,
        comms::option::FieldsImpl<AidReqFields>,
        comms::option::DispatchImpl<AidReq<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_REQ>,
        comms::option::FieldsImpl<AidReqFields>,
        comms::option::DispatchImpl<AidReq<TMsgBase> >
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
    AidReq() = default;

    /// @brief Copy constructor
    AidReq(const AidReq&) = default;

    /// @brief Move constructor
    AidReq(AidReq&& other) = default;

    /// @brief Destructor
    virtual ~AidReq() = default;

    /// @brief Copy assignment
    AidReq& operator=(const AidReq&) = default;

    /// @brief Move assignment
    AidReq& operator=(AidReq&&) = default;
};


}  // namespace message

}  // namespace ublox

