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


}  // namespace cfg

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox


