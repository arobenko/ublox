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

#include "CfgPm2.h"

#include "cc_plugin/field/common.h"

template class ublox::message::CfgPm2<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgPm2<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgPm2>;

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

    auto createSingleBitMask =
        [](const QString& name) -> QVariantMap
        {
            QVariantList bits;
            bits.append(name);
            auto props = cc::Property::createPropertiesMap(QString(), std::move(bits));
            cc::Property::setSerialisedHidden(props);
            return props;
        };

    QVariantList extintSelectValues;
    cc::Property::appendEnumValue(extintSelectValues, "EXTINT0");
    cc::Property::appendEnumValue(extintSelectValues, "EXTINT1");
    assert(extintSelectValues.size() == (int)ublox::message::CfgPm2Fields::ExtintSelect::NumOfValues);
    auto extintSelectProps = cc::Property::createPropertiesMap("extintSelect", std::move(extintSelectValues));
    cc::Property::setSerialisedHidden(extintSelectProps);

    auto createEnableDisableProps =
        [](const char* name) -> QVariantMap
        {
            QVariantList enumValues;
            cc::Property::appendEnumValue(enumValues, "disabled");
            cc::Property::appendEnumValue(enumValues, "enabled");
            assert(enumValues.size() == (int)ublox::message::CfgPm2Fields::DisabledEnabled::NumOfValues);
            auto props = cc::Property::createPropertiesMap(name, std::move(enumValues));
            cc::Property::setSerialisedHidden(props);
            return props;
        };

    QVariantList modeEnumValues;
    cc::Property::appendEnumValue(modeEnumValues, "ON/OFF");
    cc::Property::appendEnumValue(modeEnumValues, "Cyclic tracking");
    assert(modeEnumValues.size() == (int)ublox::message::CfgPm2Fields::Mode::NumOfValues);
    auto modeProps = cc::Property::createPropertiesMap("mode", std::move(modeEnumValues));
    cc::Property::setSerialisedHidden(modeProps);

    QVariantList membersData;
    membersData.append(createReservedProps());
    membersData.append(std::move(extintSelectProps));
    membersData.append(createEnableDisableProps("extintWake"));
    membersData.append(createEnableDisableProps("extintBackup"));
    membersData.append(createReservedProps());
    membersData.append(createEnableDisableProps("limitPeakCurr"));
    membersData.append(createSingleBitMask("waitTimeFix"));
    membersData.append(createSingleBitMask("updateRTC"));
    membersData.append(createSingleBitMask("updateEPH"));
    membersData.append(createReservedProps());
    membersData.append(createSingleBitMask("doNotEnterOff"));
    membersData.append(std::move(modeProps));
    membersData.append(createReservedProps());
    assert(membersData.size() == ublox::message::CfgPm2Fields::flags_numOfValues);
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
    props.append(cc_plugin::field::common::props_reserved(4));
    props.append(cc_plugin::field::common::props_reserved(5));
    props.append(cc_plugin::field::common::props_reserved(6));
    props.append(cc_plugin::field::common::props_reserved(7));
    props.append(cc_plugin::field::common::props_reserved(8));
    props.append(cc_plugin::field::common::props_reserved(9));
    props.append(cc_plugin::field::common::props_reserved(10));
    props.append(cc_plugin::field::common::props_reserved(11));
    assert(props.size() == CfgPm2::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgPm2::CfgPm2() = default;
CfgPm2::~CfgPm2() = default;

CfgPm2& CfgPm2::operator=(const CfgPm2&) = default;
CfgPm2& CfgPm2::operator=(CfgPm2&&) = default;


const char* CfgPm2::nameImpl() const
{
    static const char* Str = "CFG-PM2";
    return Str;
}

const QVariantList& CfgPm2::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

