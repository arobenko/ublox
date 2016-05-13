//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
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

#include "cfg.h"

CC_DISABLE_WARNINGS()
#include <QtCore/QString>
#include <QtCore/QVariantList>
CC_ENABLE_WARNINGS()

#include "comms_champion/comms_champion.h"
#include "ublox/field/cfg.h"
#include "ublox/message/CfgPrt.h"
#include "ublox/message/CfgNmea.h"

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace field
{

namespace cfg
{

namespace
{

cc::property::field::EnumValue createPropsInternal_portID()
{
    return cc::property::field::EnumValue()
        .name("portID")
        .add("DDC", (int)ublox::message::CfgPrtFields::PortId::DDC)
        .add("UART", (int)ublox::message::CfgPrtFields::PortId::UART)
        .add("UART2", (int)ublox::message::CfgPrtFields::PortId::UART2)
        .add("USB", (int)ublox::message::CfgPrtFields::PortId::USB)
        .add("SPI", (int)ublox::message::CfgPrtFields::PortId::SPI);
}

QVariantMap createProps_portID()
{
    return createPropsInternal_portID().asMap();
}

QVariantMap createProps_readOnlyPortID()
{
    return createPropsInternal_portID().readOnly().asMap();
}

QVariantMap createProps_txReady()
{
    auto enProps =
        cc::property::field::ForField<ublox::message::CfgPrtFields::en>()
            .name("txReady")
            .add("en")
            .serialisedHidden();
    assert(enProps.bits().size() == ublox::message::CfgPrtFields::en_numOfValues);

    auto polProps =
        cc::property::field::ForField<ublox::message::CfgPrtFields::pol>()
            .name("pol")
            .add("High-active")
            .add("Low-active")
            .serialisedHidden();
    assert(polProps.values().size() == (int)ublox::message::CfgPrtFields::Polarity::NumOfValues);

    auto pinProps =
        cc::property::field::ForField<ublox::message::CfgPrtFields::pin>()
            .name("pin")
            .serialisedHidden();

    auto thresProps =
        cc::property::field::ForField<ublox::message::CfgPrtFields::pin>()
            .name("thres")
            .serialisedHidden();

    auto txReadyProps =
        cc::property::field::ForField<ublox::message::CfgPrtFields::txReady>()
            .name("txReady")
            .add(enProps.asMap())
            .add(polProps.asMap())
            .add(pinProps.asMap())
            .add(thresProps.asMap());

    assert(txReadyProps.members().size() == ublox::message::CfgPrtFields::txReady_numOfValues);
    return txReadyProps.asMap();
}

QVariantMap createProps_inProtoMask()
{
    auto props =
        cc::property::field::ForField<ublox::message::CfgPrtFields::inProtoMask>()
            .name("inProtoMask")
            .add("inUbx")
            .add("inNmea")
            .add("inRtcm");
    assert(props.bits().size() == ublox::message::CfgPrtFields::inProtoMask_numOfValues);
    return props.asMap();
}

QVariantMap createProps_outProtoMask()
{
    auto props =
        cc::property::field::ForField<ublox::message::CfgPrtFields::outProtoMask>()
            .name("outProtoMask")
            .add("outUbx")
            .add("outNmea")
    assert(props.bits().size() == ublox::message::CfgPrtFields::outProtoMask_numOfValues);
    return props.asMap();
}

QVariantMap createProps_prtFlags()
{
    auto props =
        cc::property::field::ForField<ublox::message::CfgPrtFields::flags>()
            .name("flags")
            .add(ublox::message::CfgPrtFields::flags_extendedTxTimeout, "extendedTxTimeout");
    assert(props.bits().size() == ublox::message::CfgPrtFields::flags_numOfValues);
    return props.asMap();
}

QVariantMap createProps_protocolID()
{
    auto props =
        cc::property::field::ForField<ublox::message::CfgInfFields::protocolID>()
            .name("protocolID")
            .add("UBX")
            .add("NMEA");

    assert(props.values().size() == (int)ublox::field::cfg::ProtocolId::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_nmeaFilter()
{
    QVariantList bitNames;
    bitNames.append("posFilt");
    bitNames.append("mskPosFilt");
    bitNames.append("timeFilt");
    bitNames.append("dateFilt");
    bitNames.append("gpsOnlyFilter");
    bitNames.append("trackFilt");
    assert(bitNames.size() == ublox::message::CfgNmeaFields::filter_numOfValues);
    return cc::Property::createPropertiesMap("filter", std::move(bitNames));
}

QVariantMap createProps_nmeaVersion()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "NMEA version 2.1", (int)ublox::message::CfgNmeaFields::NmeaVersion::v21);
    cc::Property::appendEnumValue(enumValues, "NMEA version 2.3", (int)ublox::message::CfgNmeaFields::NmeaVersion::v23);
    return cc::Property::createPropertiesMap("nmeaVersion", std::move(enumValues));
}

QVariantMap createProps_nmeaFlags()
{
    QVariantList bitNames;
    bitNames.append("compat");
    bitNames.append("consider");
    assert(bitNames.size() == ublox::message::CfgNmeaFields::flags_numOfValues);
    return cc::Property::createPropertiesMap("filter", std::move(bitNames));
}

QVariantMap createProps_tpIdx()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "TIMEPULSE");
    cc::Property::appendEnumValue(enumValues, "TIMEPULSE2");
    assert(enumValues.size() == (int)ublox::field::cfg::TpIdx::NumOfValues);
    return cc::Property::createPropertiesMap("tpIdx", std::move(enumValues));
}


}  // namespace

const QVariantMap& props_portID()
{
    static const auto Props = createProps_portID();
    return Props;
}

const QVariantMap& props_readOnlyPortID()
{
    static const auto Props = createProps_readOnlyPortID();
    return Props;
}

const QVariantMap& props_txReady()
{
    static const auto Props = createProps_txReady();
    return Props;
}

const QVariantMap& props_inProtoMask()
{
    static const auto Props = createProps_inProtoMask();
    return Props;
}

const QVariantMap& props_outProtoMask()
{
    static const auto Props = createProps_outProtoMask();
    return Props;
}

const QVariantMap& props_prtFlags()
{
    static const auto Props = createProps_prtFlags();
    return Props;
}

const QVariantMap& props_protocolID()
{
    static const auto Props = createProps_protocolID();
    return Props;
}

const QVariantMap& props_datumNum()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("datumNum");
    return Props;
}

const QVariantMap& props_datumName()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("datumName");
    return Props;
}

const QVariantMap& props_datMajA()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("majA");
    return Props;
}

const QVariantMap& props_datFlat()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("flat");
    return Props;
}

const QVariantMap& props_datDX()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("dX");
    return Props;
}

const QVariantMap& props_datDY()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("dY");
    return Props;
}

const QVariantMap& props_datDZ()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("dZ");
    return Props;
}

const QVariantMap& props_datRotX()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("rotX");
    return Props;
}

const QVariantMap& props_datRotY()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("rotY");
    return Props;
}

const QVariantMap& props_datRotZ()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("rotZ");
    return Props;
}

const QVariantMap& props_datScale()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("scale");
    return Props;
}

const QVariantMap& props_nmeaFilter()
{
    static const QVariantMap Props = createProps_nmeaFilter();
    return Props;
}

const QVariantMap& props_nmeaVersion()
{
    static const QVariantMap Props = createProps_nmeaVersion();
    return Props;
}

const QVariantMap& props_nmeaNumSV()
{
    static const QVariantMap Props = cc::Property::createPropertiesMap("numSV");
    return Props;
}

const QVariantMap& props_nmeaFlags()
{
    static const QVariantMap Props = createProps_nmeaFlags();
    return Props;
}

const QVariantMap& props_tpIdx()
{
    static const QVariantMap Props = createProps_tpIdx();
    return Props;
}

}  // namespace cfg

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox


