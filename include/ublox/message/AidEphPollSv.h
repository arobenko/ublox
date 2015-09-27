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

#include "ublox/field/aid.h"

namespace ublox
{

namespace message
{

using AidEphPollSvField_svid = field::aid::svid;

using AidEphPollSvFields = std::tuple<
    AidEphPollSvField_svid
>;


template <typename TMsgBase = Message>
class AidEphPollSv : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_EPH>,
        comms::option::FieldsImpl<AidEphPollSvFields>,
        comms::option::DispatchImpl<AidEphPollSv<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_EPH>,
        comms::option::FieldsImpl<AidEphPollSvFields>,
        comms::option::DispatchImpl<AidEphPollSv<TMsgBase> >
    > Base;
public:

    enum FieldIdx
    {
        FieldIdx_svid,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");


    AidEphPollSv() = default;
    AidEphPollSv(const AidEphPollSv&) = default;
    AidEphPollSv(AidEphPollSv&& other) = default;
    virtual ~AidEphPollSv() = default;

    AidEphPollSv& operator=(const AidEphPollSv&) = default;
    AidEphPollSv& operator=(AidEphPollSv&&) = default;
};


}  // namespace message

}  // namespace ublox





