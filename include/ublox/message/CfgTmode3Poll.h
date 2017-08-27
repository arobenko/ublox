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
/// @brief Contains definition of CFG-TMODE3 (@b poll) message and its fields.

#pragma once

#include "ublox/Message.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-TMODE3 (@b poll) message fields.
/// @see CfgTmode3Poll
struct CfgTmode3PollFields
{
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<>;
};

/// @brief Definition of CFG-TMODE3 (@b poll) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgTmode3PollFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgTmode3Poll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_TMODE3>,
        comms::option::FieldsImpl<CfgTmode3PollFields::All>,
        comms::option::MsgType<CfgTmode3Poll<TMsgBase> >
    >
{
public:

    /// @brief Default constructor
    CfgTmode3Poll() = default;

    /// @brief Copy constructor
    CfgTmode3Poll(const CfgTmode3Poll&) = default;

    /// @brief Move constructor
    CfgTmode3Poll(CfgTmode3Poll&& other) = default;

    /// @brief Destructor
    ~CfgTmode3Poll() = default;

    /// @brief Copy assignment
    CfgTmode3Poll& operator=(const CfgTmode3Poll&) = default;

    /// @brief Move assignment
    CfgTmode3Poll& operator=(CfgTmode3Poll&&) = default;
};


}  // namespace message

}  // namespace ublox

