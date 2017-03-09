//
// Copyright 2017 (C). Alex Robenko. All rights reserved.
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
/// @brief Contains definition of NAV-TIMELS (@b poll) message and its fields.

#pragma once

#include "ublox/Message.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-TIMELS (@b poll) message fields.
/// @see NavTimelsPoll
struct NavTimelsPollFields
{
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<>;
};

/// @brief Definition of NAV-TIMELS (@b poll) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavTimelsPollFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavTimelsPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMELS>,
        comms::option::FieldsImpl<NavTimelsPollFields::All>,
        comms::option::MsgType<NavTimelsPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_TIMELS>,
        comms::option::FieldsImpl<NavTimelsPollFields::All>,
        comms::option::MsgType<NavTimelsPoll<TMsgBase> >
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
    NavTimelsPoll() = default;

    /// @brief Copy constructor
    NavTimelsPoll(const NavTimelsPoll&) = default;

    /// @brief Move constructor
    NavTimelsPoll(NavTimelsPoll&& other) = default;

    /// @brief Destructor
    virtual ~NavTimelsPoll() = default;

    /// @brief Copy assignment
    NavTimelsPoll& operator=(const NavTimelsPoll&) = default;

    /// @brief Move assignment
    NavTimelsPoll& operator=(NavTimelsPoll&&) = default;
};


}  // namespace message

}  // namespace ublox





