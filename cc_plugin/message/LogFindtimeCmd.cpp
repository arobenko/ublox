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

#include "LogFindtimeCmd.h"
#include "cc_plugin/field/common.h"

template class ublox::message::LogFindtimeCmd<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::LogFindtimeCmd<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::LogFindtimeCmd>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::LogFindtimeCmdFields;

QVariantMap createProps_type()
{
    return
        cc::property::field::ForField<LogFindtimeCmdFields::type>()
            .name("type")
            .readOnly()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<LogFindtimeCmdFields::version>().name("version").asMap());
    props.append(createProps_type());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<LogFindtimeCmdFields::year>().name("year").asMap());
    props.append(
        cc::property::field::ForField<LogFindtimeCmdFields::month>().name("month").asMap());
    props.append(
        cc::property::field::ForField<LogFindtimeCmdFields::day>().name("day").asMap());
    props.append(
        cc::property::field::ForField<LogFindtimeCmdFields::hour>().name("hour").asMap());
    props.append(
        cc::property::field::ForField<LogFindtimeCmdFields::minute>().name("minute").asMap());
    props.append(
        cc::property::field::ForField<LogFindtimeCmdFields::second>().name("second").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));

    assert(props.size() == LogFindtimeCmd::FieldIdx_numOfValues);
    return props;
}

}  // namespace

LogFindtimeCmd::LogFindtimeCmd() = default;
LogFindtimeCmd::~LogFindtimeCmd() = default;

LogFindtimeCmd& LogFindtimeCmd::operator=(const LogFindtimeCmd&) = default;
LogFindtimeCmd& LogFindtimeCmd::operator=(LogFindtimeCmd&&) = default;

const char* LogFindtimeCmd::nameImpl() const
{
    static const char* Str = "LOG-FINDTIME (Command)";
    return Str;
}

const QVariantList& LogFindtimeCmd::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

