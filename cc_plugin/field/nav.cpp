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

#include "nav.h"

#include "comms_champion/comms_champion.h"

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace field
{

namespace nav
{

namespace
{

QVariantMap createItowProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "ITOW");
    return props;
}

QVariantMap createEcefProperties(const char* dir)
{
    QVariantMap props;
    props.insert(cc::Property::name(), QString("ECEF_%1").arg(dir));
    return props;
}

QVariantMap createPaccProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "Pacc");
    return props;
}

}  // namespace

const QVariantMap& itowProperties()
{
    static const QVariantMap Props = createItowProperties();
    return Props;
}

const QVariantMap& ecefPropertiesX()
{
    static const QVariantMap Props = createEcefProperties("X");
    return Props;
}

const QVariantMap& ecefPropertiesY()
{
    static const QVariantMap Props = createEcefProperties("Y");
    return Props;
}

const QVariantMap& ecefPropertiesZ()
{
    static const QVariantMap Props = createEcefProperties("Z");
    return Props;
}

const QVariantMap& paccProperties()
{
    static const QVariantMap Props = createPaccProperties();
    return Props;
}

}  // namespace nav

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox

