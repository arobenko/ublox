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
/// @brief Contains definition of CFG-NAVX5 (@b poll) message and its fields.

#pragma once

#include "ublox/Message.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-NAVX5 (@b poll) message fields.
/// @see CfgNavx5
struct CfgNavx5PollFields
{
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<>;
};

/// @brief Definition of CFG-NAVX5 (@b poll) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgNavx5PollFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgNavx5Poll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_NAVX5>,
        comms::option::FieldsImpl<CfgNavx5PollFields::All>,
        comms::option::MsgType<CfgNavx5Poll<TMsgBase> >
    >
{
public:

    /// @brief Default constructor
    CfgNavx5Poll() = default;

    /// @brief Copy constructor
    CfgNavx5Poll(const CfgNavx5Poll&) = default;

    /// @brief Move constructor
    CfgNavx5Poll(CfgNavx5Poll&& other) = default;

    /// @brief Destructor
    ~CfgNavx5Poll() = default;

    /// @brief Copy assignment
    CfgNavx5Poll& operator=(const CfgNavx5Poll&) = default;

    /// @brief Move assignment
    CfgNavx5Poll& operator=(CfgNavx5Poll&&) = default;
};


}  // namespace message

}  // namespace ublox

