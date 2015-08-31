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

#include "NavSbas.h"
#include "cc_plugin/field/nav.h"
#include "cc_plugin/field/common.h"

template class ublox::message::NavSbas<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavSbas<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavSbas>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_mode()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "Disabled", (int)ublox::message::NavSbas_Mode::Disabled);
    cc::Property::appendEnumValue(enumValues, "Enabed Integrity", (int)ublox::message::NavSbas_Mode::EnabledIntegrity);
    cc::Property::appendEnumValue(enumValues, "Enabed Testmode", (int)ublox::message::NavSbas_Mode::EnabledTestmode);

    return cc::Property::createPropertiesMap("mode", std::move(enumValues));
}

QVariantMap createProps_sys(const QString& name)
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "Unknown", (int)ublox::message::NavSbas_Sys::Unknown);
    cc::Property::appendEnumValue(enumValues, "WAAS", (int)ublox::message::NavSbas_Sys::WAAS);
    cc::Property::appendEnumValue(enumValues, "EGNOS", (int)ublox::message::NavSbas_Sys::EGNOS);
    cc::Property::appendEnumValue(enumValues, "MSAS", (int)ublox::message::NavSbas_Sys::MSAS);
    cc::Property::appendEnumValue(enumValues, "GPS", (int)ublox::message::NavSbas_Sys::GPS);

    return cc::Property::createPropertiesMap(name, std::move(enumValues));
}

QVariantMap createProps_service(const QString& name)
{
    QVariantList bitNames;
    bitNames.append("Ranging");
    bitNames.append("Corrections");
    bitNames.append("Integrity");
    bitNames.append("Testmode");

    return cc::Property::createPropertiesMap(name, std::move(bitNames));
}

QVariantMap createProps_cnt()
{
    auto props = cc_plugin::field::nav::props_numCh();
    cc::Property::setName(props, "cnt");
    return props;
}

QVariantMap createProps_data()
{
    QVariantList membersData;
    membersData.append(cc_plugin::field::nav::props_svid());
    membersData.append(cc::Property::createPropertiesMap("flags"));
    membersData.append(cc::Property::createPropertiesMap("udre"));
    membersData.append(createProps_sys("svSys"));
    membersData.append(createProps_service("svService"));
    membersData.append(cc_plugin::field::common::props_reserved(1));
    membersData.append(cc::Property::createPropertiesMap("prc"));
    membersData.append(cc_plugin::field::common::props_reserved(2));
    membersData.append(cc::Property::createPropertiesMap("ic"));

    auto elementProps = cc::Property::createPropertiesMap("element", std::move(membersData));

    auto props = cc::Property::createPropertiesMap("data", std::move(elementProps));
    cc::Property::setSerialisedHidden(props);
    return props;
}


QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(cc::Property::createPropertiesMap("geo"));
    props.append(createProps_mode());
    props.append(createProps_sys("sys"));
    props.append(createProps_service("service"));
    props.append(createProps_cnt());
    props.append(cc_plugin::field::common::props_reserved(0));
    props.append(createProps_data());

    assert(props.size() == NavSbas::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavSbas::NavSbas() = default;
NavSbas::~NavSbas() = default;

NavSbas& NavSbas::operator=(const NavSbas&) = default;
NavSbas& NavSbas::operator=(NavSbas&&) = default;


const char* NavSbas::nameImpl() const
{
    static const char* Str = "NAV-SBAS";
    return Str;
}

const QVariantList& NavSbas::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

