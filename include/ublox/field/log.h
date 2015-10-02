//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
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


#pragma once

#include "common.h"

namespace ublox
{

namespace field
{

namespace log
{

using year  =
    field::common::U2T<
        comms::option::ValidNumValueRange<1, 65635>
    >;
using month  =
    field::common::U1T<
        comms::option::ValidNumValueRange<1, 12>
    >;
using day  =
    field::common::U1T<
        comms::option::ValidNumValueRange<1, 31>
    >;
using hour  =
    field::common::U1T<
        comms::option::ValidNumValueRange<0, 23>
    >;
using minute  =
    field::common::U1T<
        comms::option::ValidNumValueRange<0, 59>
    >;
using second  =
    field::common::U1T<
        comms::option::ValidNumValueRange<0, 60>
    >;

}  // namespace log

}  // namespace field

}  // namespace ublox


