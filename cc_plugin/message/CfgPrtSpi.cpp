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

#include <type_traits>
#include <functional>
#include <cassert>

#include "CfgPrtSpi.h"
#include "cc_plugin/field/cfg.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgPrtSpi<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgPrtSpi<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgPrtSpi>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgPrtSpiFields;

QVariantMap createProps_mode()
{
    cc::property::field::ForField<CfgPrtSpiFields::spiMode> spiModeProps;
    spiModeProps.name("spiMode")
                .add("Mode 0: CPOL=0, CPHA=0")
                .add("Mode 1: CPOL=0, CPHA=1")
                .add("Mode 2: CPOL=1, CPHA=0")
                .add("Mode 3: CPOL=1, CPHA=1")
                .serialisedHidden();
    assert(spiModeProps.values().size() == (int)CfgPrtSpiFields::SpiMode::NumOfValues);

    cc::property::field::ForField<CfgPrtSpiFields::flowControl> flowControlProps;
    flowControlProps.name("flowControl")
                    .add("Disabled")
                    .add("Enabled")
                    .serialisedHidden();
    assert(flowControlProps.values().size() == (int)CfgPrtSpiFields::FlowControl::NumOfValues);

    cc::property::field::ForField<CfgPrtSpiFields::ffCnt> ffCntProps;
    ffCntProps.name("ffCnt").serialisedHidden();

    auto createReservedFunc =
        []() -> QVariantMap
        {
            return cc::property::field::IntValue().hidden().asMap();
        };

    cc::property::field::ForField<CfgPrtSpiFields::mode> props;
    props.name("mode")
         .add(createReservedFunc())
         .add(spiModeProps.asMap())
         .add(createReservedFunc())
         .add(flowControlProps.asMap())
         .add(createReservedFunc())
         .add(ffCntProps.asMap())
         .add(createReservedFunc());
    assert(props.members().size() == CfgPrtSpiFields::mode::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::cfg::props_readOnlyPortID());
    props.append(cc_plugin::field::common::props_reserved(0));
    props.append(cc_plugin::field::cfg::props_txReady());
    props.append(createProps_mode());
    props.append(cc_plugin::field::common::props_reserved(3));
    props.append(cc_plugin::field::cfg::props_inProtoMask());
    props.append(cc_plugin::field::cfg::props_outProtoMask());
    props.append(cc_plugin::field::cfg::props_prtFlags());
    props.append(cc_plugin::field::common::props_reserved(5));

    assert(props.size() == CfgPrtSpi::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgPrtSpi::CfgPrtSpi() = default;
CfgPrtSpi::~CfgPrtSpi() = default;

CfgPrtSpi& CfgPrtSpi::operator=(const CfgPrtSpi&) = default;
CfgPrtSpi& CfgPrtSpi::operator=(CfgPrtSpi&&) = default;


const char* CfgPrtSpi::nameImpl() const
{
    static const char* Str = "CFG-PRT (SPI)";
    return Str;
}

const QVariantList& CfgPrtSpi::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

