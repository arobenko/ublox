//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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

#include "RxmRaw.h"
#include "cc_plugin/field/rxm.h"
#include "cc_plugin/field/common.h"

template class ublox::message::RxmRaw<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::RxmRaw<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::RxmRaw>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::RxmRawFields;

QVariantMap createProps_data()
{
    cc::property::field::ForField<RxmRawFields::block> blockProps;
    blockProps
        .add(cc::property::field::ForField<RxmRawFields::cpMes>().name("cpMes").asMap())
        .add(cc::property::field::ForField<RxmRawFields::prMes>().name("prMes").asMap())
        .add(cc::property::field::ForField<RxmRawFields::doMes>().name("doMes").asMap())
        .add(cc::property::field::ForField<RxmRawFields::sv>().name("sv").asMap())
        .add(cc::property::field::ForField<RxmRawFields::mesQI>().name("mesQI").asMap())
        .add(cc::property::field::ForField<RxmRawFields::cno>().name("cno").asMap())
        .add(cc::property::field::ForField<RxmRawFields::lli>().name("lli").asMap());

    assert(blockProps.members().size() == RxmRawFields::block::FieldIdx_numOfValues);

    return
        cc::property::field::ForField<RxmRawFields::data>()
            .name("data")
            .add(blockProps.asMap())
            .serialisedHidden()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<RxmRawFields::rcvTow>().name("rcvTow").asMap());
    props.append(cc_plugin::field::rxm::props_week());
    props.append(cc_plugin::field::rxm::props_numSV());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_data());

    assert(props.size() == RxmRaw::FieldIdx_numOfValues);
    return props;
}

}  // namespace

RxmRaw::RxmRaw() = default;
RxmRaw::~RxmRaw() = default;

RxmRaw& RxmRaw::operator=(const RxmRaw&) = default;
RxmRaw& RxmRaw::operator=(RxmRaw&&) = default;

const char* RxmRaw::nameImpl() const
{
    static const char* Str = "RXM-RAW";
    return Str;
}

const QVariantList& RxmRaw::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

