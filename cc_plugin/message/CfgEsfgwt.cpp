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

#include "CfgEsfgwt.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgEsfgwt<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgEsfgwt<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgEsfgwt>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgEsfgwtFields;

QVariantMap createProps_flags()
{
    cc::property::field::ForField<CfgEsfgwtFields::flags> props;
    props.name("flags")
         .add(CfgEsfgwtFields::flags::BitIdx_setVehicle, "setVehicle")
         .add("setTime")
         .add("setWt");
    assert(props.bits().size() == CfgEsfgwtFields::flags::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_scaledValue(const char* name, int decimals)
{
    return
        cc::property::field::IntValue()
            .name(name)
            .scaledDecimals(decimals)
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_flags());
    props.append(
        cc::property::field::ForField<CfgEsfgwtFields::id>().name("id").asMap());
    props.append(createProps_scaledValue("wtFactor", 6));
    props.append(field::common::props_reserved(1));
    props.append(createProps_scaledValue("wtQuantError", 6));
    props.append(createProps_scaledValue("timeTagFactor", 6));
    props.append(
        cc::property::field::ForField<CfgEsfgwtFields::wtCountMax>().name("wtCountMax").asMap());
    props.append(
        cc::property::field::ForField<CfgEsfgwtFields::timeTagMax>().name("timeTagMax").asMap());
    props.append(
        cc::property::field::ForField<CfgEsfgwtFields::wtLatency>().name("wtLatency").asMap());
    props.append(field::common::props_reserved(2));
    props.append(
        cc::property::field::ForField<CfgEsfgwtFields::wtFrequency>().name("wtFrequency").asMap());
    props.append(field::common::props_reserved(3));
    props.append(
        cc::property::field::ForField<CfgEsfgwtFields::speedDeadBand>().name("speedDeadBand").asMap());
    props.append(field::common::props_reserved(4));
    props.append(field::common::props_reserved(5));
    assert(props.size() == CfgEsfgwt::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgEsfgwt::CfgEsfgwt() = default;
CfgEsfgwt::~CfgEsfgwt() = default;

CfgEsfgwt& CfgEsfgwt::operator=(const CfgEsfgwt&) = default;
CfgEsfgwt& CfgEsfgwt::operator=(CfgEsfgwt&&) = default;


const char* CfgEsfgwt::nameImpl() const
{
    static const char* Str = "CFG-ESFGWT";
    return Str;
}

const QVariantList& CfgEsfgwt::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

