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

#include "TimVcocal.h"
#include "cc_plugin/field/common.h"

template class ublox::message::TimVcocal<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::TimVcocal<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::TimVcocal>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::TimVcocalFields;

QVariantMap createProps_oscId()
{
    typedef TimVcocalFields::oscId Field;
    auto props =
        cc::property::field::ForField<Field>()
            .name("oscId")
            .add("internal")
            .add("external");
    assert(props.values().size() == (int)Field::ValueType::NumOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<TimVcocalFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<TimVcocalFields::version>().name("version").asMap());
    props.append(createProps_oscId());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<TimVcocalFields::gainUncertainty>()
            .name("gainUncertainty").scaledDecimals(9).asMap());
    props.append(
        cc::property::field::ForField<TimVcocalFields::gainVco>()
            .name("gainVco").scaledDecimals(9).asMap());

    assert(props.size() == TimVcocal::FieldIdx_numOfValues);
    return props;
}

}  // namespace

TimVcocal::TimVcocal() = default;
TimVcocal::~TimVcocal() = default;

TimVcocal& TimVcocal::operator=(const TimVcocal&) = default;
TimVcocal& TimVcocal::operator=(TimVcocal&&) = default;

const char* TimVcocal::nameImpl() const
{
    static const char* Str = "TIM-VCOCAL";
    return Str;
}

const QVariantList& TimVcocal::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

