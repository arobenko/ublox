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

#include "TimSmeas.h"

#include <cassert>

#include "cc_plugin/field/common.h"

template class ublox::message::TimSmeas<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::TimSmeas<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::TimSmeas>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::TimSmeasFields;

QVariantMap createProps_flags()
{
    using Field = TimSmeasFields::flags;
    auto props =
        cc::property::field::ForField<Field>()
            .name("flags")
            .add("freqValid")
            .add("phaseValid");
    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_data()
{
    auto blockProps =
        cc::property::field::ForField<TimSmeasFields::block>()
            .add(cc::property::field::ForField<TimSmeasFields::sourceId>().name("sourceId").asMap())
            .add(createProps_flags())
            .add(cc::property::field::ForField<TimSmeasFields::phaseOffsetFrac>().name("phaseOffsetFrac").scaledDecimals(4).asMap())
            .add(cc::property::field::ForField<TimSmeasFields::phaseUncFrac>().name("phaseUncFrac").scaledDecimals(4).asMap())
            .add(cc::property::field::ForField<TimSmeasFields::phaseOffset>().name("phaseOffset").asMap())
            .add(cc::property::field::ForField<TimSmeasFields::phaseUnc>().name("phaseUnc").asMap())
            .add(cc_plugin::field::common::props_reserved(3))
            .add(cc::property::field::ForField<TimSmeasFields::freqOffset>().name("freqOffset").scaledDecimals(4).asMap())
            .add(cc::property::field::ForField<TimSmeasFields::freqUnc>().name("freqUnc").scaledDecimals(4).asMap());
    assert(blockProps.members().size() == TimSmeasFields::block::FieldIdx_numOfValues);

    return
        cc::property::field::ForField<TimSmeasFields::data<> >()
            .name("data")
            .add(blockProps.asMap())
            .serialisedHidden()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<TimSmeasFields::version>().name("version").asMap());
    props.append(
        cc::property::field::ForField<TimSmeasFields::numMeas>().name("numMeas").readOnly().asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<TimSmeasFields::iTOW>().name("iTOW").readOnly().asMap());
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(createProps_data());

    assert(props.size() == TimSmeas::FieldIdx_numOfValues);
    return props;
}

}  // namespace

TimSmeas::TimSmeas() = default;
TimSmeas::~TimSmeas() = default;

TimSmeas& TimSmeas::operator=(const TimSmeas&) = default;
TimSmeas& TimSmeas::operator=(TimSmeas&&) = default;

const char* TimSmeas::nameImpl() const
{
    static const char* Str = "TIM-SMEAS";
    return Str;
}

const QVariantList& TimSmeas::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

