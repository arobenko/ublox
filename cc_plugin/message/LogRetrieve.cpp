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

#include "LogRetrieve.h"
#include "cc_plugin/field/common.h"

template class ublox::message::LogRetrieve<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::LogRetrieve<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::LogRetrieve>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::LogRetrieveFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<LogRetrieveFields::startNumber>().name("startNumber").asMap());
    props.append(
        cc::property::field::ForField<LogRetrieveFields::entryCount>().name("entryCount").asMap());
    props.append(
        cc::property::field::ForField<LogRetrieveFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    assert(props.size() == LogRetrieve::FieldIdx_numOfValues);
    return props;
}

}  // namespace

LogRetrieve::LogRetrieve() = default;
LogRetrieve::~LogRetrieve() = default;

LogRetrieve& LogRetrieve::operator=(const LogRetrieve&) = default;
LogRetrieve& LogRetrieve::operator=(LogRetrieve&&) = default;

const char* LogRetrieve::nameImpl() const
{
    static const char* Str = "LOG-RETRIEVE";
    return Str;
}

const QVariantList& LogRetrieve::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

