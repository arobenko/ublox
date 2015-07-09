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
    props.insert(cc::Property::name(), QString("ECEF%1").arg(dir));
    return props;
}

QVariantMap createPaccProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "Pacc");
    return props;
}

QVariantMap createLonProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "LON");
    return props;
}

QVariantMap createLatProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "LAT");
    return props;
}

QVariantMap createHeightProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "HEIGHT");
    return props;
}

QVariantMap createHmslProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "HMSL");
    return props;
}

QVariantMap createHaccProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "Hacc");
    return props;
}

QVariantMap createVaccProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "Vacc");
    return props;
}

QVariantMap createEastProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "EAST");
    return props;
}

QVariantMap createNorthProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "NORTH");
    return props;
}

QVariantMap createAltProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "NORTH");
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

QVariantMap createTtffProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "TTFF");
    return props;
}

QVariantMap createMsssProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "MSSS");
    return props;
}

QVariantMap createFracProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "Frac");
    return props;
}

QVariantMap createWeekProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "week");
    return props;
}

QVariantMap createSaccProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "SAcc");
    return props;
}

QVariantMap createNumSvProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "numSV");
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

QVariantMap createSpeedProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "Speed");
    return props;
}

QVariantMap createGroundSpeedProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "GSpeed");
    return props;
}

QVariantMap createHeadingProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "Heading");
    return props;
}

QVariantMap createCaccProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "CAcc");
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
    static const QVariantMap Props = createPaccProperties();
    return Props;
}

const QVariantMap& lonProperties()
{
    static const QVariantMap Props = createLonProperties();
    return Props;
}

const QVariantMap& latProperties()
{
    static const QVariantMap Props = createLatProperties();
    return Props;
}

const QVariantMap& heightProperties()
{
    static const QVariantMap Props = createHeightProperties();
    return Props;
}

const QVariantMap& hmslProperties()
{
    static const QVariantMap Props = createHmslProperties();
    return Props;
}

const QVariantMap& haccProperties()
{
    static const QVariantMap Props = createHaccProperties();
    return Props;
}

const QVariantMap& vaccProperties()
{
    static const QVariantMap Props = createVaccProperties();
    return Props;
}

const QVariantMap& eastProperties()
{
    static const QVariantMap Props = createEastProperties();
    return Props;
}

const QVariantMap& northProperties()
{
    static const QVariantMap Props = createNorthProperties();
    return Props;
}

const QVariantMap& altProperties()
{
    static const QVariantMap Props = createAltProperties();
    return Props;
}

const QVariantMap& zoneProperties()
{
    static const QVariantMap Props = createZoneProperties();
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
    static const QVariantMap Props = createTtffProperties();
    return Props;
}

const QVariantMap& msssProperties()
{
    static const QVariantMap Props = createMsssProperties();
    return Props;
}

const QVariantMap& fracProperties()
{
    static const QVariantMap Props = createFracProperties();
    return Props;
}

const QVariantMap& weekProperties()
{
    static const QVariantMap Props = createWeekProperties();
    return Props;
}

const QVariantMap& saccProperties()
{
    static const QVariantMap Props = createSaccProperties();
    return Props;
}

const QVariantMap& numSvProperties()
{
    static const QVariantMap Props = createNumSvProperties();
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
    static const QVariantMap Props = createSpeedProperties();
    return Props;
}

const QVariantMap& groundSpeedProperties()
{
    static const QVariantMap Props = createGroundSpeedProperties();
    return Props;
}

const QVariantMap& headingProperties()
{
    static const QVariantMap Props = createHeadingProperties();
    return Props;
}

const QVariantMap& caccProperties()
{
    static const QVariantMap Props = createCaccProperties();
    return Props;
}

}  // namespace nav

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox

