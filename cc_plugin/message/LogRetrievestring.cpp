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

#include "LogRetrievestring.h"
#include "cc_plugin/field/common.h"

template class ublox::message::LogRetrievestring<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::LogRetrievestring<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::LogRetrievestring>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::LogRetrievestringFields;

QVariantMap createProps_byteCount()
{
    return
        cc::property::field::ForField<LogRetrievestringFields::byteCount>()
            .name("byteCount")
            .readOnly()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<LogRetrievestringFields::entryIndex>().name("entryIndex").asMap());
    props.append(
        cc::property::field::ForField<LogRetrievestringFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<LogRetrievestringFields::year>().name("year").asMap());
    props.append(
        cc::property::field::ForField<LogRetrievestringFields::month>().name("month").asMap());
    props.append(
        cc::property::field::ForField<LogRetrievestringFields::day>().name("day").asMap());
    props.append(
        cc::property::field::ForField<LogRetrievestringFields::hour>().name("hour").asMap());
    props.append(
        cc::property::field::ForField<LogRetrievestringFields::minute>().name("minute").asMap());
    props.append(
        cc::property::field::ForField<LogRetrievestringFields::second>().name("second").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(createProps_byteCount());
    props.append(
        cc::property::field::ForField<LogRetrievestringFields::bytes>().name("bytes").asMap());
    assert(props.size() == LogRetrievestring::FieldIdx_numOfValues);
    return props;
}

}  // namespace

LogRetrievestring::LogRetrievestring() = default;
LogRetrievestring::~LogRetrievestring() = default;

LogRetrievestring& LogRetrievestring::operator=(const LogRetrievestring&) = default;
LogRetrievestring& LogRetrievestring::operator=(LogRetrievestring&&) = default;

const char* LogRetrievestring::nameImpl() const
{
    static const char* Str = "LOG-RETRIEVESTRING";
    return Str;
}

const QVariantList& LogRetrievestring::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

