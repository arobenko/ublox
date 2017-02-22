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

#include "CfgTxslot.h"

#include <cassert>

#include <QtCore/QString>

#include "cc_plugin/field/common.h"
#include "cc_plugin/field/cfg.h"

template class ublox::message::CfgTxslot<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgTxslot<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgTxslot>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgTxslotFields;

QVariantMap createProps_enable()
{
    cc::property::field::ForField<CfgTxslotFields::enable> props;
    props.name("enable")
         .add("DDC")
         .add("UART1")
         .add("UART2")
         .add("USB")
         .add("SPI");
    assert(props.bits().size() == CfgTxslotFields::enable::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_refTp()
{
    cc::property::field::ForField<CfgTxslotFields::refTp> props;
    props.name("refTp")
         .add("Timepulse")
         .add("Timepulse 2");
    assert(props.values().size() == (int)CfgTxslotFields::RefTp::NumOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<CfgTxslotFields::version>().name("version").asMap());
    props.append(createProps_enable());
    props.append(createProps_refTp());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<CfgTxslotFields::end0>().name("end0").asMap());
    props.append(
        cc::property::field::ForField<CfgTxslotFields::end1>().name("end1").asMap());
    props.append(
        cc::property::field::ForField<CfgTxslotFields::end2>().name("end2").asMap());
    assert(props.size() == CfgTxslot::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgTxslot::CfgTxslot() = default;
CfgTxslot::~CfgTxslot() = default;

CfgTxslot& CfgTxslot::operator=(const CfgTxslot&) = default;
CfgTxslot& CfgTxslot::operator=(CfgTxslot&&) = default;


const char* CfgTxslot::nameImpl() const
{
    static const char* Str = "CFG-TXSLOT";
    return Str;
}

const QVariantList& CfgTxslot::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

