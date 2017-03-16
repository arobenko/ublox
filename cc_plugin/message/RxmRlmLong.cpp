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


#include "RxmRlmLong.h"

#include <cassert>

#include "cc_plugin/field/common.h"

template class ublox::message::RxmRlmLong<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::RxmRlmLong<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::RxmRlmLong>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::RxmRlmLongFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<RxmRlmLongFields::version>().name("version").asMap());
    props.append(
        cc::property::field::ForField<RxmRlmLongFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<RxmRlmLongFields::svId>().name("svId").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<RxmRlmLongFields::beacon_1>().name("beacon_1").asMap());
    props.append(
        cc::property::field::ForField<RxmRlmLongFields::beacon_2>().name("beacon_2").asMap());
    props.append(
        cc::property::field::ForField<RxmRlmLongFields::message>().name("message").asMap());
    props.append(
        cc::property::field::ForField<RxmRlmLongFields::params_1>().name("params_1").asMap());
    props.append(
        cc::property::field::ForField<RxmRlmLongFields::params_2>().name("params_2").asMap());
    props.append(
        cc::property::field::ForField<RxmRlmLongFields::params_3>().name("params_3").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));

    assert(props.size() == RxmRlmLong::FieldIdx_numOfValues);
    return props;
}

}  // namespace

RxmRlmLong::RxmRlmLong() = default;
RxmRlmLong::~RxmRlmLong() = default;

RxmRlmLong& RxmRlmLong::operator=(const RxmRlmLong&) = default;
RxmRlmLong& RxmRlmLong::operator=(RxmRlmLong&&) = default;

const char* RxmRlmLong::nameImpl() const
{
    static const char* Str = "RXM-RLM (long)";
    return Str;
}

const QVariantList& RxmRlmLong::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

