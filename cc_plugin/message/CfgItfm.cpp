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

#include <type_traits>
#include <functional>
#include <cassert>

#include "CfgItfm.h"
#include "cc_plugin/field/cfg.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgItfm<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgItfm<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgItfm>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_config()
{
    auto bbThresholdProps = cc::Property::createPropertiesMap("bbThreshold");
    cc::Property::setSerialisedHidden(bbThresholdProps);

    auto cwThresholdProps = cc::Property::createPropertiesMap("cwThreshold");
    cc::Property::setSerialisedHidden(cwThresholdProps);

    auto reserved1Props = cc::Property::createPropertiesMap("reserved1");
    cc::Property::setSerialisedHidden(reserved1Props);

    QVariantList bitNames;
    bitNames.append("enable");
    assert(bitNames.size() == ublox::message::CfgItfmFields::config_enable_numOfValues);
    auto enableProps = cc::Property::createPropertiesMap(QString(), std::move(bitNames));
    cc::Property::setSerialisedHidden(enableProps);

    QVariantList membersData;
    membersData.append(std::move(bbThresholdProps));
    membersData.append(std::move(cwThresholdProps));
    membersData.append(std::move(reserved1Props));
    membersData.append(std::move(enableProps));
    assert(membersData.size() == ublox::message::CfgItfmFields::config_numOfValues);
    return cc::Property::createPropertiesMap("config", std::move(membersData));
}

QVariantMap createProps_config2()
{
    auto reserved2Props = cc::Property::createPropertiesMap("reserved2");
    cc::Property::setSerialisedHidden(reserved2Props);

    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "unknown");
    cc::Property::appendEnumValue(enumValues, "passive");
    cc::Property::appendEnumValue(enumValues, "active");
    assert(enumValues.size() == (int)ublox::message::CfgItfmFields::AntSetting::NumOfValues);
    auto antSettingProps = cc::Property::createPropertiesMap("antSetting", std::move(enumValues));
    cc::Property::setSerialisedHidden(antSettingProps);

    auto reserved3Props = cc::Property::createPropertiesMap("reserved3");
    cc::Property::setSerialisedHidden(reserved3Props);

    QVariantList membersData;
    membersData.append(std::move(reserved2Props));
    membersData.append(std::move(antSettingProps));
    membersData.append(std::move(reserved3Props));
    assert(membersData.size() == ublox::message::CfgItfmFields::config2_numOfValues);
    return cc::Property::createPropertiesMap("config2", std::move(membersData));
}


QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_config());
    props.append(createProps_config2());

    assert(props.size() == CfgItfm::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgItfm::CfgItfm() = default;
CfgItfm::~CfgItfm() = default;

CfgItfm& CfgItfm::operator=(const CfgItfm&) = default;
CfgItfm& CfgItfm::operator=(CfgItfm&&) = default;


const char* CfgItfm::nameImpl() const
{
    static const char* Str = "CFG-ITFM";
    return Str;
}

const QVariantList& CfgItfm::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

