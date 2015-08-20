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

#include "CfgTm.h"
#include "cc_plugin/field/cfg.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgTm<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgTm<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgTm>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createIntIdProperties()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "EXTINT0", (int)ublox::message::CfgTmIntId::EXTINT0);
    cc::Property::appendEnumValue(enumValues, "EXTINT1", (int)ublox::message::CfgTmIntId::EXTINT1);
    cc::Property::appendEnumValue(enumValues, "EXTINT2", (int)ublox::message::CfgTmIntId::EXTINT2);

    return cc::Property::createPropertiesMap("INTID", std::move(enumValues));
}

QVariantMap createRateProperties()
{
    return cc::Property::createPropertiesMap("Rate");
}

QVariantMap createFlagsProperties()
{
    QVariantList enabledMaskBitNames;
    enabledMaskBitNames.append("enabled");
    auto enabledProps = cc::Property::createPropertiesMap("Flags", std::move(enabledMaskBitNames));
    cc::Property::setSerialisedHidden(enabledProps);

    QVariantList edgeEnumValues;
    cc::Property::appendEnumValue(edgeEnumValues, "Rising");
    cc::Property::appendEnumValue(edgeEnumValues, "Falling");
    auto edgeProps = cc::Property::createPropertiesMap("Edge", std::move(edgeEnumValues));
    cc::Property::setSerialisedHidden(edgeProps);

    QVariantList timebaseEnumValues;
    cc::Property::appendEnumValue(timebaseEnumValues, "GPS");
    cc::Property::appendEnumValue(timebaseEnumValues, "UTC");
    auto timebaseProps = cc::Property::createPropertiesMap("Timebase", std::move(timebaseEnumValues));
    cc::Property::setSerialisedHidden(timebaseProps);

    QVariantMap reservedProps;
    cc::Property::setFieldHidden(reservedProps);

    QVariantList memberProps;
    memberProps.append(std::move(enabledProps));
    memberProps.append(std::move(edgeProps));
    memberProps.append(std::move(timebaseProps));
    memberProps.append(std::move(reservedProps));

    return cc::Property::createPropertiesMap("Flags", std::move(memberProps));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createIntIdProperties());
    props.append(createRateProperties());
    props.append(createFlagsProperties());

    assert(props.size() == CfgTm::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

CfgTm::CfgTm() = default;
CfgTm::~CfgTm() = default;

CfgTm& CfgTm::operator=(const CfgTm&) = default;
CfgTm& CfgTm::operator=(CfgTm&&) = default;


const char* CfgTm::nameImpl() const
{
    static const char* Str = "CFG-TM";
    return Str;
}

const QVariantList& CfgTm::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

