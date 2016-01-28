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

QVariantMap createProps_mode()
{
    QVariantList spiModeEnumValues;
    cc::Property::appendEnumValue(spiModeEnumValues, "Mode 0: CPOL=0, CPHA=0");
    cc::Property::appendEnumValue(spiModeEnumValues, "Mode 1: CPOL=0, CPHA=1");
    cc::Property::appendEnumValue(spiModeEnumValues, "Mode 2: CPOL=1, CPHA=0");
    cc::Property::appendEnumValue(spiModeEnumValues, "Mode 3: CPOL=1, CPHA=1");
    assert(spiModeEnumValues.size() == (int)ublox::message::CfgPrtSpiFields::SpiMode::NumOfValues);
    auto spiModeProps = cc::Property::createPropertiesMap("spiMode", std::move(spiModeEnumValues));
    cc::Property::setSerialisedHidden(spiModeProps);

    QVariantList flowControlEnumValues;
    cc::Property::appendEnumValue(flowControlEnumValues, "Disabled");
    cc::Property::appendEnumValue(flowControlEnumValues, "Enabled");
    assert(flowControlEnumValues.size() == (int)ublox::message::CfgPrtSpiFields::FlowControl::NumOfValues);
    auto flowControlProps = cc::Property::createPropertiesMap("flowControl", std::move(flowControlEnumValues));
    cc::Property::setSerialisedHidden(flowControlProps);

    auto ffCntProps = cc::Property::createPropertiesMap("ffCnt");
    cc::Property::setSerialisedHidden(ffCntProps);

    auto createReservedFunc =
        []() -> QVariantMap
        {
            QVariantMap props;
            cc::Property::setFieldHidden(props);
            return props;
        };

    QVariantList membersData;
    membersData.append(createReservedFunc());
    membersData.append(std::move(spiModeProps));
    membersData.append(createReservedFunc());
    membersData.append(std::move(flowControlProps));
    membersData.append(createReservedFunc());
    membersData.append(std::move(ffCntProps));
    membersData.append(createReservedFunc());
    assert(membersData.size() == ublox::message::CfgPrtSpiFields::mode_numOfValues);
    return cc::Property::createPropertiesMap("mode", std::move(membersData));
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

