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

#include "CfgNmeaExt.h"
#include "cc_plugin/field/common.h"
#include "cc_plugin/field/cfg.h"

template class ublox::message::CfgNmeaExt<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgNmeaExt<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgNmeaExt>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_gnssToFilter()
{
    QVariantList bitNames;
    bitNames.append("gps");
    bitNames.append("sbas");
    bitNames.append(QVariant());
    bitNames.append(QVariant());
    bitNames.append("qzss");
    bitNames.append("qlonass");
    assert(bitNames.size() == ublox::message::CfgNmeaField_gnssToFilter_numOfValues);
    return cc::Property::createPropertiesMap("gnssToFilter", std::move(bitNames));
}

QVariantMap createProps_svNumbering()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "Strict");
    cc::Property::appendEnumValue(enumValues, "Extended");
    assert(enumValues.size() == (int)ublox::message::CfgNmea_SvNumbering::NumOfValues);
    return cc::Property::createPropertiesMap("svNumbering", std::move(enumValues));
}

QVariantMap createProps_mainTalkerId()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "Not overridden");
    cc::Property::appendEnumValue(enumValues, "GP");
    cc::Property::appendEnumValue(enumValues, "GL");
    cc::Property::appendEnumValue(enumValues, "GN");
    assert(enumValues.size() == (int)ublox::message::CfgNmea_MainTalkerId::NumOfValues);
    return cc::Property::createPropertiesMap("mainTalkerId", std::move(enumValues));
}

QVariantMap createProps_gsvTalkerId()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "GNSS Specific");
    cc::Property::appendEnumValue(enumValues, "Main");
    assert(enumValues.size() == (int)ublox::message::CfgNmea_GsvTalkerId::NumOfValues);
    return cc::Property::createPropertiesMap("gsvTalkerId", std::move(enumValues));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::cfg::props_nmeaFilter());
    props.append(cc_plugin::field::cfg::props_nmeaVersion());
    props.append(cc_plugin::field::cfg::props_nmeaNumSV());
    props.append(cc_plugin::field::cfg::props_nmeaFlags());
    props.append(createProps_gnssToFilter());
    props.append(createProps_svNumbering());
    props.append(createProps_mainTalkerId());
    props.append(createProps_gsvTalkerId());
    props.append(cc_plugin::field::common::props_reserved(0));
    assert(props.size() == CfgNmeaExt::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgNmeaExt::CfgNmeaExt() = default;
CfgNmeaExt::~CfgNmeaExt() = default;

CfgNmeaExt& CfgNmeaExt::operator=(const CfgNmeaExt&) = default;
CfgNmeaExt& CfgNmeaExt::operator=(CfgNmeaExt&&) = default;


const char* CfgNmeaExt::nameImpl() const
{
    static const char* Str = "CFG-NMEA (Extended)";
    return Str;
}

const QVariantList& CfgNmeaExt::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

