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

QVariantMap createNameOnlyProperties(const char* name)
{
    return cc::Property::createPropertiesMap(name);
}

QVariantMap createCharLenProperties()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "5 bit");
    cc::Property::appendEnumValue(enumValues, "6 bit");
    cc::Property::appendEnumValue(enumValues, "7 bit");
    cc::Property::appendEnumValue(enumValues, "8 bit");

    auto props = cc::Property::createPropertiesMap("Character Length", std::move(enumValues));
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantMap createParityProperties()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "Even", (int)ublox::field::cfg::Parity::Even);
    cc::Property::appendEnumValue(enumValues, "Odd", (int)ublox::field::cfg::Parity::Odd);
    cc::Property::appendEnumValue(enumValues, "No Parity", (int)ublox::field::cfg::Parity::NoParity);
    cc::Property::appendEnumValue(enumValues, "No Parity (2)", (int)ublox::field::cfg::Parity::NoParity2);

    auto props = cc::Property::createPropertiesMap("Parity", std::move(enumValues));
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantMap createStopBitProperties()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "1 Stop Bit");
    cc::Property::appendEnumValue(enumValues, "1.5 Stop Bits");
    cc::Property::appendEnumValue(enumValues, "2 Stop Bits");
    auto props = cc::Property::createPropertiesMap("Stop Bit", std::move(enumValues));
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantMap createBitOrderProperties()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "LSB First");
    cc::Property::appendEnumValue(enumValues, "MSB First");
    auto props = cc::Property::createPropertiesMap("Bit Order", std::move(enumValues));
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantMap createOversamplingProperties()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "16x");
    cc::Property::appendEnumValue(enumValues, "8x");
    auto props = cc::Property::createPropertiesMap("Oversampling", std::move(enumValues));
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantMap createPrtModeProperties()
{
    auto createHiddenBitsProperties =
        []() -> QVariantMap
        {
            auto props = cc::Property::createPropertiesMap("Reseved");
            cc::Property::setFieldHidden(props);
            return props;
        };

    QVariantList membersData;
    membersData.append(createHiddenBitsProperties());
    membersData.append(createCharLenProperties());
    membersData.append(createHiddenBitsProperties());
    membersData.append(createParityProperties());
    membersData.append(createStopBitProperties());
    membersData.append(createHiddenBitsProperties());
    membersData.append(createBitOrderProperties());
    membersData.append(createHiddenBitsProperties());
    membersData.append(createOversamplingProperties());
    membersData.append(createHiddenBitsProperties());

    return cc::Property::createPropertiesMap("Mode", std::move(membersData));
}

QVariantMap createProtoMaskProperties(const char* prefix)
{
    QVariantList bitNames;
    bitNames.append("UBX Protocol");
    bitNames.append("NMEA Protocol");
    bitNames.append("RTCM Protocol");

    static const int FullSize =
        std::numeric_limits<std::uint8_t>::digits * sizeof(std::uint16_t);
    while (bitNames.size() < (FullSize - 4)) {
        bitNames.append(QVariant());
    }

    bitNames.append("User 0 Protocol");
    bitNames.append("User 1 Protocol");
    bitNames.append("User 2 Protocol");
    bitNames.append("User 3 Protocol");

    auto name = QString("%1_proto_mask").arg(prefix);
    return cc::Property::createPropertiesMap(name, std::move(bitNames));
}

QVariantMap createPrtFlagsProperties()
{
    QVariantList bitNames;
    bitNames.append("Autobauding enabled");

    return cc::Property::createPropertiesMap("Flags", std::move(bitNames));
}

QVariantMap createProtocolIdProperties()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "UBX Protocol", (int)ublox::field::cfg::ProtocolIdVal::Ubx);
    cc::Property::appendEnumValue(enumValues, "NMEA Protocol", (int)ublox::field::cfg::ProtocolIdVal::Nmea);
    cc::Property::appendEnumValue(enumValues, "RTCM Protocol", (int)ublox::field::cfg::ProtocolIdVal::Rtcm);
    cc::Property::appendEnumValue(enumValues, "RAW Protocol", (int)ublox::field::cfg::ProtocolIdVal::Raw);
    cc::Property::appendEnumValue(enumValues, "User 0 Protocol", (int)ublox::field::cfg::ProtocolIdVal::User0);
    cc::Property::appendEnumValue(enumValues, "User 1 Protocol", (int)ublox::field::cfg::ProtocolIdVal::User1);
    cc::Property::appendEnumValue(enumValues, "User 2 Protocol", (int)ublox::field::cfg::ProtocolIdVal::User2);
    cc::Property::appendEnumValue(enumValues, "User 3 Protocol", (int)ublox::field::cfg::ProtocolIdVal::User3);

    return cc::Property::createPropertiesMap("ProtocolID", std::move(enumValues));
}

QVariantMap createNavBbrProperties()
{
    QVariantList bitNames;
    bitNames.append("Ephemeris");
    bitNames.append("Almanach");
    bitNames.append("Health");
    bitNames.append("Klobuchart");
    bitNames.append("Position");
    bitNames.append("Clock Drift");
    bitNames.append("Oscilator Parameter");
    bitNames.append("UTC Correction Parameters");
    bitNames.append("RTC");

    return cc::Property::createPropertiesMap("nav_bbr", std::move(bitNames));
}

QVariantMap createResetProperties()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "Hardware Reset (Watchdog)", (int)ublox::field::cfg::ResetType::Hardware);
    cc::Property::appendEnumValue(enumValues, "Controlled Software Reset", (int)ublox::field::cfg::ResetType::Software);
    cc::Property::appendEnumValue(enumValues, "Controlled Software Reset (GPS Only)", (int)ublox::field::cfg::ResetType::GpsOnly);
    cc::Property::appendEnumValue(enumValues, "Controlled GPS stop", (int)ublox::field::cfg::ResetType::GpsStop);
    cc::Property::appendEnumValue(enumValues, "Controlled GPS start", (int)ublox::field::cfg::ResetType::GpsStart);

    return cc::Property::createPropertiesMap("Reset", std::move(enumValues));
}

}  // namespace

const QVariantMap& portIdProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("PortID");
    return Props;
}

const QVariantMap& prtModeProperties()
{
    static const QVariantMap Props = createPrtModeProperties();
    return Props;
}

const QVariantMap& baudrateProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Baudrate");
    return Props;
}

const QVariantMap& inProtoMaskProperties()
{
    static const QVariantMap Props = createProtoMaskProperties("In");
    return Props;
}

const QVariantMap& outProtoMaskProperties()
{
    static const QVariantMap Props = createProtoMaskProperties("Out");
    return Props;
}

const QVariantMap& prtFlagsProperties()
{
    static const QVariantMap Props = createPrtFlagsProperties();
    return Props;
}

const QVariantMap& rateProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Rate");
    return Props;
}

QVariantMap rateProperties(unsigned idx)
{
    auto name = QString("Rate%1").arg(idx, 1, 10, QChar('0'));
    return cc::Property::createPropertiesMap(name);
}

const QVariantMap& protocolIdProperties()
{
    static const QVariantMap Props = createProtocolIdProperties();
    return Props;
}

QVariantMap infMsgMaskProperties(unsigned idx)
{
    QVariantList bitNames;
    bitNames.append("INF-ERROR");
    bitNames.append("INF-WARNING");
    bitNames.append("INF-NOTICE");
    bitNames.append("INF-TEST");
    bitNames.append("INF-DEBUG");
    bitNames.append(QVariant());
    bitNames.append(QVariant());
    bitNames.append("INF-USER");

    auto name = QString("INFMSG_mask%1").arg(idx, 1, 10, QChar('0'));
    return cc::Property::createPropertiesMap(name, std::move(bitNames));
}

const QVariantMap& navBbrProperties()
{
    static const QVariantMap Props = createNavBbrProperties();
    return Props;
}

const QVariantMap& resetProperties()
{
    static const QVariantMap Props = createResetProperties();
    return Props;
}

const QVariantMap& datumNumProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Datum#");
    return Props;
}

const QVariantMap& datumProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Datum");
    return Props;
}

const QVariantMap& majXProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("majX");
    return Props;
}

const QVariantMap& flatProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("flat");
    return Props;
}

const QVariantMap& dXProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("dX");
    return Props;
}

const QVariantMap& dYProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("dY");
    return Props;
}

const QVariantMap& dZProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("dZ");
    return Props;
}

const QVariantMap& rotXProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("rotX");
    return Props;
}

const QVariantMap& rotYProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("rotY");
    return Props;
}

const QVariantMap& rotZProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("rotZ");
    return Props;
}

const QVariantMap& scaleProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("scale");
    return Props;
}

const QVariantMap& intervalProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("interval");
    return Props;
}

const QVariantMap& lengthProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("length");
    return Props;
}

const QVariantMap& statusProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("status");
    return Props;
}

const QVariantMap& timeRefProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("time_ref");
    return Props;
}

const QVariantMap& antennaCableDelayProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("antenna_cable_delay");
    return Props;
}

const QVariantMap& rfGroupDelayProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("RF_group_delay");
    return Props;
}

const QVariantMap& userDelayProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("user_delay");
    return Props;
}

const QVariantMap& measProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Meas");
    return Props;
}

const QVariantMap& navProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Nav");
    return Props;
}

const QVariantMap& timeProperties()
{
    static const QVariantMap Props = createNameOnlyProperties("Time");
    return Props;
}

}  // namespace cfg

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox


