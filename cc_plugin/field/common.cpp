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


#include "common.h"

#include "comms_champion/comms_champion.h"

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace field
{

namespace common
{

namespace
{

QVariantMap createRes1Properties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "res1");
    return props;
}

QVariantMap createRes2Properties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "res2");
    return props;
}


}  // namespace

const QVariantList& emptyProperties()
{
    static const QVariantList Props;
    return Props;
}

const QVariantMap& res1Properties()
{
    static const QVariantMap Props = createRes1Properties();
    return Props;
}

const QVariantMap& res2Properties()
{
    static const QVariantMap Props = createRes2Properties();
    return Props;
}


}  // namespace common

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox

