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
/// @brief Contains definition of INF-NOTICE message.

#pragma once

#include "InfStringMsgBase.h"

namespace ublox
{

namespace message
{

/// @brief Definition of INF-NOTICE message
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class InfNotice : public InfStringMsgBase<MsgId_INF_NOTICE, TMsgBase>
{
public:
    /// @brief Default constructor
    InfNotice() = default;

    /// @brief Copy constructor
    InfNotice(const InfNotice&) = default;

    /// @brief Move constructor
    InfNotice(InfNotice&& other) = default;

    /// @brief Destructor
    virtual ~InfNotice() = default;

    /// @brief Copy assignment
    InfNotice& operator=(const InfNotice&) = default;

    /// @brief Move assignment
    InfNotice& operator=(InfNotice&&) = default;
};

}  // namespace message

}  // namespace ublox



