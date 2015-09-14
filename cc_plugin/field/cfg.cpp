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

#include <QtCore/QString>
#include <QtCore/QVariantList>

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

QVariantMap createProps_portID()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "DDC", (int)ublox::message::CfgPrt_PortId::DDC);
    cc::Property::appendEnumValue(enumValues, "UART", (int)ublox::message::CfgPrt_PortId::UART);
    cc::Property::appendEnumValue(enumValues, "UART2", (int)ublox::message::CfgPrt_PortId::UART2);
    cc::Property::appendEnumValue(enumValues, "USB", (int)ublox::message::CfgPrt_PortId::USB);
    cc::Property::appendEnumValue(enumValues, "SPI", (int)ublox::message::CfgPrt_PortId::SPI);

    return cc::Property::createPropertiesMap("portID", std::move(enumValues));
}

QVariantMap createProps_readOnlyPortID()
{
    auto props = createProps_portID();
    cc::Property::setReadOnly(props);
    return props;
}

QVariantMap createProps_txReady()
{
    QVariantList enBitNames;
    enBitNames.append("en");
    auto enProps = cc::Property::createPropertiesMap("txReady", std::move(enBitNames));
    cc::Property::setSerialisedHidden(enProps);

    QVariantList polEnumValues;
    cc::Property::appendEnumValue(polEnumValues, "High-active");
    cc::Property::appendEnumValue(polEnumValues, "Low-active");
    assert(polEnumValues.size() == (int)ublox::field::cfg::Polarity::NumOfValues);
    auto polProps = cc::Property::createPropertiesMap("pol", std::move(polEnumValues));
    cc::Property::setSerialisedHidden(polProps);

    auto pinProps = cc::Property::createPropertiesMap("pin");
    cc::Property::setSerialisedHidden(pinProps);

    auto thresProps = cc::Property::createPropertiesMap("thres");
    cc::Property::setSerialisedHidden(thresProps);

    QVariantList membersData;
    membersData.append(std::move(enProps));
    membersData.append(std::move(polProps));
    membersData.append(std::move(pinProps));
    membersData.append(std::move(thresProps));
    assert(membersData.size() == ublox::message::CfgPrt_txReady_numOfValues);
    return cc::Property::createPropertiesMap("txReady", std::move(membersData));
}

QVariantMap createProps_inProtoMask()
{
    QVariantList bitNames;
    bitNames.append("inUbx");
    bitNames.append("inNmea");
    bitNames.append("inRtcm");
    assert(bitNames.size() == ublox::message::CfgPrt_inProtoMask_numOfValues);
    return cc::Property::createPropertiesMap("inProtoMask", std::move(bitNames));
}

QVariantMap createProps_outProtoMask()
{
    QVariantList bitNames;
    bitNames.append("outUbx");
    bitNames.append("outNmea");
    assert(bitNames.size() == ublox::message::CfgPrt_outProtoMask_numOfValues);
    return cc::Property::createPropertiesMap("outProtoMask", std::move(bitNames));
}

QVariantMap createProps_prtFlags()
{
    QVariantList bitNames;
    bitNames.append(QVariant());
    bitNames.append("extendedTxTimeout");
    assert(bitNames.size() == ublox::message::CfgPrt_flags_numOfValues);
    return cc::Property::createPropertiesMap("flags", std::move(bitNames));
}

QVariantMap createProps_protocolID()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "UBX");
    cc::Property::appendEnumValue(enumValues, "NMEA");
    assert(enumValues.size() == (int)ublox::field::cfg::ProtocolId::NumOfValues);
    return cc::Property::createPropertiesMap("protocolID", std::move(enumValues));
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
    assert(bitNames.size() == ublox::message::CfgNmeaField_filter_numOfValues);
    return cc::Property::createPropertiesMap("filter", std::move(bitNames));
}

QVariantMap createProps_nmeaVersion()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "NMEA version 2.1", (int)ublox::message::CfgNmea_NmeaVersion::v21);
    cc::Property::appendEnumValue(enumValues, "NMEA version 2.3", (int)ublox::message::CfgNmea_NmeaVersion::v23);
    return cc::Property::createPropertiesMap("nmeaVersion", std::move(enumValues));
}

QVariantMap createProps_nmeaFlags()
{
    QVariantList bitNames;
    bitNames.append("compat");
    bitNames.append("consider");
    assert(bitNames.size() == ublox::message::CfgNmeaField_flags_numOfValues);
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


