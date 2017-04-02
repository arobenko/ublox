//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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

#include "LogRetrieveposextra.h"
#include "cc_plugin/field/common.h"

template class ublox::message::LogRetrieveposextra<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::LogRetrieveposextra<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::LogRetrieveposextra>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::LogRetrieveposextraFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<LogRetrieveposextraFields::entryIndex>().name("entryIndex").asMap());
    props.append(
        cc::property::field::ForField<LogRetrieveposextraFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<LogRetrieveposextraFields::year>().name("year").asMap());
    props.append(
        cc::property::field::ForField<LogRetrieveposextraFields::month>().name("month").asMap());
    props.append(
        cc::property::field::ForField<LogRetrieveposextraFields::day>().name("day").asMap());
    props.append(
        cc::property::field::ForField<LogRetrieveposextraFields::hour>().name("hour").asMap());
    props.append(
        cc::property::field::ForField<LogRetrieveposextraFields::minute>().name("minute").asMap());
    props.append(
        cc::property::field::ForField<LogRetrieveposextraFields::second>().name("second").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(
        cc::property::field::ForField<LogRetrieveposextraFields::distance>().name("distance").asMap());
    props.append(cc_plugin::field::common::props_reserved(3));
    props.append(cc_plugin::field::common::props_reserved(4));
    props.append(cc_plugin::field::common::props_reserved(5));

    assert(props.size() == LogRetrieveposextra::FieldIdx_numOfValues);
    return props;
}

}  // namespace

LogRetrieveposextra::LogRetrieveposextra() = default;
LogRetrieveposextra::~LogRetrieveposextra() = default;

LogRetrieveposextra& LogRetrieveposextra::operator=(const LogRetrieveposextra&) = default;
LogRetrieveposextra& LogRetrieveposextra::operator=(LogRetrieveposextra&&) = default;

const char* LogRetrieveposextra::nameImpl() const
{
    static const char* Str = "LOG-RETRIEVEPOSEXTRA";
    return Str;
}

const QVariantList& LogRetrieveposextra::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

