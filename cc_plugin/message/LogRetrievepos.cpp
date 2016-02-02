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

#include "LogRetrievepos.h"
#include "cc_plugin/field/common.h"

template class ublox::message::LogRetrievepos<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::LogRetrievepos<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::LogRetrievepos>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_latLong(const char* name)
{
    auto props = cc::Property::createPropertiesMap(name);
    cc::Property::setDisplayScaled(props);
    cc::Property::setFloatDecimals(props, 7);
    return props;
}

QVariantMap createProps_fixType()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "2D-Fix", (int)ublox::message::LogRetrieveposFields::FixType::Fix_2D);
    cc::Property::appendEnumValue(enumValues, "3D-Fix", (int)ublox::message::LogRetrieveposFields::FixType::Fix_3D);
    return cc::Property::createPropertiesMap("fixType", std::move(enumValues));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::Property::createPropertiesMap("entryIdx"));
    props.append(createProps_latLong("lon"));
    props.append(createProps_latLong("lat"));
    props.append(cc::Property::createPropertiesMap("hMSL"));
    props.append(cc::Property::createPropertiesMap("hAcc"));
    props.append(cc::Property::createPropertiesMap("gSpeed"));
    props.append(cc::Property::createPropertiesMap("heading"));
    props.append(cc::Property::createPropertiesMap("version"));
    props.append(createProps_fixType());
    props.append(cc::Property::createPropertiesMap("year"));
    props.append(cc::Property::createPropertiesMap("month"));
    props.append(cc::Property::createPropertiesMap("day"));
    props.append(cc::Property::createPropertiesMap("hour"));
    props.append(cc::Property::createPropertiesMap("minute"));
    props.append(cc::Property::createPropertiesMap("second"));
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc::Property::createPropertiesMap("numSV"));
    props.append(cc_plugin::field::common::props_reserved(2));
    assert(props.size() == LogRetrievepos::FieldIdx_numOfValues);
    return props;
}

}  // namespace

LogRetrievepos::LogRetrievepos() = default;
LogRetrievepos::~LogRetrievepos() = default;

LogRetrievepos& LogRetrievepos::operator=(const LogRetrievepos&) = default;
LogRetrievepos& LogRetrievepos::operator=(LogRetrievepos&&) = default;

const char* LogRetrievepos::nameImpl() const
{
    static const char* Str = "LOG-RETRIEVEPOS";
    return Str;
}

const QVariantList& LogRetrievepos::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

