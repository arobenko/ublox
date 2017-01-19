//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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

#include <cassert>

#include "CfgUsb.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgUsb<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgUsb<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgUsb>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgUsbFields;

QVariantMap createProps_flags()
{
    cc::property::field::ForField<CfgUsbFields::flags> props;
    props.name("flags")
         .add("reEnum")
         .add("powerMode");
    assert(props.bits().size() == CfgUsbFields::flags::BitIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<CfgUsbFields::vendorID>().name("vendorID").asMap());
    props.append(
        cc::property::field::ForField<CfgUsbFields::productID>().name("productID").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(
        cc::property::field::ForField<CfgUsbFields::powerConsumption>().name("powerConsumption").asMap());
    props.append(createProps_flags());
    props.append(
        cc::property::field::ForField<CfgUsbFields::vendorString>().name("vendorString").asMap());
    props.append(
        cc::property::field::ForField<CfgUsbFields::productString>().name("productString").asMap());
    props.append(
            cc::property::field::ForField<CfgUsbFields::serialNumber>().name("serialNumber").asMap());
    assert(props.size() == CfgUsb::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgUsb::CfgUsb() = default;
CfgUsb::~CfgUsb() = default;

CfgUsb& CfgUsb::operator=(const CfgUsb&) = default;
CfgUsb& CfgUsb::operator=(CfgUsb&&) = default;


const char* CfgUsb::nameImpl() const
{
    static const char* Str = "CFG-USB";
    return Str;
}

const QVariantList& CfgUsb::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

