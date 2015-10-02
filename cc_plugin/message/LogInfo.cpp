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

#include "LogInfo.h"
#include "cc_plugin/field/common.h"

template class ublox::message::LogInfo<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::LogInfo<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::LogInfo>;

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
    QVariantList bitNames;
    bitNames.append(QVariant());
    bitNames.append(QVariant());
    bitNames.append(QVariant());
    bitNames.append("recording");
    bitNames.append("inactive");
    bitNames.append("circular");
    return cc::Property::createPropertiesMap("status", std::move(bitNames));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::Property::createPropertiesMap("version"));
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc::Property::createPropertiesMap("filestoreCapacity"));
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(cc_plugin::field::common::props_reserved(3));
    props.append(cc::Property::createPropertiesMap("currentMaxLogSize"));
    props.append(cc::Property::createPropertiesMap("currentLogSize"));
    props.append(cc::Property::createPropertiesMap("entryCount"));
    props.append(cc::Property::createPropertiesMap("oldestYear"));
    props.append(cc::Property::createPropertiesMap("oldestMonth"));
    props.append(cc::Property::createPropertiesMap("oldestDay"));
    props.append(cc::Property::createPropertiesMap("oldestHour"));
    props.append(cc::Property::createPropertiesMap("oldestMinute"));
    props.append(cc::Property::createPropertiesMap("oldestSecond"));
    props.append(cc_plugin::field::common::props_reserved(4));
    props.append(cc::Property::createPropertiesMap("newestYear"));
    props.append(cc::Property::createPropertiesMap("newestMonth"));
    props.append(cc::Property::createPropertiesMap("newestDay"));
    props.append(cc::Property::createPropertiesMap("newestHour"));
    props.append(cc::Property::createPropertiesMap("newestMinute"));
    props.append(cc::Property::createPropertiesMap("newestSecond"));
    props.append(cc_plugin::field::common::props_reserved(5));
    props.append(createProps_status());
    props.append(cc_plugin::field::common::props_reserved(6));

    assert(props.size() == LogInfo::FieldIdx_numOfValues);
    return props;
}

}  // namespace

LogInfo::LogInfo() = default;
LogInfo::~LogInfo() = default;

LogInfo& LogInfo::operator=(const LogInfo&) = default;
LogInfo& LogInfo::operator=(LogInfo&&) = default;

const char* LogInfo::nameImpl() const
{
    static const char* Str = "LOG-INFO";
    return Str;
}

const QVariantList& LogInfo::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

