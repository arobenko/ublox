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

#include "CfgTp.h"
#include "cc_plugin/field/cfg.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgTp<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgTp<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgTp>;

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
    cc::Property::appendEnumValue(enumValues, "negative", (int)ublox::message::CfgTpFields::Status::Negative);
    cc::Property::appendEnumValue(enumValues, "off", (int)ublox::message::CfgTpFields::Status::Off);
    cc::Property::appendEnumValue(enumValues, "positive", (int)ublox::message::CfgTpFields::Status::Positive);
    return cc::Property::createPropertiesMap("status", std::move(enumValues));
}

QVariantMap createProps_timeRef()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "UTC time");
    cc::Property::appendEnumValue(enumValues, "GPS time");
    cc::Property::appendEnumValue(enumValues, "Local time");
    assert(enumValues.size() == (int)ublox::message::CfgTpFields::TimeRef::NumOfValues);
    return cc::Property::createPropertiesMap("timeRef", std::move(enumValues));
}

QVariantMap createProps_flags()
{
    QVariantList bitNames;
    bitNames.append("syncMode");
    assert(bitNames.size() == ublox::message::CfgTpFields::flags_numOfValues);
    return cc::Property::createPropertiesMap("flags", std::move(bitNames));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::Property::createPropertiesMap("interval"));
    props.append(cc::Property::createPropertiesMap("length"));
    props.append(createProps_status());
    props.append(createProps_timeRef());
    props.append(createProps_flags());
    props.append(cc_plugin::field::common::props_reserved(0));
    props.append(cc::Property::createPropertiesMap("antennaCableDelay"));
    props.append(cc::Property::createPropertiesMap("rfGroupDelay"));
    props.append(cc::Property::createPropertiesMap("userDelay"));

    assert(props.size() == CfgTp::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgTp::CfgTp() = default;
CfgTp::~CfgTp() = default;

CfgTp& CfgTp::operator=(const CfgTp&) = default;
CfgTp& CfgTp::operator=(CfgTp&&) = default;


const char* CfgTp::nameImpl() const
{
    static const char* Str = "CFG-TP";
    return Str;
}

const QVariantList& CfgTp::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

