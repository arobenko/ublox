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

#include "CfgGnss.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgGnss<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgGnss<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgGnss>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_numConfigBlocks()
{
    auto props = cc::Property::createPropertiesMap("numConfigBlocks");
    cc::Property::setReadOnly(props);
    return props;
}

QVariantMap createProps_gnssId()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "GPS", (int)ublox::message::CfgGnssFields::GnssId::GPS);
    cc::Property::appendEnumValue(enumValues, "SBAS", (int)ublox::message::CfgGnssFields::GnssId::SBAS);
    cc::Property::appendEnumValue(enumValues, "QZSS", (int)ublox::message::CfgGnssFields::GnssId::QZSS);
    cc::Property::appendEnumValue(enumValues, "GLONASS", (int)ublox::message::CfgGnssFields::GnssId::GLONASS);
    return cc::Property::createPropertiesMap("gnssId", std::move(enumValues));
}

QVariantMap createProps_flags()
{
    QVariantList bitNames;
    bitNames.append("enable");
    assert(bitNames.size() == ublox::message::CfgGnssFields::flags_numOfValues);
    return cc::Property::createPropertiesMap("flags", std::move(bitNames));
}

QVariantMap createProps_data()
{
    QVariantList membersData;
    membersData.append(createProps_gnssId());
    membersData.append(cc::Property::createPropertiesMap("resTrkCh"));
    membersData.append(cc::Property::createPropertiesMap("maxTrkCh"));
    membersData.append(cc_plugin::field::common::props_reserved(1));
    membersData.append(createProps_flags());
    assert(membersData.size() == ublox::message::CfgGnssFields::block_numOfValues);

    auto elemProps = cc::Property::createPropertiesMap("element", std::move(membersData));
    auto props = cc::Property::createPropertiesMap("data", std::move(elemProps));
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::Property::createPropertiesMap("msgVer"));
    props.append(cc::Property::createPropertiesMap("numTrkChHw"));
    props.append(cc::Property::createPropertiesMap("numTrkChUse"));
    props.append(createProps_numConfigBlocks());
    props.append(createProps_data());
    assert(props.size() == CfgGnss::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgGnss::CfgGnss() = default;
CfgGnss::~CfgGnss() = default;

CfgGnss& CfgGnss::operator=(const CfgGnss&) = default;
CfgGnss& CfgGnss::operator=(CfgGnss&&) = default;


const char* CfgGnss::nameImpl() const
{
    static const char* Str = "CFG-GNSS";
    return Str;
}

const QVariantList& CfgGnss::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

