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

#include "TimHoc.h"
#include "cc_plugin/field/common.h"

template class ublox::message::TimHoc<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::TimHoc<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::TimHoc>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::TimHocFields;

QVariantMap createProps_oscId()
{
    typedef TimHocFields::oscId Field;
    auto props =
        cc::property::field::ForField<Field>()
            .name("oscId")
            .add("internal")
            .add("external");

    assert(props.values().size() == (int)Field::ValueType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_flags()
{
    typedef TimHocFields::flags Field;
    auto props =
        cc::property::field::ForField<Field>()
            .name("flags")
            .add("raw")
            .add("difference");
    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<TimHocFields::version>().name("version").asMap());
    props.append(createProps_oscId());
    props.append(createProps_flags());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<TimHocFields::value>().name("value").scaledDecimals(4).asMap());
    assert(props.size() == TimHoc::FieldIdx_numOfValues);
    return props;
}

}  // namespace

TimHoc::TimHoc() = default;
TimHoc::~TimHoc() = default;

TimHoc& TimHoc::operator=(const TimHoc&) = default;
TimHoc& TimHoc::operator=(TimHoc&&) = default;

const char* TimHoc::nameImpl() const
{
    static const char* Str = "TIM-HOC";
    return Str;
}

const QVariantList& TimHoc::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

