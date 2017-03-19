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

#include <cassert>

#include "TimVcocalExt.h"
#include "cc_plugin/field/common.h"

template class ublox::message::TimVcocalExt<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::TimVcocalExt<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::TimVcocalExt>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::TimVcocalExtFields;

QVariantMap createProps_oscId()
{
    typedef TimVcocalExtFields::oscId Field;
    auto props =
        cc::property::field::ForField<Field>()
            .name("oscId")
            .add("internal")
            .add("external");
    assert(props.values().size() == (int)Field::ValueType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_srcId()
{
    typedef TimVcocalExtFields::srcId Field;
    auto props =
        cc::property::field::ForField<Field>()
            .name("srcId")
            .add("internal oscillator")
            .add("GNSS")
            .add("EXTINT0")
            .add("EXTINT1");
    assert(props.values().size() == (int)Field::ValueType::NumOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<TimVcocalExtFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<TimVcocalExtFields::version>().name("version").asMap());
    props.append(createProps_oscId());
    props.append(createProps_srcId());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<TimVcocalExtFields::raw0>().name("raw0").asMap());
    props.append(
        cc::property::field::ForField<TimVcocalExtFields::raw1>().name("raw1").asMap());
    props.append(
        cc::property::field::ForField<TimVcocalExtFields::maxStepSize>().name("maxStepSize").asMap());

    assert(props.size() == TimVcocalExt::FieldIdx_numOfValues);
    return props;
}

}  // namespace

TimVcocalExt::TimVcocalExt() = default;
TimVcocalExt::~TimVcocalExt() = default;

TimVcocalExt& TimVcocalExt::operator=(const TimVcocalExt&) = default;
TimVcocalExt& TimVcocalExt::operator=(TimVcocalExt&&) = default;

const char* TimVcocalExt::nameImpl() const
{
    static const char* Str = "TIM-VCOCAL (Extended)";
    return Str;
}

const QVariantList& TimVcocalExt::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

