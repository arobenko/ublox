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

#include "LogString.h"
#include "cc_plugin/field/common.h"

template class ublox::message::LogString<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::LogString<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::LogString>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::LogStringFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<LogStringFields::bytes>().name("bytes").asMap());

    assert(props.size() == LogString::FieldIdx_numOfValues);
    return props;
}

}  // namespace

LogString::LogString() = default;
LogString::~LogString() = default;

LogString& LogString::operator=(const LogString&) = default;
LogString& LogString::operator=(LogString&&) = default;

const char* LogString::nameImpl() const
{
    static const char* Str = "LOG-STRING";
    return Str;
}

const QVariantList& LogString::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

