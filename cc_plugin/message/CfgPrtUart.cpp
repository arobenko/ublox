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

#include <type_traits>
#include <functional>
#include <cassert>

#include "CfgPrtUart.h"
#include "cc_plugin/field/cfg.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgPrtUart<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgPrtUart<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgPrtUart>;

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
    QVariantList charLenEnumValues;
    cc::Property::appendEnumValue(charLenEnumValues, "5bit");
    cc::Property::appendEnumValue(charLenEnumValues, "6bit");
    cc::Property::appendEnumValue(charLenEnumValues, "7bit");
    cc::Property::appendEnumValue(charLenEnumValues, "8bit");
    assert(charLenEnumValues.size() == (int)ublox::message::CfgPrtUart_BitLength::NumOfValues);
    auto charLenProps = cc::Property::createPropertiesMap("charLen", std::move(charLenEnumValues));
    cc::Property::setSerialisedHidden(charLenProps);

    QVariantList parityEnumValues;
    cc::Property::appendEnumValue(parityEnumValues, "Even", (int)ublox::message::CfgPrtUart_Parity::Even);
    cc::Property::appendEnumValue(parityEnumValues, "Odd", (int)ublox::message::CfgPrtUart_Parity::Odd);
    cc::Property::appendEnumValue(parityEnumValues, "No Parity", (int)ublox::message::CfgPrtUart_Parity::NoParity);
    cc::Property::appendEnumValue(parityEnumValues, "No Parity(2)", (int)ublox::message::CfgPrtUart_Parity::NoParity2);
    auto parityProps = cc::Property::createPropertiesMap("parity", std::move(parityEnumValues));
    cc::Property::setSerialisedHidden(parityProps);

    QVariantList nStopBitsEnumValues;
    cc::Property::appendEnumValue(nStopBitsEnumValues, "1");
    cc::Property::appendEnumValue(nStopBitsEnumValues, "1.5");
    cc::Property::appendEnumValue(nStopBitsEnumValues, "2");
    cc::Property::appendEnumValue(nStopBitsEnumValues, "0.5");
    assert(nStopBitsEnumValues.size() == (int)ublox::message::CfgPrtUart_StopBits::NumOfValues);
    auto nStopBitsProps = cc::Property::createPropertiesMap("nStopBits", std::move(nStopBitsEnumValues));
    cc::Property::setSerialisedHidden(nStopBitsProps);

    auto createReservedFunc =
        []() -> QVariantMap
        {
            QVariantMap props;
            cc::Property::setFieldHidden(props);
            return props;
        };

    QVariantList membersData;
    membersData.append(createReservedFunc());
    membersData.append(std::move(charLenProps));
    membersData.append(createReservedFunc());
    membersData.append(std::move(parityProps));
    membersData.append(std::move(nStopBitsProps));
    membersData.append(createReservedFunc());
    assert(membersData.size() == ublox::message::CfgPrtUartField_mode_numOfValues);
    return cc::Property::createPropertiesMap("mode", std::move(membersData));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::cfg::props_portID());
    props.append(cc_plugin::field::common::props_reserved(0));
    props.append(cc_plugin::field::cfg::props_txReady());
    props.append(createProps_mode());
    props.append(cc::Property::createPropertiesMap("baudRate"));
    props.append(cc_plugin::field::cfg::props_inProtoMask());
    props.append(cc_plugin::field::cfg::props_outProtoMask());
    props.append(cc_plugin::field::cfg::props_prtFlags());
    props.append(cc_plugin::field::common::props_reserved(5));

    assert(props.size() == CfgPrtUart::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgPrtUart::CfgPrtUart() = default;
CfgPrtUart::~CfgPrtUart() = default;

CfgPrtUart& CfgPrtUart::operator=(const CfgPrtUart&) = default;
CfgPrtUart& CfgPrtUart::operator=(CfgPrtUart&&) = default;


const char* CfgPrtUart::nameImpl() const
{
    static const char* Str = "CFG-PRT (UART)";
    return Str;
}

const QVariantList& CfgPrtUart::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

