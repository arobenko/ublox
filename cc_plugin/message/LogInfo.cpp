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

using ublox::message::LogInfoFields;

QVariantMap createProps_status()
{
    cc::property::field::ForField<LogInfoFields::status> props;
    props.name("status")
         .add(LogInfoFields::status_recording, "recording")
         .add("inactive")
         .add("circular");
    assert(props.bits().size() == LogInfoFields::status_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<LogInfoFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<LogInfoFields::filestoreCapacity>().name("filestoreCapacity").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(cc_plugin::field::common::props_reserved(3));
    props.append(
        cc::property::field::ForField<LogInfoFields::currentMaxLogSize>().name("currentMaxLogSize").asMap());
    props.append(
        cc::property::field::ForField<LogInfoFields::currentLogSize>().name("currentLogSize").asMap());
    props.append(
        cc::property::field::ForField<LogInfoFields::entryCount>().name("entryCount").asMap());
    props.append(
        cc::property::field::ForField<LogInfoFields::oldestYear>().name("oldestYear").asMap());
    props.append(
        cc::property::field::ForField<LogInfoFields::oldestMonth>().name("oldestMonth").asMap());
    props.append(
        cc::property::field::ForField<LogInfoFields::oldestDay>().name("oldestDay").asMap());
    props.append(
        cc::property::field::ForField<LogInfoFields::oldestHour>().name("oldestHour").asMap());
    props.append(
        cc::property::field::ForField<LogInfoFields::oldestMinute>().name("oldestMinute").asMap());
    props.append(
        cc::property::field::ForField<LogInfoFields::oldestSecond>().name("oldestSecond").asMap());
    props.append(cc_plugin::field::common::props_reserved(4));
    props.append(
        cc::property::field::ForField<LogInfoFields::newestYear>().name("newestYear").asMap());
    props.append(
        cc::property::field::ForField<LogInfoFields::newestMonth>().name("newestMonth").asMap());
    props.append(
        cc::property::field::ForField<LogInfoFields::newestDay>().name("newestDay").asMap());
    props.append(
        cc::property::field::ForField<LogInfoFields::newestHour>().name("newestHour").asMap());
    props.append(
        cc::property::field::ForField<LogInfoFields::newestMinute>().name("newestMinute").asMap());
    props.append(
        cc::property::field::ForField<LogInfoFields::newestSecond>().name("newestSecond").asMap());
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

