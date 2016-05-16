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

using ublox::message::CfgPrtUartFields;

QVariantMap createProps_mode()
{
    cc::property::field::ForField<CfgPrtUartFields::charLen> charLenProps;
    charLenProps.name("charLen")
                .add("5bit")
                .add("6bit")
                .add("7bit")
                .add("8bit")
                .serialisedHidden();
    assert(charLenProps.values().size() == (int)CfgPrtUartFields::CharLen::NumOfValues);

    cc::property::field::ForField<CfgPrtUartFields::parity> parityProps;
    parityProps.name("parity")
               .add("Even", (int)CfgPrtUartFields::Parity::Even)
               .add("Odd", (int)CfgPrtUartFields::Parity::Odd)
               .add("No Parity", (int)CfgPrtUartFields::Parity::NoParity)
               .add("No Parity(2)", (int)CfgPrtUartFields::Parity::NoParity2)
               .serialisedHidden();

    cc::property::field::ForField<CfgPrtUartFields::nStopBits> nStopBitsProps;
    nStopBitsProps.name("nStopBits")
                  .add("1")
                  .add("1.5")
                  .add("2")
                  .add("0.5")
                  .serialisedHidden();
    assert(nStopBitsProps.values().size() == (int)CfgPrtUartFields::StopBits::NumOfValues);

    auto createReservedFunc =
        []() -> QVariantMap
        {
            return cc::property::field::IntValue().hidden().asMap();
        };

    cc::property::field::ForField<CfgPrtUartFields::mode> props;
    props.name("mode")
         .add(createReservedFunc())
         .add(charLenProps.asMap())
         .add(createReservedFunc())
         .add(parityProps.asMap())
         .add(nStopBitsProps.asMap())
         .add(createReservedFunc());
    assert(props.members().size() == CfgPrtUartFields::mode_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::cfg::props_portID());
    props.append(cc_plugin::field::common::props_reserved(0));
    props.append(cc_plugin::field::cfg::props_txReady());
    props.append(createProps_mode());
    props.append(
        cc::property::field::ForField<CfgPrtUartFields::baudRate>().name("baudRate").asMap());
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

