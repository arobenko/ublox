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

#include "LogFindtime.h"
#include "cc_plugin/field/common.h"

template class ublox::message::LogFindtime<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::LogFindtime<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::LogFindtime>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::LogFindtimeFields;

QVariantMap createProps_type()
{
    return
        cc::property::field::ForField<LogFindtimeFields::type>()
            .name("type")
            .readOnly()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<LogFindtimeFields::version>().name("version").asMap());
    props.append(createProps_type());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<LogFindtimeFields::entryNumber>().name("entryNumber").asMap());

    assert(props.size() == LogFindtime::FieldIdx_numOfValues);
    return props;
}

}  // namespace

LogFindtime::LogFindtime() = default;
LogFindtime::~LogFindtime() = default;

LogFindtime& LogFindtime::operator=(const LogFindtime&) = default;
LogFindtime& LogFindtime::operator=(LogFindtime&&) = default;

const char* LogFindtime::nameImpl() const
{
    static const char* Str = "LOG-FINDTIME";
    return Str;
}

const QVariantList& LogFindtime::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

