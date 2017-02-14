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

#include "CfgDosc.h"

#include <cassert>

#include "cc_plugin/field/common.h"

template class ublox::message::CfgDosc<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgDosc<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgDosc>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgDoscFields;

QVariantMap createProps_numOsc()
{
    return
        cc::property::field::ForField<CfgDoscFields::numOsc>()
            .name("numOsc")
            .readOnly()
            .asMap();
}

QVariantMap createProps_oscId()
{
    auto props =
        cc::property::field::ForField<CfgDoscFields::oscId>()
            .name("oscId")
            .add("internal")
            .add("external")
        ;
    assert(props.values().size() == (int)CfgDoscFields::oscId::ValueType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_isCalibrated()
{
    auto props =
        cc::property::field::ForField<CfgDoscFields::isCalibrated>()
            .serialisedHidden()
            .add("isCalibrated");

    assert(props.bits().size() == CfgDoscFields::isCalibrated::BitIdx::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_controlIf()
{
    return
        cc::property::field::ForField<CfgDoscFields::controlIf>()
            .name("controlIf")
            .serialisedHidden()
            .add("Custom DAC")
            .add("Microchip MCP4726")
            .add("TI DAC8571")
            .add("12 bit DAC", (int)CfgDoscFields::controlIf::ValueType::Dac_12)
            .add("14 bit DAC")
            .add("16 bit DAC")
            .asMap();
        ;
}


QVariantMap createProps_flags()
{
    cc::property::field::ForField<CfgDoscFields::flags> props;
    props.name("flags")
         .add(createProps_isCalibrated())
         .add(createProps_controlIf())
         .add(cc::property::field::IntValue().name("reserved").hidden().asMap());
    assert(props.members().size() == CfgDoscFields::flags::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_data()
{
    cc::property::field::ForField<CfgDoscFields::block> blockProps;
    blockProps.add(createProps_oscId())
              .add(cc_plugin::field::common::props_reserved(2))
              .add(createProps_flags())
              .add(cc::property::field::ForField<CfgDoscFields::freq>().name("freq").asMap())
              .add(cc::property::field::ForField<CfgDoscFields::phaseOffset>().name("phaseOffset").asMap())
              .add(cc::property::field::ForField<CfgDoscFields::withTemp>().name("withTemp").asMap())
              .add(cc::property::field::ForField<CfgDoscFields::withAge>().name("withAge").asMap())
              .add(cc::property::field::ForField<CfgDoscFields::timeToTemp>().name("timeToTemp").asMap())
              .add(cc_plugin::field::common::props_reserved(3))
              .add(cc::property::field::ForField<CfgDoscFields::gainVco>().name("gainVco").asMap())
              .add(cc::property::field::ForField<CfgDoscFields::gainUncertainty>().name("gainUncertainty").asMap())
              .add(cc_plugin::field::common::props_reserved(4));
    assert(blockProps.members().size() == CfgDoscFields::block::FieldIdx_numOfValues);

    return
        cc::property::field::ForField<CfgDoscFields::data<> >()
            .name("data")
            .add(blockProps.asMap())
            .serialisedHidden()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;

    props.append(cc::property::field::ForField<CfgDoscFields::version>().name("version").asMap());
    props.append(createProps_numOsc());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_data());

    assert(props.size() == CfgDosc::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgDosc::CfgDosc() = default;
CfgDosc::~CfgDosc() = default;

CfgDosc& CfgDosc::operator=(const CfgDosc&) = default;
CfgDosc& CfgDosc::operator=(CfgDosc&&) = default;

const char* CfgDosc::nameImpl() const
{
    static const char* Str = "CFG-DOSC";
    return Str;
}

const QVariantList& CfgDosc::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

