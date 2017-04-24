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

#include "RxmMeasx.h"
#include "cc_plugin/field/rxm.h"
#include "cc_plugin/field/common.h"

template class ublox::message::RxmMeasx<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::RxmMeasx<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::RxmMeasx>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::RxmMeasxFields;

QVariantMap createProps_towSet()
{
    using Field = RxmMeasxFields::towSet;
    auto props =
        cc::property::field::ForField<Field>()
            .name("towSet")
            .add("no")
            .add("yes")
            .add("yes (2)");
    assert(props.values().size() == (int)Field::ValueType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_flags()
{
    using Field = RxmMeasxFields::flags;
    auto props =
        cc::property::field::ForField<Field>()
            .name("flags")
            .add(createProps_towSet())
            .add(cc::property::field::IntValue().hidden().asMap());
    assert(props.members().size() == (int)Field::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_mpathIndic()
{
    using Field = RxmMeasxFields::mpathIndic;
    auto props =
        cc::property::field::ForField<Field>()
            .name("mpathIndic")
            .add("not measured")
            .add("low")
            .add("medium")
            .add("high");

    assert(props.values().size() == (int)Field::ValueType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_dopplerMS()
{
    return
        cc::property::field::ForField<RxmMeasxFields::dopplerMS>()
            .name("dopplerMS")
            .scaledDecimals(2)
            .asMap();
}

QVariantMap createProps_dopplerHZ()
{
    return
        cc::property::field::ForField<RxmMeasxFields::dopplerHZ>()
            .name("dopplerHZ")
            .scaledDecimals(1)
            .asMap();
}

QVariantMap createProps_codePhase()
{
    return
        cc::property::field::ForField<RxmMeasxFields::codePhase>()
            .name("codePhase")
            .scaledDecimals(9)
            .asMap();
}

QVariantMap createProps_data()
{
    auto blockProps =
        cc::property::field::ForField<RxmMeasxFields::block>()
            .add(cc_plugin::field::common::props_gnssId())
            .add(cc::property::field::ForField<RxmMeasxFields::svId>().name("svId").asMap())
            .add(cc::property::field::ForField<RxmMeasxFields::cNo>().name("cNo").asMap())
            .add(createProps_mpathIndic())
            .add(createProps_dopplerMS())
            .add(createProps_dopplerHZ())
            .add(cc::property::field::ForField<RxmMeasxFields::wholeChips>().name("wholeChips").asMap())
            .add(cc::property::field::ForField<RxmMeasxFields::fracChips>().name("fracChips").asMap())
            .add(createProps_codePhase())
            .add(cc::property::field::ForField<RxmMeasxFields::intCodePhase>().name("intCodePhase").asMap())
            .add(cc::property::field::ForField<RxmMeasxFields::pseuRangeRMSErr>().name("pseuRangeRMSErr").asMap())
            .add(cc_plugin::field::common::props_reserved(6));
    assert(blockProps.members().size() == RxmMeasxFields::block::FieldIdx_numOfValues);

    return
        cc::property::field::ForField<RxmMeasxFields::data<> >()
            .name("data")
            .serialisedHidden()
            .add(blockProps.asMap())
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<RxmMeasxFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<RxmMeasxFields::gpsTOW>().name("gpsTOW").asMap());
    props.append(
        cc::property::field::ForField<RxmMeasxFields::gloTOW>().name("gloTOW").asMap());
    props.append(
        cc::property::field::ForField<RxmMeasxFields::bdsTOW>().name("bdsTOW").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(
        cc::property::field::ForField<RxmMeasxFields::qzssTOW>().name("qzssTOW").asMap());
    props.append(
        cc::property::field::ForField<RxmMeasxFields::gpsTOWacc>().name("gpsTOWacc").asMap());
    props.append(
        cc::property::field::ForField<RxmMeasxFields::gloTOWacc>().name("gloTOWacc").asMap());
    props.append(
        cc::property::field::ForField<RxmMeasxFields::bdsTOWacc>().name("bdsTOWacc").asMap());
    props.append(cc_plugin::field::common::props_reserved(3));
    props.append(
        cc::property::field::ForField<RxmMeasxFields::qzssTOWacc>().name("qzssTOWacc").asMap());
    props.append(
        cc::property::field::ForField<RxmMeasxFields::numSV>().name("numSV").readOnly().asMap());
    props.append(createProps_flags());
    props.append(cc_plugin::field::common::props_reserved(4));
    props.append(cc_plugin::field::common::props_reserved(5));
    props.append(createProps_data());

    assert(props.size() == RxmMeasx::FieldIdx_numOfValues);
    return props;
}

}  // namespace

RxmMeasx::RxmMeasx() = default;
RxmMeasx::~RxmMeasx() = default;

RxmMeasx& RxmMeasx::operator=(const RxmMeasx&) = default;
RxmMeasx& RxmMeasx::operator=(RxmMeasx&&) = default;

const char* RxmMeasx::nameImpl() const
{
    static const char* Str = "RXM-MEASX";
    return Str;
}

const QVariantList& RxmMeasx::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

