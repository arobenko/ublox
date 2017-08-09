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

#include "CfgPms.h"

#include "cc_plugin/field/common.h"

template class ublox::message::CfgPms<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgPms<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgPms>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgPmsFields;

QVariantMap createProps_powerSetupValue()
{
    return
        cc::property::field::ForField<CfgPmsFields::powerSetupValue>()
            .name("powerSetupValue")
            .add("Full Power")
            .add("Balanced")
            .add("Interval")
            .add("Aggressive 1Hz")
            .add("Aggressive 2Hz")
            .add("Aggressive 4Hz")
            .add("Invalid", (int)CfgPmsFields::PowerSetupValue::Invalid)
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<CfgPmsFields::version>().name("version").asMap());
    props.append(createProps_powerSetupValue());
    props.append(
        cc::property::field::ForField<CfgPmsFields::period>().name("period").asMap());
    props.append(
        cc::property::field::ForField<CfgPmsFields::onTime>().name("onTime").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    assert(props.size() == CfgPms::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgPms::CfgPms() = default;
CfgPms::~CfgPms() = default;

CfgPms& CfgPms::operator=(const CfgPms&) = default;
CfgPms& CfgPms::operator=(CfgPms&&) = default;


const char* CfgPms::nameImpl() const
{
    static const char* Str = "CFG-PMS";
    return Str;
}

const QVariantList& CfgPms::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

