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

#include "NavSvinfo.h"

#include <cassert>

#include "cc_plugin/field/nav.h"
#include "cc_plugin/field/common.h"

template class ublox::message::NavSvinfo<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavSvinfo<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavSvinfo>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_globalFlags()
{
    QVariantList chipGenValues;
    cc::Property::appendEnumValue(chipGenValues, "Antaris");
    cc::Property::appendEnumValue(chipGenValues, "ublox-5");
    cc::Property::appendEnumValue(chipGenValues, "ublox-6");
    assert(chipGenValues.size() == (int)ublox::message::NavSvinfo_ChipGen::NumOfValues);
    auto chipGenProps = cc::Property::createPropertiesMap("chipGen", std::move(chipGenValues));
    cc::Property::setSerialisedHidden(chipGenProps);

    auto reservedProps = cc::Property::createPropertiesMap("reserved");
    cc::Property::setFieldHidden(reservedProps);

    QVariantList membersData;
    membersData.append(std::move(chipGenProps));
    membersData.append(std::move(reservedProps));
    assert(membersData.size() == ublox::message::NavSvinfoField_globalFlags_numOfValues);
    return cc::Property::createPropertiesMap("globalFlags", std::move(membersData));
}

QVariantMap createProps_flags()
{
    QVariantList bitNames;
    bitNames.append("svUsed");
    bitNames.append("diffCorr");
    bitNames.append("orbitAvail");
    bitNames.append("orbitEph");
    bitNames.append("unhealthy");
    bitNames.append("orbitAlm");
    bitNames.append("orbitAop");
    bitNames.append("smoothed");
    return cc::Property::createPropertiesMap("flags", std::move(bitNames));
}

QVariantMap createProps_quality()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "Idle");
    cc::Property::appendEnumValue(enumValues, "Searching");
    cc::Property::appendEnumValue(enumValues, "Signal acquired");
    cc::Property::appendEnumValue(enumValues, "Signal unusable");
    cc::Property::appendEnumValue(enumValues, "Code Lock");
    cc::Property::appendEnumValue(enumValues, "Code and Carrier Locked");
    cc::Property::appendEnumValue(enumValues, "Code and Carrier Locked");
    cc::Property::appendEnumValue(enumValues, "Code and Carrier Locked");
    return cc::Property::createPropertiesMap("quality", std::move(enumValues));
}


QVariantMap createProps_info()
{
    QVariantList membersData;
    membersData.append(cc::Property::createPropertiesMap("chn"));
    membersData.append(cc_plugin::field::nav::props_svid());
    membersData.append(createProps_flags());
    membersData.append(createProps_quality());
    membersData.append(cc::Property::createPropertiesMap("cno"));
    membersData.append(cc::Property::createPropertiesMap("elev"));
    membersData.append(cc::Property::createPropertiesMap("azim"));
    membersData.append(cc::Property::createPropertiesMap("prRes"));
    assert(membersData.size() == ublox::message::NavSvinfoField_info_numOfValues);

    QVariantMap bundleProps;
    cc::Property::setData(bundleProps, std::move(membersData));

    auto props = cc::Property::createPropertiesMap("info", std::move(bundleProps));
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(cc_plugin::field::nav::props_numCh());
    props.append(createProps_globalFlags());
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(createProps_info());

    assert(props.size() == NavSvinfo::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavSvinfo::NavSvinfo() = default;
NavSvinfo::~NavSvinfo() = default;

NavSvinfo& NavSvinfo::operator=(const NavSvinfo&) = default;
NavSvinfo& NavSvinfo::operator=(NavSvinfo&&) = default;

const char* NavSvinfo::nameImpl() const
{
    static const char* Str = "NAV-SVINFO";
    return Str;
}

const QVariantList& NavSvinfo::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

