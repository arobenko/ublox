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
/// @brief Contains definition of INF-DEBUG message.

#pragma once

#include "InfStringMsgBase.h"

namespace ublox
{

namespace message
{

/// @brief Definition of INF-DEBUG message
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class InfDebug : public InfStringMsgBase<MsgId_INF_DEBUG, TMsgBase>
{
public:
    /// @brief Default constructor
    InfDebug() = default;

    /// @brief Copy constructor
    InfDebug(const InfDebug&) = default;

    /// @brief Move constructor
    InfDebug(InfDebug&& other) = default;

    /// @brief Destructor
    virtual ~InfDebug() = default;

    /// @brief Copy assignment
    InfDebug& operator=(const InfDebug&) = default;

    /// @brief Move assignment
    InfDebug& operator=(InfDebug&&) = default;

};

}  // namespace message

}  // namespace ublox



