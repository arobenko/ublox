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

#include "EsfMeas.h"

#include <cassert>

#include "cc_plugin/field/common.h"

template class ublox::message::EsfMeas<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::EsfMeas<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::EsfMeas>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::EsfMeasFields;

QVariantMap createProps_timeMarkSent()
{
    using Field = EsfMeasFields::timeMarkSent;
    auto props =
        cc::property::field::ForField<Field>()
            .name("timeMarkSent")
            .serialisedHidden()
            .add("None")
            .add("Ext0")
            .add("Ext1");
    assert(props.values().size() == (int)Field::ValueType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_timeMarkEdge()
{
    using Field = EsfMeasFields::timeMarkEdge;
    auto props =
        cc::property::field::ForField<Field>()
            .name("timeMarkEdge")
            .serialisedHidden()
            .add("Rising")
            .add("Falling");
    assert(props.values().size() == (int)Field::ValueType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_flagsBits()
{
    using Field = EsfMeasFields::flagsBits;
    auto props =
        cc::property::field::ForField<Field>()
            .serialisedHidden()
            .add("calibTtagValid");
    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_flags()
{
    using Field = EsfMeasFields::flags;
    auto props =
        cc::property::field::ForField<Field>()
            .name("flags")
            .add(createProps_timeMarkSent())
            .add(createProps_timeMarkEdge())
            .add(createProps_flagsBits());
    assert(props.members().size() == Field::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_data()
{
    using DataElemField = EsfMeasFields::dataElem;
    auto dataElemProps =
        cc::property::field::ForField<DataElemField>()
            .add(cc::property::field::ForField<EsfMeasFields::dataField>().name("dataField").asMap())
            .add(cc::property::field::ForField<EsfMeasFields::dataType>().name("dataType").asMap())
            .serialisedHidden();
    assert(dataElemProps.members().size() == DataElemField::FieldIdx_numOfValues);

    return
        cc::property::field::ForField<EsfMeasFields::data<> >()
            .name("data")
            .add(dataElemProps.asMap())
            .serialisedHidden()
            .asMap();
}

QVariantMap createProps_calibTtag()
{
    using Field = EsfMeasFields::calibTtag;
    auto props =
        cc::property::field::ForField<Field>()
            .name("calibTtag")
            .field(cc::property::field::ForField<Field::Field>().name("calibTtag").asMap())
            .uncheckable();
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<EsfMeasFields::timeTag>().name("timeTag").asMap());
    props.append(createProps_flags());
    props.append(
        cc::property::field::ForField<EsfMeasFields::id>().name("id").asMap());
    props.append(createProps_data());
    props.append(createProps_calibTtag());

    assert(props.size() == EsfMeas::FieldIdx_numOfValues);
    return props;
}

}  // namespace

EsfMeas::EsfMeas() = default;
EsfMeas::~EsfMeas() = default;

EsfMeas& EsfMeas::operator=(const EsfMeas&) = default;
EsfMeas& EsfMeas::operator=(EsfMeas&&) = default;

const char* EsfMeas::nameImpl() const
{
    static const char* Str = "ESF-MEAS";
    return Str;
}

const QVariantList& EsfMeas::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

