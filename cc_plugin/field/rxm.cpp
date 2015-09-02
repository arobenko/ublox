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

#include "rxm.h"

#include "comms_champion/comms_champion.h"
#include "ublox/field/rxm.h"
#include "common.h"

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace field
{

namespace rxm
{

namespace
{

QVariantMap createProps_numSV()
{
    auto props = common::props_numSV();
    cc::Property::setReadOnly(props);
    return props;
}

}  // namespace

const QVariantMap& props_iTOW()
{
    return common::props_iTOW();
}

const QVariantMap& props_week()
{
    return common::props_week();
}

const QVariantMap& props_numSV()
{
    static const auto Props = createProps_numSV();
    return Props;
}

const QVariantMap& props_svid()
{
    return common::props_svid();
}

}  // namespace rxm

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox




