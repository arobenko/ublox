//
// Copyright 2017 (C). Alex Robenko. All rights reserved.
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


#include "RxmRlmShort.h"

#include <cassert>

#include "cc_plugin/field/common.h"

template class ublox::message::RxmRlmShort<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::RxmRlmShort<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::RxmRlmShort>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::RxmRlmShortFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<RxmRlmShortFields::version>().name("version").asMap());
    props.append(
        cc::property::field::ForField<RxmRlmShortFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<RxmRlmShortFields::svId>().name("svId").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<RxmRlmShortFields::beacon_1>().name("beacon_1").asMap());
    props.append(
        cc::property::field::ForField<RxmRlmShortFields::beacon_2>().name("beacon_2").asMap());
    props.append(
        cc::property::field::ForField<RxmRlmShortFields::message>().name("message").asMap());
    props.append(
        cc::property::field::ForField<RxmRlmShortFields::params>().name("params").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));

    assert(props.size() == RxmRlmShort::FieldIdx_numOfValues);
    return props;
}

}  // namespace

RxmRlmShort::RxmRlmShort() = default;
RxmRlmShort::~RxmRlmShort() = default;

RxmRlmShort& RxmRlmShort::operator=(const RxmRlmShort&) = default;
RxmRlmShort& RxmRlmShort::operator=(RxmRlmShort&&) = default;

const char* RxmRlmShort::nameImpl() const
{
    static const char* Str = "RXM-RLM (short)";
    return Str;
}

const QVariantList& RxmRlmShort::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

