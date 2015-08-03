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

#include "inf.h"

#include "comms_champion/comms_champion.h"

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace field
{

namespace inf
{

namespace
{

QVariantMap createStringProperties()
{
    return cc::Property::createPropertiesMap("String");
}

}  // namespace

const QVariantMap& stringProperties()
{
    static const QVariantMap Props = createStringProperties();
    return Props;
}

}  // namespace inf

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox


