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

/// @brief Definition of the fields for AID-ALM (@b poll) message.
/// @see AidAlmPoll
using AidAlmPollFields = std::tuple<>;

/// @brief Definition of AID-ALM (@b poll) message
/// @details Poll request for AID-ALM (@ref AidAlm) message(s).@n
///     Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref AidAlmPollFields for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AidAlmPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALM>,
        comms::option::FieldsImpl<AidAlmPollFields>,
        comms::option::DispatchImpl<AidAlmPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALM>,
        comms::option::FieldsImpl<AidAlmPollFields>,
        comms::option::DispatchImpl<AidAlmPoll<TMsgBase> >
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
    AidAlmPoll() = default;

    /// @brief Copy constructor
    AidAlmPoll(const AidAlmPoll&) = default;

    /// @brief Move constructor
    AidAlmPoll(AidAlmPoll&& other) = default;

    /// @brief Destructor
    virtual ~AidAlmPoll() = default;

    /// @brief Copy assignment
    AidAlmPoll& operator=(const AidAlmPoll&) = default;

    /// @brief Move assignment
    AidAlmPoll& operator=(AidAlmPoll&&) = default;
};


}  // namespace message

}  // namespace ublox





