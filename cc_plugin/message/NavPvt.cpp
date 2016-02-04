//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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

#include "NavPvt.h"
#include "cc_plugin/field/common.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavPvt<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavPvt<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavPvt>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_valid()
{
    QVariantList bitNames;
    bitNames.append("validDate");
    bitNames.append("validTime");
    bitNames.append("fullyResolved");
    assert(bitNames.size() == ublox::message::NavPvtFields::valid_numOfValues);

    return cc::Property::createPropertiesMap("valid", std::move(bitNames));
}

QVariantMap createProps_fixType()
{
    auto props = cc_plugin::field::nav::props_gpsFix();
    cc::Property::setName(props, "fixType");
    return props;
}

QVariantMap createProps_flags()
{
    QVariantList bitNames;
    bitNames.append("gnssFixOK");
    bitNames.append("diffSoln");
    assert(bitNames.size() == ublox::message::NavPvtFields::flagsBits_numOfValues);
    auto flagsProps = cc::Property::createPropertiesMap("flags", std::move(bitNames));
    cc::Property::setSerialisedHidden(flagsProps);

    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "n/a");
    cc::Property::appendEnumValue(enumValues, "ENABLED");
    cc::Property::appendEnumValue(enumValues, "ACQUISITION");
    cc::Property::appendEnumValue(enumValues, "TRACKING");
    cc::Property::appendEnumValue(enumValues, "POWER OPTIMIZED TRACKING");
    cc::Property::appendEnumValue(enumValues, "INACTIVE");
    assert(enumValues.size() == (int)ublox::message::NavPvtFields::PsmState::NumOfValues);
    auto psmStateProps = cc::Property::createPropertiesMap("psmState", std::move(enumValues));
    cc::Property::setSerialisedHidden(psmStateProps);

    QVariantList membersProps;
    membersProps.append(std::move(flagsProps));
    membersProps.append(std::move(psmStateProps));
    assert(membersProps.size() == (int)ublox::message::NavPvtFields::flags_numOfValues);

    return cc::Property::createPropertiesMap("flags", std::move(membersProps));
}

QVariantMap createProps_headingAcc()
{
    auto props = cc::Property::createPropertiesMap("headingAcc");
    cc::Property::setDisplayScaled(props);
    cc::Property::setFloatDecimals(props, 5);
    return props;
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(cc_plugin::field::nav::props_year());
    props.append(cc_plugin::field::nav::props_month());
    props.append(cc_plugin::field::nav::props_day());
    props.append(cc_plugin::field::nav::props_hour());
    props.append(cc_plugin::field::nav::props_min());
    props.append(cc_plugin::field::nav::props_sec());
    props.append(createProps_valid());
    props.append(cc_plugin::field::nav::props_tAcc());
    props.append(cc_plugin::field::nav::props_nano());
    props.append(createProps_fixType());
    props.append(createProps_flags());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc_plugin::field::nav::props_numSV());
    props.append(cc_plugin::field::nav::props_lon());
    props.append(cc_plugin::field::nav::props_lat());
    props.append(cc_plugin::field::nav::props_height());
    props.append(cc_plugin::field::nav::props_hMSL());
    props.append(cc_plugin::field::nav::props_hAcc());
    props.append(cc_plugin::field::nav::props_vAcc());
    props.append(cc_plugin::field::nav::props_velN());
    props.append(cc_plugin::field::nav::props_velE());
    props.append(cc_plugin::field::nav::props_velD());
    props.append(cc_plugin::field::nav::props_gSpeed());
    props.append(cc_plugin::field::nav::props_heading());
    props.append(cc_plugin::field::nav::props_sAcc());
    props.append(createProps_headingAcc());
    props.append(cc_plugin::field::nav::props_pDOP());
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(cc_plugin::field::common::props_reserved(3));

    assert(props.size() == NavPvt::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavPvt::NavPvt() = default;
NavPvt::~NavPvt() = default;

NavPvt& NavPvt::operator=(const NavPvt&) = default;
NavPvt& NavPvt::operator=(NavPvt&&) = default;

const char* NavPvt::nameImpl() const
{
    static const char* Str = "NAV-PVT";
    return Str;
}

const QVariantList& NavPvt::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

