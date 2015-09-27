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

using AidAlmPollSv_svid = field::aid::svid;

using AidAlmPollSvFields = std::tuple<
    AidAlmPollSv_svid
>;


template <typename TMsgBase = Message>
class AidAlmPollSv : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALM>,
        comms::option::FieldsImpl<AidAlmPollSvFields>,
        comms::option::DispatchImpl<AidAlmPollSv<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALM>,
        comms::option::FieldsImpl<AidAlmPollSvFields>,
        comms::option::DispatchImpl<AidAlmPollSv<TMsgBase> >
    > Base;
public:

    enum FieldIdx
    {
        FieldIdx_svid,
        FieldIdx_numOfValues
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");


    AidAlmPollSv() = default;
    AidAlmPollSv(const AidAlmPollSv&) = default;
    AidAlmPollSv(AidAlmPollSv&& other) = default;
    virtual ~AidAlmPollSv() = default;

    AidAlmPollSv& operator=(const AidAlmPollSv&) = default;
    AidAlmPollSv& operator=(AidAlmPollSv&&) = default;
};


}  // namespace message

}  // namespace ublox





