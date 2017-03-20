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
/// @brief Contains definition of NAV-DGPS (@b poll) message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/nav.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the NAV-DGPS (@b poll) message fields.
/// @see NavDgpsPoll
struct NavDgpsPollFields
{
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<>;
};

/// @brief Definition of NAV-DGPS (@b poll) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref NavDgpsPollFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class NavDgpsPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_DGPS>,
        comms::option::FieldsImpl<NavDgpsPollFields::All>,
        comms::option::MsgType<NavDgpsPoll<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_NAV_DGPS>,
        comms::option::FieldsImpl<NavDgpsPollFields::All>,
        comms::option::MsgType<NavDgpsPoll<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == 0U,
        "Number of fields is incorrect");

    /// @brief Default constructor
    NavDgpsPoll() = default;

    /// @brief Copy constructor
    NavDgpsPoll(const NavDgpsPoll&) = default;

    /// @brief Move constructor
    NavDgpsPoll(NavDgpsPoll&& other) = default;

    /// @brief Destructor
    ~NavDgpsPoll() = default;

    /// @brief Copy assignment
    NavDgpsPoll& operator=(const NavDgpsPoll&) = default;

    /// @brief Move assignment
    NavDgpsPoll& operator=(NavDgpsPoll&&) = default;
};


}  // namespace message

}  // namespace ublox





