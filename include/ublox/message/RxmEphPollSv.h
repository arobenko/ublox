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

using RxmEphPollSvField_svid = field::rxm::svid;

using RxmEphPollSvFields = std::tuple<
    RxmEphPollSvField_svid
>;


template <typename TMsgBase = Message>
class RxmEphPollSv : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_EPH>,
        comms::option::FieldsImpl<RxmEphPollSvFields>,
        comms::option::DispatchImpl<RxmEphPollSv<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_RXM_EPH>,
        comms::option::FieldsImpl<RxmEphPollSvFields>,
        comms::option::DispatchImpl<RxmEphPollSv<TMsgBase> >
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
    RxmEphPollSv() = default;

    /// @brief Copy constructor
    RxmEphPollSv(const RxmEphPollSv&) = default;

    /// @brief Move constructor
    RxmEphPollSv(RxmEphPollSv&& other) = default;

    /// @brief Destructor
    virtual ~RxmEphPollSv() = default;

    /// @brief Copy assignment
    RxmEphPollSv& operator=(const RxmEphPollSv&) = default;

    /// @brief Move assignment
    RxmEphPollSv& operator=(RxmEphPollSv&&) = default;
};


}  // namespace message

}  // namespace ublox





