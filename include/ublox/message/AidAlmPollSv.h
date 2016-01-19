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

/// @file
/// @brief Contains definition of AID-ALM (<b>poll SV</b>) message and its fields.

#pragma once

#include "comms/Message.h"
#include "ublox/Message.h"

#include "ublox/field/aid.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the AID-ALM (<b> poll</b>) message fields.
/// @see AidAlmPollSv
struct AidAlmPollSvFields
{
    /// @brief Definition of "svid" field.
    using svid = field::aid::svid;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<svid>;
};

/// @brief Definition of AID-ALM (<b>poll SV</b>) message
/// @details Poll request for AID-ALM (@ref AidAlm) message with requested SV.@n
///     Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref AidAlmPollSvFields for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AidAlmPollSv : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALM>,
        comms::option::FieldsImpl<AidAlmPollSvFields::All>,
        comms::option::DispatchImpl<AidAlmPollSv<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALM>,
        comms::option::FieldsImpl<AidAlmPollSvFields::All>,
        comms::option::DispatchImpl<AidAlmPollSv<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_svid, ///< svid field, see @ref AidAlmPollSvFields::svid
        FieldIdx_numOfValues  ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");


    /// @brief Default constructor
    AidAlmPollSv() = default;

    /// @brief Copy constructor
    AidAlmPollSv(const AidAlmPollSv&) = default;

    /// @brief Move constructor
    AidAlmPollSv(AidAlmPollSv&& other) = default;

    /// @brief Destructor
    virtual ~AidAlmPollSv() = default;

    /// @brief Copy assignment
    AidAlmPollSv& operator=(const AidAlmPollSv&) = default;

    /// @brief Move assignment
    AidAlmPollSv& operator=(AidAlmPollSv&&) = default;
};


}  // namespace message

}  // namespace ublox





