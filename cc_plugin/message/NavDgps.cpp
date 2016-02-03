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

#include "NavDgps.h"
#include "cc_plugin/field/nav.h"
#include "cc_plugin/field/common.h"

template class ublox::message::NavDgps<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavDgps<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavDgps>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_status()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "none");
    cc::Property::appendEnumValue(enumValues, "PR+PRR correction");
    assert(enumValues.size() == (int)ublox::message::NavDgpsFields::Status::NumOfValues);
    return cc::Property::createPropertiesMap("status", std::move(enumValues));
}

QVariantMap createProps_flags()
{
    auto channelProps = cc::Property::createPropertiesMap("channel");
    cc::Property::setSerialisedHidden(channelProps);

    QVariantList bitNames;
    bitNames.append("dgpsUsed");
    assert(bitNames.size() == ublox::message::NavDgpsFields::flagsBits_numOfValues);
    auto flagsProps = cc::Property::createPropertiesMap("flags", std::move(bitNames));
    cc::Property::setSerialisedHidden(flagsProps);

    QVariantList membersData;
    membersData.append(std::move(channelProps));
    membersData.append(std::move(flagsProps));
    assert(membersData.size() == ublox::message::NavDgpsFields::flags_numOfValues);
    return cc::Property::createPropertiesMap("flags", std::move(membersData));
}

QVariantMap createProps_data()
{
    QVariantList membersData;
    membersData.append(cc_plugin::field::nav::props_svid());
    membersData.append(createProps_flags());
    membersData.append(cc::Property::createPropertiesMap("ageC"));
    membersData.append(cc::Property::createPropertiesMap("prc"));
    membersData.append(cc::Property::createPropertiesMap("prrc"));
    assert(membersData.size() == ublox::message::NavDgpsFields::block_numOfValues);
    auto elementProps = cc::Property::createPropertiesMap("element", std::move(membersData));

    auto props = cc::Property::createPropertiesMap("data", std::move(elementProps));
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(cc::Property::createPropertiesMap("age"));
    props.append(cc::Property::createPropertiesMap("baseId"));
    props.append(cc::Property::createPropertiesMap("baseHealth"));
    props.append(cc_plugin::field::nav::props_numCh());
    props.append(createProps_status());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_data());

    assert(props.size() == NavDgps::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavDgps::NavDgps() = default;
NavDgps::~NavDgps() = default;

NavDgps& NavDgps::operator=(const NavDgps&) = default;
NavDgps& NavDgps::operator=(NavDgps&&) = default;

const char* NavDgps::nameImpl() const
{
    static const char* Str = "NAV-DGPS";
    return Str;
}

const QVariantList& NavDgps::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

