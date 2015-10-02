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

#include "LogCreate.h"
#include "cc_plugin/field/common.h"

template class ublox::message::LogCreate<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::LogCreate<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::LogCreate>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_logCfg()
{
    QVariantList bitNames;
    bitNames.append("circular");
    assert(bitNames.size() == ublox::message::LogCreateField_logCfg_numOfValues);
    return cc::Property::createPropertiesMap("logCfg", std::move(bitNames));
}

QVariantMap createProps_logSize()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "maximum safe");
    cc::Property::appendEnumValue(enumValues, "minimum");
    cc::Property::appendEnumValue(enumValues, "user defined");
    assert(enumValues.size() == (int)ublox::message::LogCreate_LogSize::NumOfValues);
    return cc::Property::createPropertiesMap("logSize", std::move(enumValues));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::Property::createPropertiesMap("version"));
    props.append(createProps_logCfg());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_logSize());
    props.append(cc::Property::createPropertiesMap("userDefinedSize"));

    assert(props.size() == LogCreate::FieldIdx_numOfValues);
    return props;
}

}  // namespace

LogCreate::LogCreate() = default;
LogCreate::~LogCreate() = default;

LogCreate& LogCreate::operator=(const LogCreate&) = default;
LogCreate& LogCreate::operator=(LogCreate&&) = default;

const char* LogCreate::nameImpl() const
{
    static const char* Str = "LOG-CREATE";
    return Str;
}

const QVariantList& LogCreate::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

