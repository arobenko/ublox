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

#include "CfgPm.h"

#include "cc_plugin/field/common.h"

template class ublox::message::CfgPm<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgPm<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgPm>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_flags()
{
    auto createReservedProps =
        []() -> QVariantMap
        {
            auto props = cc::Property::createPropertiesMap("reserved");
            cc::Property::setFieldHidden(props);
            return props;
        };

    auto internalProps = cc::Property::createPropertiesMap("internal");
    cc::Property::setSerialisedHidden(internalProps);

    QVariantList extintSelectValues;
    cc::Property::appendEnumValue(extintSelectValues, "EXTINT0");
    cc::Property::appendEnumValue(extintSelectValues, "EXTINT1");
    assert(extintSelectValues.size() == (int)ublox::message::CfgPm_ExtintSelect::NumOfValues);
    auto extintSelectProps = cc::Property::createPropertiesMap("extintSelect", std::move(extintSelectValues));
    cc::Property::setSerialisedHidden(extintSelectProps);

    auto createEnableDisableProps =
        [](const char* name) -> QVariantMap
        {
            QVariantList enumValues;
            cc::Property::appendEnumValue(enumValues, "disabled");
            cc::Property::appendEnumValue(enumValues, "enabled");
            assert(enumValues.size() == (int)ublox::message::CfgPm_DisabledEnabled::NumOfValues);
            auto props = cc::Property::createPropertiesMap(name, std::move(enumValues));
            cc::Property::setSerialisedHidden(props);
            return props;
        };

    QVariantList flagsBitNames;
    flagsBitNames.append("waitTimeFix");
    flagsBitNames.append("updateRtc");
    flagsBitNames.append("updateEPH");
    assert(flagsBitNames.size() == ublox::message::CfgPmField_flags_flags_numOfValues);
    auto flagsProps = cc::Property::createPropertiesMap(QString(), std::move(flagsBitNames));
    cc::Property::setSerialisedHidden(flagsProps);

    QVariantList membersData;
    membersData.append(createReservedProps());
    membersData.append(std::move(internalProps));
    membersData.append(std::move(extintSelectProps));
    membersData.append(createEnableDisableProps("extintWake"));
    membersData.append(createEnableDisableProps("extintBackup"));
    membersData.append(createReservedProps());
    membersData.append(createEnableDisableProps("limitPeakCurr"));
    membersData.append(std::move(flagsProps));
    assert(membersData.size() == ublox::message::CfgPmField_flags_numOfValues);
    return cc::Property::createPropertiesMap("flags", std::move(membersData));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::Property::createPropertiesMap("version"));
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(cc_plugin::field::common::props_reserved(3));
    props.append(createProps_flags());
    props.append(cc::Property::createPropertiesMap("updatePeriod"));
    props.append(cc::Property::createPropertiesMap("searchPeriod"));
    props.append(cc::Property::createPropertiesMap("gridOffset"));
    props.append(cc::Property::createPropertiesMap("onTime"));
    props.append(cc::Property::createPropertiesMap("minAcqTime"));
    assert(props.size() == CfgPm::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgPm::CfgPm() = default;
CfgPm::~CfgPm() = default;

CfgPm& CfgPm::operator=(const CfgPm&) = default;
CfgPm& CfgPm::operator=(CfgPm&&) = default;


const char* CfgPm::nameImpl() const
{
    static const char* Str = "CFG-PM";
    return Str;
}

const QVariantList& CfgPm::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

