//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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
/// @brief Contains definition of common fields used in AID class messages.

#pragma once

#include "common.h"

namespace ublox
{

namespace field
{

namespace aid
{

/// @brief Definition of common "svid" field which consumes only 1 byte.
using svid = common::svid;

/// @brief Definition of common "svid" field which consumes 4 bytes.
using svid_ext = common::U4T<comms::option::ValidNumValueRange<1, 96> >;

}  // namespace aid

}  // namespace field

}  // namespace ublox


