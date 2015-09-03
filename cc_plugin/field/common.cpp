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

#include <type_traits>

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

QVariantMap createProps_reserved(unsigned idx)
{
    auto str = QString("reserved%1").arg(idx, 1, 10, QChar('0'));
    return cc::Property::createPropertiesMap(str);
}

// TODO: remove
QVariantMap createResProperties(unsigned idx)
{
    auto str = QString("res%1").arg(idx, 1, 10, QChar('0'));
    return cc::Property::createPropertiesMap(str);
}

QVariantMap createNameOnlyProperties(const char* name)
{
    return cc::Property::createPropertiesMap(name);
}

}  // namespace

const QVariantList& emptyProperties()
{
    static const QVariantList Props;
    return Props;
}

const QVariantMap& props_iTOW()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("iTOW");
    return Props;
}

const QVariantMap& props_week()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("week");
    return Props;
}

const QVariantMap& props_numSV()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("numSV");
    return Props;
}

const QVariantMap& props_svid()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("svid");
    return Props;
}

const QVariantMap& props_reserved(unsigned idx)
{
    static const QVariantMap Props[] = {
        createProps_reserved(0),
        createProps_reserved(1),
        createProps_reserved(2),
        createProps_reserved(3),
        createProps_reserved(4),
        createProps_reserved(5)
    };

    static const auto MapSize = std::extent<decltype(Props)>::value;
    if (MapSize <= idx) {
        static const QVariantMap EmptyMap;
        return EmptyMap;
    }

    return Props[idx];
}




// TODO: remove
const QVariantMap& resProperties()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("res");
    return Props;
}

const QVariantMap& resProperties(unsigned idx)
{
    static const QVariantMap Props[] = {
        createResProperties(0),
        createResProperties(1),
        createResProperties(2),
        createResProperties(3),
        createResProperties(4)
    };

    static const auto MapSize = std::extent<decltype(Props)>::value;
    if (MapSize <= idx) {
        static const QVariantMap EmptyMap;
        return EmptyMap;
    }

    return Props[idx];
}

const QVariantMap& padProperties()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("pad");
    return Props;
}

const QVariantMap& itowProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("ITOW");
    return Props;
}

const QVariantMap& svidProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("SVID");
    return Props;
}

const QVariantMap& elevProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Elev");
    return Props;
}

const QVariantMap& azimProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Azim");
    return Props;
}


}  // namespace common

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox

