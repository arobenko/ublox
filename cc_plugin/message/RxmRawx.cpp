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

#include "RxmRawx.h"
#include "cc_plugin/field/rxm.h"
#include "cc_plugin/field/common.h"

template class ublox::message::RxmRawx<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::RxmRawx<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::RxmRawx>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::RxmRawxFields;

QVariantMap createProps_recStat()
{
    using Field = RxmRawxFields::recStat;
    auto props =
        cc::property::field::ForField<Field>()
            .name("recStat")
            .add("leapSec")
            .add("clkReset");
    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_trkStat()
{
    using Field = RxmRawxFields::trkStat;
    auto props =
        cc::property::field::ForField<Field>()
            .name("trkStat")
            .add("prValid")
            .add("cpValid")
            .add("halfCyc")
            .add("subHalfCyc");
    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}


QVariantMap createProps_data()
{
    auto blockProps =
        cc::property::field::ForField<RxmRawxFields::block>()
            .add(cc::property::field::ForField<RxmRawxFields::prMes>().name("prMes").asMap())
            .add(cc::property::field::ForField<RxmRawxFields::cpMes>().name("cpMes").asMap())
            .add(cc::property::field::ForField<RxmRawxFields::doMes>().name("doMes").asMap())
            .add(cc_plugin::field::common::props_gnssId())
            .add(cc::property::field::ForField<RxmRawxFields::svId>().name("svId").asMap())
            .add(cc_plugin::field::common::props_reserved(2))
            .add(cc::property::field::ForField<RxmRawxFields::freqId>().name("freqId").asMap())
            .add(cc::property::field::ForField<RxmRawxFields::locktime>().name("locktime").asMap())
            .add(cc::property::field::ForField<RxmRawxFields::cno>().name("cno").asMap())
            .add(cc::property::field::ForField<RxmRawxFields::prStdev>().name("prStdev").asMap())
            .add(cc::property::field::ForField<RxmRawxFields::cpStdev>().name("cpStdev").scaledDecimals(3).asMap())
            .add(cc::property::field::ForField<RxmRawxFields::doStdev>().name("doStdev").asMap())
            .add(createProps_trkStat())
            .add(cc_plugin::field::common::props_reserved(3));

    assert(blockProps.members().size() == RxmRawxFields::block::FieldIdx_numOfValues);

    return
        cc::property::field::ForField<RxmRawxFields::data<> >()
            .name("data")
            .add(blockProps.asMap())
            .serialisedHidden()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<RxmRawxFields::rcvTow>().name("rcvTow").asMap());
    props.append(cc_plugin::field::rxm::props_week());
    props.append(
        cc::property::field::ForField<RxmRawxFields::leapS>().name("leapS").asMap());
    props.append(
        cc::property::field::ForField<RxmRawxFields::numMeas>().name("numMeas").readOnly().asMap());
    props.append(createProps_recStat());
    props.append(
        cc::property::field::ForField<RxmRawxFields::version>().name("version").readOnly().asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_data());

    assert(props.size() == RxmRawx::FieldIdx_numOfValues);
    return props;
}

}  // namespace

RxmRawx::RxmRawx() = default;
RxmRawx::~RxmRawx() = default;

RxmRawx& RxmRawx::operator=(const RxmRawx&) = default;
RxmRawx& RxmRawx::operator=(RxmRawx&&) = default;

const char* RxmRawx::nameImpl() const
{
    static const char* Str = "RXM-RAWX";
    return Str;
}

const QVariantList& RxmRawx::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

