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

#include "ublox/field/rxm.h"

namespace ublox
{

namespace message
{

using RxmAlmPollSv_svid = field::rxm::svid;

using RxmAlmPollSvFields = std::tuple<
    RxmAlmPollSv_svid
>;


template <typename TMsgBase = Message>
class RxmAlmPollSv : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_ALM>,
        comms::option::FieldsImpl<RxmAlmPollSvFields>,
        comms::option::DispatchImpl<RxmAlmPollSv<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_ALM>,
        comms::option::FieldsImpl<RxmAlmPollSvFields>,
        comms::option::DispatchImpl<RxmAlmPollSv<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_svid,
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    RxmAlmPollSv() = default;

    /// @brief Copy constructor
    RxmAlmPollSv(const RxmAlmPollSv&) = default;

    /// @brief Move constructor
    RxmAlmPollSv(RxmAlmPollSv&& other) = default;

    /// @brief Destructor
    virtual ~RxmAlmPollSv() = default;

    /// @brief Copy assignment
    RxmAlmPollSv& operator=(const RxmAlmPollSv&) = default;

    /// @brief Move assignment
    RxmAlmPollSv& operator=(RxmAlmPollSv&&) = default;
};


}  // namespace message

}  // namespace ublox





