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
/// @brief Contains definition of CFG-DGNSS (@b poll) message and its fields.

#pragma once

#include "ublox/Message.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the CFG-DGNSS (@b poll) message fields.
/// @see CfgDgnssPoll
struct CfgDgnssPollFields
{
    using All = std::tuple<>;
};

/// @brief Definition of CFG-DGNSS (@b poll) message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref CfgDgnssPollFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class CfgDgnssPoll : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_CFG_DGNSS>,
        comms::option::FieldsImpl<CfgDgnssPollFields::All>,
        comms::option::MsgType<CfgDgnssPoll<TMsgBase> >
    >
{
public:
    /// @brief Default constructor
    CfgDgnssPoll() = default;

    /// @brief Copy constructor
    CfgDgnssPoll(const CfgDgnssPoll&) = default;

    /// @brief Move constructor
    CfgDgnssPoll(CfgDgnssPoll&& other) = default;

    /// @brief Destructor
    ~CfgDgnssPoll() = default;

    /// @brief Copy assignment
    CfgDgnssPoll& operator=(const CfgDgnssPoll&) = default;

    /// @brief Move assignment
    CfgDgnssPoll& operator=(CfgDgnssPoll&&) = default;
};


}  // namespace message

}  // namespace ublox

