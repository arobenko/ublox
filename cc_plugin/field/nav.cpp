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
    return
        cc::property::field::ForField<ublox::field::nav::ecef>()
            .name(QString("ecef%1").arg(dir))
            .asMap();
}

QVariantMap createProps_gpsFix(const QString& propsName)
{
    cc::property::field::ForField<ublox::field::nav::gpsFix> props;
    props.name(propsName)
         .add("no fix")
         .add("dead reckoning only")
         .add("2D-fix")
         .add("3D-fix")
         .add("GPS + dead reckoning combined")
         .add("time only fix");
    assert(props.values().size() == (int)ublox::field::nav::GpsFix::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_lon()
{
    return
        cc::property::field::ForField<ublox::field::nav::lon>()
            .name("lon")
            .scaledDecimals(7)
            .asMap();
}

QVariantMap createProps_lat()
{
    return
        cc::property::field::ForField<ublox::field::nav::lat>()
            .name("lat")
            .scaledDecimals(7)
            .asMap();
}

QVariantMap createProps_heading()
{
    return
        cc::property::field::ForField<ublox::field::nav::heading>()
            .name("heading")
            .scaledDecimals(5)
            .asMap();
}

QVariantMap createProps_velX(char suffix)
{
    return
        cc::property::field::IntValue()
            .name(QString("vel%1").arg(suffix))
            .asMap();
}

QVariantMap createProps_numCh(const QString& propsName)
{
    return
        cc::property::field::IntValue()
            .name(propsName)
            .readOnly()
            .asMap();
}

}  // namespace

const QVariantMap& props_iTOW()
{
    return common::props_iTOW();
}

const QVariantMap& props_fTOW()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::nav::fTOW>()
            .name("fTOW")
            .asMap();
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
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::nav::pAcc>()
            .name("pAcc")
            .asMap();
    return Props;
}

const QVariantMap& props_sAcc()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::nav::sAcc>()
            .name("sAcc")
            .asMap();
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
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::nav::height>()
            .name("height")
            .asMap();
    return Props;
}

const QVariantMap& props_hMSL()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::nav::hMSL>()
            .name("hMSL")
            .asMap();
    return Props;
}

const QVariantMap& props_hAcc()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::nav::hAcc>()
            .name("hAcc")
            .asMap();
    return Props;
}

const QVariantMap& props_vAcc()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::nav::vAcc>()
            .name("vAcc")
            .asMap();
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
    return
        cc::property::field::IntValue()
            .name(QString("%1DOP").arg(prefix))
            .scaledDecimals(2)
            .asMap();
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
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::nav::year>()
            .name("year")
            .asMap();
    return Props;
}

const QVariantMap& props_month()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::nav::month>()
            .name("month")
            .asMap();
    return Props;
}

const QVariantMap& props_day()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::nav::day>()
            .name("day")
            .asMap();
    return Props;
}

const QVariantMap& props_hour()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::nav::hour>()
            .name("hour")
            .asMap();
    return Props;
}

const QVariantMap& props_min()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::nav::min>()
            .name("min")
            .asMap();
    return Props;
}

const QVariantMap& props_sec()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::nav::sec>()
            .name("sec")
            .asMap();
    return Props;
}

const QVariantMap& props_tAcc()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::nav::tAcc>()
            .name("tAcc")
            .asMap();
    return Props;
}

const QVariantMap& props_nano()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::nav::nano>()
            .name("nano")
            .asMap();
    return Props;
}

const QVariantMap& props_gSpeed()
{
    static const QVariantMap Props =
        cc::property::field::IntValue()
            .name("gSpeed")
            .asMap();
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

