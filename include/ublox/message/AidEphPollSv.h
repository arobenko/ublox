//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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

/// @file
/// @brief Contains definition of AID-EPH (<b>poll SV</b>) message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/aid.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the AID-EPH (<b> poll</b>) message fields.
/// @see AidEphPollSv
struct AidEphPollSvFields
{
    /// @brief Definition of "svid" field.
    using svid = field::aid::svid;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<svid>;
};

/// @brief Definition of AID-EPH (<b>poll SV</b>) message
/// @details Poll request for AID-EPH (@ref AidEph) message with requested SV.@n
///     Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref AidEphPollSvFields for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AidEphPollSv : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_EPH>,
        comms::option::FieldsImpl<AidEphPollSvFields::All>,
        comms::option::DispatchImpl<AidEphPollSv<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_EPH>,
        comms::option::FieldsImpl<AidEphPollSvFields::All>,
        comms::option::DispatchImpl<AidEphPollSv<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_svid, ///< svid field, see @ref AidEphPollSvFields::svid
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    AidEphPollSv() = default;

    /// @brief Copy constructor
    AidEphPollSv(const AidEphPollSv&) = default;

    /// @brief Move constructor
    AidEphPollSv(AidEphPollSv&& other) = default;

    /// @brief Destructor
    virtual ~AidEphPollSv() = default;

    /// @brief Copy assignment
    AidEphPollSv& operator=(const AidEphPollSv&) = default;

    /// @brief Move assignment
    AidEphPollSv& operator=(AidEphPollSv&&) = default;
};


}  // namespace message

}  // namespace ublox





