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

QVariantMap createNameOnlyProperties(const char* name)
{
    return cc::Property::createPropertiesMap(name);
}

QVariantMap createNsvProperties()
{
    auto props = cc::Property::createPropertiesMap("NSV");
    cc::Property::setReadOnly(props);
    return props;
}

QVariantMap createNumSvProperties()
{
    auto props = cc::Property::createPropertiesMap("NumSv");
    cc::Property::setReadOnly(props);
    return props;
}

QVariantMap createStatusInfoSvFlagProperties()
{
    auto uraProps = createNameOnlyProperties("URA");
    cc::Property::setSerialisedHidden(uraProps);

    QVariantList bitNames;
    bitNames.append("SV healthy");
    bitNames.append("Ephemeris valid");
    bitNames.append("Almanach valid");
    bitNames.append("SV not available");

    auto flagProps = cc::Property::createPropertiesMap("Flags", std::move(bitNames));
    cc::Property::setSerialisedHidden(flagProps);

    QVariantList members;
    members.append(std::move(uraProps));
    members.append(std::move(flagProps));

    QVariantMap props;
    cc::Property::setData(props, std::move(members));
    return props;
}

QVariantMap createAgeProperties()
{
    auto almAgeProps = createNameOnlyProperties("Alm. Age");
    cc::Property::setSerialisedHidden(almAgeProps);
    auto ephAgeProps = createNameOnlyProperties("Eph. Age");
    cc::Property::setSerialisedHidden(ephAgeProps);

    QVariantList members;
    members.append(std::move(almAgeProps));
    members.append(std::move(ephAgeProps));

    QVariantMap props;
    cc::Property::setData(props, std::move(members));
    return props;
}


}  // namespace

const QVariantMap& itowProperties()
{
    return common::itowProperties();
}

const QVariantMap& weekProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Week");
    return Props;
}

const QVariantMap& nsvProperties()
{
    static const QVariantMap Props = createNsvProperties();
    return Props;
}

const QVariantMap& cpMesProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("CPMes");
    return Props;
}

const QVariantMap& prMesProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("PRMes");
    return Props;
}

const QVariantMap& doMesProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("DOMes");
    return Props;
}

const QVariantMap& svProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("SV");
    return Props;
}

const QVariantMap& mesQiProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("MesQI");
    return Props;
}

const QVariantMap& cnoProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("CNO");
    return Props;
}

const QVariantMap& lliProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("LLI");
    return Props;
}

const QVariantMap& numVisProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("NumVis");
    return Props;
}

const QVariantMap& numSvProperties()
{
    static const QVariantMap Props = createNumSvProperties();
    return Props;
}

const QVariantMap& svidProperties()
{
    return common::svidProperties();
}

const QVariantMap& statusInfoSvFlagProperties()
{
    static const QVariantMap Props = createStatusInfoSvFlagProperties();
    return Props;
}

const QVariantMap& azimProperties()
{
    return common::azimProperties();
}

const QVariantMap& elevProperties()
{
    return common::elevProperties();
}

const QVariantMap& ageProperties()
{
    static const auto Props = createAgeProperties();
    return Props;
}

const QVariantMap& chnProperties()
{
    static const auto Props = createNameOnlyProperties("CHN");
    return Props;
}

const QVariantMap& dwordProperties()
{
    static const auto Props = createNameOnlyProperties("DWORD");
    return Props;
}

}  // namespace rxm

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox




