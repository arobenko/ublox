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

#include "CfgEsrc.h"

#include <cassert>

#include "cc_plugin/field/nav.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgEsrc<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgEsrc<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgEsrc>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgEsrcFields;

QVariantMap createProps_numSources()
{
    return
        cc::property::field::ForField<CfgEsrcFields::numSources>()
            .name("numSources")
            .readOnly()
            .asMap();
}

QVariantMap createProps_extInt()
{
    auto props =
        cc::property::field::ForField<CfgEsrcFields::extInt>()
            .name("extInt")
            .add("EXTINT0")
            .add("EXTINT1")
        ;
    assert(props.values().size() == (int)CfgEsrcFields::extInt::ValueType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_sourceType()
{
    auto props =
        cc::property::field::ForField<CfgEsrcFields::sourceType>()
            .name("sourceType")
            .add("none")
            .add("frequency")
            .add("time")
            .add("external oscillator")
        ;
    assert(props.values().size() == (int)CfgEsrcFields::sourceType::ValueType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_polarity()
{
    auto props =
        cc::property::field::ForField<CfgEsrcFields::polarity>()
            .name("polarity")
            .serialisedHidden()
            .add("rising edge")
            .add("falling edge")
        ;
    assert(props.values().size() == (int)CfgEsrcFields::polarity::ValueType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_gnssUtc()
{
    auto props =
        cc::property::field::ForField<CfgEsrcFields::gnssUtc>()
            .name("gnssUtc")
            .serialisedHidden()
            .add("GNSS")
            .add("UTC")
        ;
    assert(props.values().size() == (int)CfgEsrcFields::gnssUtc::ValueType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_flags()
{
    cc::property::field::ForField<CfgEsrcFields::flags> props;
    props.name("flags")
         .add(createProps_polarity())
         .add(createProps_gnssUtc())
         .add(cc::property::field::IntValue().name("reserved").hidden().asMap());
    assert(props.members().size() == CfgEsrcFields::flags::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_data()
{
    cc::property::field::ForField<CfgEsrcFields::block> blockProps;
    blockProps.add(createProps_extInt())
              .add(createProps_sourceType())
              .add(createProps_flags())
              .add(cc::property::field::ForField<CfgEsrcFields::freq>().name("freq").asMap())
              .add(cc_plugin::field::common::props_reserved(2))
              .add(cc::property::field::ForField<CfgEsrcFields::withTemp>().name("withTemp").asMap())
              .add(cc::property::field::ForField<CfgEsrcFields::withAge>().name("withAge").asMap())
              .add(cc::property::field::ForField<CfgEsrcFields::timeToTemp>().name("timeToTemp").asMap())
              .add(cc::property::field::ForField<CfgEsrcFields::maxDevLifeTime>().name("maxDevLifeTime").asMap())
              .add(cc::property::field::ForField<CfgEsrcFields::offset>().name("offset").asMap())
              .add(cc::property::field::ForField<CfgEsrcFields::offsetUncertainty>().name("offsetUncertainty").asMap())
              .add(cc::property::field::ForField<CfgEsrcFields::jitter>().name("jitter").asMap());
    assert(blockProps.members().size() == CfgEsrcFields::block::FieldIdx_numOfValues);

    return
        cc::property::field::ForField<CfgEsrcFields::data<> >()
            .name("data")
            .add(blockProps.asMap())
            .serialisedHidden()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;

    props.append(cc::property::field::ForField<CfgEsrcFields::version>().name("version").asMap());
    props.append(createProps_numSources());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_data());

    assert(props.size() == CfgEsrc::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgEsrc::CfgEsrc() = default;
CfgEsrc::~CfgEsrc() = default;

CfgEsrc& CfgEsrc::operator=(const CfgEsrc&) = default;
CfgEsrc& CfgEsrc::operator=(CfgEsrc&&) = default;

const char* CfgEsrc::nameImpl() const
{
    static const char* Str = "CFG-ESRC";
    return Str;
}

const QVariantList& CfgEsrc::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

