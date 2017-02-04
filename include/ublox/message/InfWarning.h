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
/// @brief Contains definition of INF-WARNING message.

#pragma once

#include "InfStringMsgBase.h"

namespace ublox
{

namespace message
{

/// @brief Definition of INF-WARNING message
/// @tparam TMsgBase Common interface class for all the messages.
/// @tparam TStrOpt Extra option(s) for @b str field
template <typename TMsgBase = Message, typename TStrOpt = comms::option::EmptyOption>
class InfWarning : public
    InfStringMsgBase<
        MsgId_INF_WARNING,
        TMsgBase,
        TStrOpt,
        InfWarning<TMsgBase, TStrOpt> >
{
public:
    /// @brief Default constructor
    InfWarning() = default;

    /// @brief Copy constructor
    InfWarning(const InfWarning&) = default;

    /// @brief Move constructor
    InfWarning(InfWarning&& other) = default;

    /// @brief Destructor
    virtual ~InfWarning() = default;

    /// @brief Copy assignment
    InfWarning& operator=(const InfWarning&) = default;

    /// @brief Move assignment
    InfWarning& operator=(InfWarning&&) = default;
};

}  // namespace message

}  // namespace ublox



