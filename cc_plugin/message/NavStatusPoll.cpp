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

#include <type_traits>
#include <functional>
#include <cassert>

#include "NavStatusPoll.h"
#include "cc_plugin/field/common.h"

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

const char* NavStatusPoll::nameImpl() const
{
    static const char* Str = "NAV-STATUS (Poll)";
    return Str;
}

const QVariantList& NavStatusPoll::fieldsPropertiesImpl() const
{
    return field::common::emptyProperties();
}

bool NavStatusPoll::isPollImpl() const
{
    return true;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

