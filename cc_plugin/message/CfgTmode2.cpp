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

#include <cassert>

#include "CfgTmode2.h"

#include "cc_plugin/field/common.h"

template class ublox::message::CfgTmode2<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgTmode2<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgTmode2>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_timeMode()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "Disabled");
    cc::Property::appendEnumValue(enumValues, "Survey In");
    cc::Property::appendEnumValue(enumValues, "Fixed Mode");
    assert(enumValues.size() == (int)ublox::message::CfgTmode2_TimeMode::NumOfValues);
    return cc::Property::createPropertiesMap("timeMode", std::move(enumValues));
}

QVariantMap createProps_flags()
{
    QVariantList bitNames;
    bitNames.append("lla");
    bitNames.append("altInv");
    assert(bitNames.size() == ublox::message::CfgTmode2Field_flags_numOfValues);
    return cc::Property::createPropertiesMap("flags", std::move(bitNames));
}

QVariantMap createProps_cartesian(char coord)
{
    auto name = QString("ecef%1").arg(coord);
    auto valProps = cc::Property::createPropertiesMap(name);
    auto props = cc::Property::createPropertiesMap(name, std::move(valProps));
    cc::Property::setUncheckable(props);
    return props;
}

QVariantMap createProps_geodetic(const char* name, int scaledDigits = 0)
{
    auto valProps = cc::Property::createPropertiesMap(name);
    if (0 < scaledDigits) {
        cc::Property::setDisplayScaled(valProps);
        cc::Property::setFloatDecimals(valProps, scaledDigits);
    }

    auto props = cc::Property::createPropertiesMap(name, std::move(valProps));
    cc::Property::setUncheckable(props);
    return props;
}


QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_timeMode());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_flags());
    props.append(createProps_cartesian('X'));
    props.append(createProps_geodetic("lat", 7));
    props.append(createProps_cartesian('Y'));
    props.append(createProps_geodetic("lon", 7));
    props.append(createProps_cartesian('Z'));
    props.append(createProps_geodetic("alt"));
    props.append(cc::Property::createPropertiesMap("fixedPosAcc"));
    props.append(cc::Property::createPropertiesMap("svinMinDur"));
    props.append(cc::Property::createPropertiesMap("svinAccLimit"));

    assert(props.size() == CfgTmode2::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgTmode2::CfgTmode2() = default;
CfgTmode2::~CfgTmode2() = default;

CfgTmode2& CfgTmode2::operator=(const CfgTmode2&) = default;
CfgTmode2& CfgTmode2::operator=(CfgTmode2&&) = default;


const char* CfgTmode2::nameImpl() const
{
    static const char* Str = "CFG-TMODE2";
    return Str;
}

const QVariantList& CfgTmode2::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

