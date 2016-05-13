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
#include "ublox/field/nav.h"
#include "common.h"

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

QVariantMap createProps_ecef(const char* dir)
{
    return cc::Property::createPropertiesMap(QString("ecef%1").arg(dir));
}

QVariantMap createProps_gpsFix(const QString& propsName)
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "no fix");
    cc::Property::appendEnumValue(enumValues, "dead reckoning only");
    cc::Property::appendEnumValue(enumValues, "2D-fix");
    cc::Property::appendEnumValue(enumValues, "3D-fix");
    cc::Property::appendEnumValue(enumValues, "GPS + dead reckoning combined");
    cc::Property::appendEnumValue(enumValues, "time only fix");

    return cc::Property::createPropertiesMap(propsName, std::move(enumValues));
}

QVariantMap createProps_lon()
{
    auto props = cc::Property::createPropertiesMap("lon");
    cc::Property::setDisplayScaled(props);
    cc::Property::setFloatDecimals(props, 7);
    return props;
}

QVariantMap createProps_lat()
{
    auto props = cc::Property::createPropertiesMap("lat");
    cc::Property::setDisplayScaled(props);
    cc::Property::setFloatDecimals(props, 7);
    return props;
}

QVariantMap createProps_heading()
{
    auto props = cc::Property::createPropertiesMap("heading");
    cc::Property::setDisplayScaled(props);
    cc::Property::setFloatDecimals(props, 5);
    return props;
}

QVariantMap createProps_velX(char suffix)
{
    return cc::Property::createPropertiesMap(QString("vel%1").arg(suffix));
}

QVariantMap createProps_numCh(const QString& propsName)
{
    auto props = cc::Property::createPropertiesMap(propsName);
    cc::Property::setReadOnly(props);
    return props;
}

}  // namespace

const QVariantMap& props_iTOW()
{
    return common::props_iTOW();
}

const QVariantMap& props_fTOW()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("fTOW");
    return Props;
}

const QVariantMap& props_ecefX()
{
    static const QVariantMap Props = createProps_ecef("X");
    return Props;
}

const QVariantMap& props_ecefY()
{
    static const QVariantMap Props = createProps_ecef("Y");
    return Props;
}

const QVariantMap& props_ecefZ()
{
    static const QVariantMap Props = createProps_ecef("Z");
    return Props;
}

const QVariantMap& props_ecefVX()
{
    static const QVariantMap Props = createProps_ecef("VX");
    return Props;
}

const QVariantMap& props_ecefVY()
{
    static const QVariantMap Props = createProps_ecef("VY");
    return Props;
}

const QVariantMap& props_ecefVZ()
{
    static const QVariantMap Props = createProps_ecef("VZ");
    return Props;
}

const QVariantMap& props_pAcc()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("pAcc");
    return Props;
}

const QVariantMap& props_sAcc()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("sAcc");
    return Props;
}

const QVariantMap& props_lon()
{
    static const QVariantMap Props = createProps_lon();
    return Props;
}

const QVariantMap& props_lat()
{
    static const QVariantMap Props = createProps_lat();
    return Props;
}

const QVariantMap& props_height()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("height");
    return Props;
}

const QVariantMap& props_hMSL()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("hMSL");
    return Props;
}

const QVariantMap& props_hAcc()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("hAcc");
    return Props;
}

const QVariantMap& props_vAcc()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("vAcc");
    return Props;
}

const QVariantMap& props_gpsFix()
{
    static const QVariantMap Props = createProps_gpsFix("gpsFix");
    return Props;
}

const QVariantMap& props_fixType()
{
    static const QVariantMap Props = createProps_gpsFix("fixType");
    return Props;
}

QVariantMap createProps_xDOP(char prefix)
{
    auto props = cc::Property::createPropertiesMap(QString("%1DOP").arg(prefix));
    cc::Property::setDisplayScaled(props);
    cc::Property::setFloatDecimals(props, 2);
    return props;
}

const QVariantMap& props_pDOP()
{
    static const auto Props = createProps_xDOP('p');
    return Props;
}

const QVariantMap& props_week()
{
    return common::props_week();
}

const QVariantMap& props_numSV()
{
    return common::props_numSV();
}

const QVariantMap& props_year()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("year");
    return Props;
}

const QVariantMap& props_month()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("month");
    return Props;
}

const QVariantMap& props_day()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("day");
    return Props;
}

const QVariantMap& props_hour()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("hour");
    return Props;
}

const QVariantMap& props_min()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("min");
    return Props;
}

const QVariantMap& props_sec()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("sec");
    return Props;
}

const QVariantMap& props_tAcc()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("tAcc");
    return Props;
}

const QVariantMap& props_nano()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("nano");
    return Props;
}

const QVariantMap& props_gSpeed()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("gSpeed");
    return Props;
}

const QVariantMap& props_heading()
{
    static const QVariantMap Props = createProps_heading();
    return Props;
}

const QVariantMap& props_velN()
{
    static const QVariantMap Props = createProps_velX('N');
    return Props;
}

const QVariantMap& props_velE()
{
    static const QVariantMap Props = createProps_velX('E');
    return Props;
}

const QVariantMap& props_velD()
{
    static const QVariantMap Props = createProps_velX('D');
    return Props;
}

const QVariantMap& props_numCh()
{
    static const QVariantMap Props = createProps_numCh("numCh");
    return Props;
}

const QVariantMap& props_cnt()
{
    static const QVariantMap Props = createProps_numCh("cnt");
    return Props;
}

const QVariantMap& props_svid()
{
    return common::props_svid();
}

}  // namespace nav

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox

