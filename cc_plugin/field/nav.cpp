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

QVariantMap createNameOnlyProperties(const char* name)
{
    QVariantMap props;
    props.insert(cc::Property::name(), name);
    return props;
}

QVariantMap createEcefProperties(const char* dir)
{
    QVariantMap props;
    props.insert(cc::Property::name(), QString("ECEF%1").arg(dir));
    return props;
}

QVariantMap createZoneProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "ZONE");
    return props;
}

QVariantMap createHemProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "HEM");
    props.insert(cc::Property::indexedName(0), "North");
    props.insert(cc::Property::indexedName(1), "South");
    return props;
}

QVariantMap createDopProperties(char letter)
{
    static const QString Suffix("DOP");
    QVariantMap props;
    QString str(letter);
    str.append(Suffix);
    props.insert(cc::Property::name(), str);
    return props;
}

QVariantMap createGpsFixProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "GPSfix");
    props.insert(cc::Property::indexedName(0U), "no fix");
    props.insert(cc::Property::indexedName(1U), "dead reckoning only");
    props.insert(cc::Property::indexedName(2U), "2D-fix");
    props.insert(cc::Property::indexedName(3U), "3D-fix");
    props.insert(cc::Property::indexedName(4U), "GPS + dead reckoning combined");
    props.insert(cc::Property::indexedName(5U), "time only fix");
    return props;
}

QVariantMap createFlagsProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "Flags");
    props.insert(cc::Property::indexedName(0U), "GPSfixOK");
    props.insert(cc::Property::indexedName(1U), "DiffSoln");
    props.insert(cc::Property::indexedName(2U), "WKNSET");
    props.insert(cc::Property::indexedName(3U), "TOWSET");
    return props;
}

QVariantMap createDiffStatusProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "DiffS");
    props.insert(cc::Property::indexedName(0U), "none");
    props.insert(cc::Property::indexedName(1U), "PR+PRR Correction");
    props.insert(cc::Property::indexedName(2U), "PR+PRR+CP Correction");
    props.insert(cc::Property::indexedName(3U), "High accuracy PR+PRR+CP Correction");
    return props;
}

QVariantMap createVelProperties(const char* dir)
{
    QString str("VEL_");
    str.append(QString(dir));
    QVariantMap props;
    props.insert(cc::Property::name(), str);
    return props;
}

QVariantMap createTimeValidProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "Valid");
    props.insert(cc::Property::indexedName(0U), "Valid Time of Week");
    props.insert(cc::Property::indexedName(1U), "Valid Week Number");
    props.insert(cc::Property::indexedName(2U), "Valid UTC");
    return props;
}

QVariantMap createNchProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "NCH");
    props.insert(cc::Property::readOnly(), true);
    return props;
}

QVariantMap createInfoFlagsProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "Flags");
    props.insert(cc::Property::indexedName(0U), "SV is used for navigation");
    props.insert(cc::Property::indexedName(1U), "Diff correction data is available");
    props.insert(cc::Property::indexedName(2U), "Orbit info is available");
    props.insert(cc::Property::indexedName(3U), "Orbit info is Ephemeris");
    props.insert(cc::Property::indexedName(4U), "SV is unhealthy");
    return props;
}

QVariantMap createQiProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "QI");
    props.insert(cc::Property::indexedName(0U), "Idle");
    props.insert(cc::Property::indexedName(1U), "Searching");
    props.insert(cc::Property::indexedName(2U), "Searching (2)");
    props.insert(cc::Property::indexedName(3U), "Signal detected, unusable");
    props.insert(cc::Property::indexedName(4U), "Code Lock on Signal");
    props.insert(cc::Property::indexedName(5U), "Code and Carrier locked");
    props.insert(cc::Property::indexedName(6U), "Code and Carrier locked (2)");
    props.insert(cc::Property::indexedName(7U), "Code and Carrier locked, 50bps data");
    return props;
}


}  // namespace

const QVariantMap& itowProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("ITOW");
    return Props;
}

const QVariantMap& ecefPropertiesX()
{
    static const QVariantMap Props = createEcefProperties("_X");
    return Props;
}

const QVariantMap& ecefPropertiesY()
{
    static const QVariantMap Props = createEcefProperties("_Y");
    return Props;
}

const QVariantMap& ecefPropertiesZ()
{
    static const QVariantMap Props = createEcefProperties("_Z");
    return Props;
}

const QVariantMap& ecefPropertiesVX()
{
    static const QVariantMap Props = createEcefProperties("VX");
    return Props;
}

const QVariantMap& ecefPropertiesVY()
{
    static const QVariantMap Props = createEcefProperties("VY");
    return Props;
}

const QVariantMap& ecefPropertiesVZ()
{
    static const QVariantMap Props = createEcefProperties("VZ");
    return Props;
}

const QVariantMap& paccProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Pacc");
    return Props;
}

const QVariantMap& lonProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("LON");
    return Props;
}

const QVariantMap& latProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("LAT");
    return Props;
}

const QVariantMap& heightProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("HEIGHT");
    return Props;
}

const QVariantMap& hmslProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("HMSL");
    return Props;
}

const QVariantMap& haccProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Hacc");
    return Props;
}

const QVariantMap& vaccProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Vacc");
    return Props;
}

const QVariantMap& eastProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("EAST");
    return Props;
}

const QVariantMap& northProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("NORTH");
    return Props;
}

const QVariantMap& altProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("ALT");
    return Props;
}

const QVariantMap& zoneProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("ZONE");
    return Props;
}

const QVariantMap& hemProperties()
{
    static const QVariantMap Props = createHemProperties();
    return Props;
}

const QVariantMap& gdopProperties()
{
    static const QVariantMap Props = createDopProperties('G');
    return Props;
}

const QVariantMap& pdopProperties()
{
    static const QVariantMap Props = createDopProperties('P');
    return Props;
}

const QVariantMap& tdopProperties()
{
    static const QVariantMap Props = createDopProperties('T');
    return Props;
}

const QVariantMap& vdopProperties()
{
    static const QVariantMap Props = createDopProperties('V');
    return Props;
}

const QVariantMap& hdopProperties()
{
    static const QVariantMap Props = createDopProperties('H');
    return Props;
}

const QVariantMap& ndopProperties()
{
    static const QVariantMap Props = createDopProperties('N');
    return Props;
}

const QVariantMap& edopProperties()
{
    static const QVariantMap Props = createDopProperties('E');
    return Props;
}

const QVariantMap& gpsFixProperties()
{
    static const QVariantMap Props = createGpsFixProperties();
    return Props;
}

const QVariantMap& flagsProperties()
{
    static const QVariantMap Props = createFlagsProperties();
    return Props;
}

const QVariantMap& diffStatusProperties()
{
    static const QVariantMap Props = createDiffStatusProperties();
    return Props;
}

const QVariantMap& ttffProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("TTFF");
    return Props;
}

const QVariantMap& msssProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("MSSS");
    return Props;
}

const QVariantMap& fracProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Frac");
    return Props;
}

const QVariantMap& weekProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("week");
    return Props;
}

const QVariantMap& saccProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("SAcc");
    return Props;
}

const QVariantMap& numSvProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("numSV");
    return Props;
}

const QVariantMap& velPropertiesN()
{
    static const QVariantMap Props = createVelProperties("N");
    return Props;
}

const QVariantMap& velPropertiesE()
{
    static const QVariantMap Props = createVelProperties("E");
    return Props;
}

const QVariantMap& velPropertiesD()
{
    static const QVariantMap Props = createVelProperties("D");
    return Props;
}

const QVariantMap& speedProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Speed");
    return Props;
}

const QVariantMap& groundSpeedProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("GSpeed");
    return Props;
}

const QVariantMap& headingProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Heading");
    return Props;
}

const QVariantMap& caccProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("CAcc");
    return Props;
}

const QVariantMap& leapSecProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("LeapS");
    return Props;
}

const QVariantMap& timeValidProperties()
{
    static const QVariantMap Props = createTimeValidProperties();
    return Props;
}

const QVariantMap& taccProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("TAcc");
    return Props;
}

const QVariantMap& nanoProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Nano");
    return Props;
}

const QVariantMap& yearProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Year");
    return Props;
}

const QVariantMap& monthProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Month");
    return Props;
}

const QVariantMap& dayProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Day");
    return Props;
}

const QVariantMap& hourProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Hour");
    return Props;
}

const QVariantMap& minProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Min");
    return Props;
}

const QVariantMap& secProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Sec");
    return Props;
}

const QVariantMap& clkbProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("CLKB");
    return Props;
}

const QVariantMap& clkdProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("CLKD");
    return Props;
}

const QVariantMap& faccProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("FAcc");
    return Props;
}

const QVariantMap& nchProperties()
{
    static const QVariantMap Props = createNchProperties();
    return Props;
}

const QVariantMap& svidProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("SVID");
    return Props;
}

const QVariantMap& chNumProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("chn");
    return Props;
}

const QVariantMap& infoFlagsProperties()
{
    static const QVariantMap Props = createInfoFlagsProperties();
    return Props;
}

const QVariantMap& qiProperties()
{
    static const QVariantMap Props = createQiProperties();
    return Props;
}

const QVariantMap& cnoProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("CNO");
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

const QVariantMap& prresProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("PRRes");
    return Props;
}

}  // namespace nav

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox

