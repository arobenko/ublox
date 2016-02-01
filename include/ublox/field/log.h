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
/// @brief Contains definition of common fields used in LOG class messages.

#pragma once

#include "common.h"

namespace ublox
{

namespace field
{

namespace log
{

/// @brief Definition of common "year" field.
using year  =
    field::common::U2T<
        comms::option::ValidNumValueRange<1, 65635>
    >;

/// @brief Definition of common "month" field.
using month  =
    field::common::U1T<
        comms::option::ValidNumValueRange<1, 12>
    >;

/// @brief Definition of common "day" field.
using day  =
    field::common::U1T<
        comms::option::ValidNumValueRange<1, 31>
    >;

/// @brief Definition of common "hour" field.
using hour  =
    field::common::U1T<
        comms::option::ValidNumValueRange<0, 23>
    >;

/// @brief Definition of common "minute" field.
using minute  =
    field::common::U1T<
        comms::option::ValidNumValueRange<0, 59>
    >;

/// @brief Definition of common "second" field.
using second  =
    field::common::U1T<
        comms::option::ValidNumValueRange<0, 60>
    >;

}  // namespace log

}  // namespace field

}  // namespace ublox


