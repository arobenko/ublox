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

using ublox::message::LogRetrieveposFields;

QVariantMap createProps_latLong(const char* name)
{
    return
        cc::property::field::ForField<LogRetrieveposFields::lat>()
            .name(name)
            .scaledDecimals(7)
            .asMap();
}

QVariantMap createProps_fixType()
{
    return
        cc::property::field::ForField<LogRetrieveposFields::fixType>()
            .name("fixType")
            .add("Dead reckoning", (int)LogRetrieveposFields::FixType::DeadReckoning)
            .add("2D-Fix", (int)LogRetrieveposFields::FixType::Fix_2D)
            .add("3D-Fix", (int)LogRetrieveposFields::FixType::Fix_3D)
            .add("GNSS + Dead reckoning", (int)LogRetrieveposFields::FixType::GnssAndDeadReckoning)
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<LogRetrieveposFields::entryIndex>().name("entryIndex").asMap());
    props.append(createProps_latLong("lon"));
    props.append(createProps_latLong("lat"));
    props.append(
        cc::property::field::ForField<LogRetrieveposFields::hMSL>().name("hMSL").asMap());
    props.append(
        cc::property::field::ForField<LogRetrieveposFields::hAcc>().name("hAcc").asMap());
    props.append(
        cc::property::field::ForField<LogRetrieveposFields::gSpeed>().name("gSpeed").asMap());
    props.append(
        cc::property::field::ForField<LogRetrieveposFields::heading>().name("heading").asMap());
    props.append(
        cc::property::field::ForField<LogRetrieveposFields::version>().name("version").asMap());
    props.append(createProps_fixType());
    props.append(
        cc::property::field::ForField<LogRetrieveposFields::year>().name("year").asMap());
    props.append(
        cc::property::field::ForField<LogRetrieveposFields::month>().name("month").asMap());
    props.append(
        cc::property::field::ForField<LogRetrieveposFields::day>().name("day").asMap());
    props.append(
        cc::property::field::ForField<LogRetrieveposFields::hour>().name("hour").asMap());
    props.append(
        cc::property::field::ForField<LogRetrieveposFields::minute>().name("minute").asMap());
    props.append(
        cc::property::field::ForField<LogRetrieveposFields::second>().name("second").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<LogRetrieveposFields::numSV>().name("numSV").asMap());
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

