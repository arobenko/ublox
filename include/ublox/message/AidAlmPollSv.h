//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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
///     Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref AidAlmPollSvFields for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AidAlmPollSv : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALM>,
        comms::option::FieldsImpl<AidAlmPollSvFields::All>,
        comms::option::MsgType<AidAlmPollSv<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALM>,
        comms::option::FieldsImpl<AidAlmPollSvFields::All>,
        comms::option::MsgType<AidAlmPollSv<TMsgBase> >
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b svid for @ref AidAlmPollSvFields::svid field
    COMMS_MSG_FIELDS_ACCESS(svid);

    /// @brief Default constructor
    AidAlmPollSv() = default;

    /// @brief Copy constructor
    AidAlmPollSv(const AidAlmPollSv&) = default;

    /// @brief Move constructor
    AidAlmPollSv(AidAlmPollSv&& other) = default;

    /// @brief Destructor
    ~AidAlmPollSv() = default;

    /// @brief Copy assignment
    AidAlmPollSv& operator=(const AidAlmPollSv&) = default;

    /// @brief Move assignment
    AidAlmPollSv& operator=(AidAlmPollSv&&) = default;
};


}  // namespace message

}  // namespace ublox





