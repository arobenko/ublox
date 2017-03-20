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

/// @brief Definition of INF-ERROR message
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TStrOpt Extra option(s) for @b str field
template <typename TMsgBase = Message, typename TStrOpt = comms::option::EmptyOption>
class InfError : public
    InfStringMsgBase<
        MsgId_INF_ERROR,
        TMsgBase,
        TStrOpt,
        InfError<TMsgBase, TStrOpt> >
{
public:
    /// @brief Default constructor
    InfError() = default;

    /// @brief Copy constructor
    InfError(const InfError&) = default;

    /// @brief Move constructor
    InfError(InfError&& other) = default;

    /// @brief Destructor
    ~InfError() = default;

    /// @brief Copy assignment
    InfError& operator=(const InfError&) = default;

    /// @brief Move assignment
    InfError& operator=(InfError&&) = default;

};

}  // namespace message

}  // namespace ublox



