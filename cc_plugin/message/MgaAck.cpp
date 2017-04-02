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

#include "MgaAck.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaAck<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaAck<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaAck>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaAckFields;

QVariantMap createProps_type()
{
    auto props =
        cc::property::field::ForField<MgaAckFields::type>()
            .name("type")
            .add("Not used")
            .add("Accepted");
    assert(props.values().size() == (int)MgaAckFields::Type::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_infoCode()
{
    auto props =
        cc::property::field::ForField<MgaAckFields::infoCode>()
            .name("infoCode")
            .add("Data accepted")
            .add("No time")
            .add("Bad version")
            .add("Bad size")
            .add("Database error")
            .add("Not ready")
            .add("Unknown type");

    assert(props.values().size() == (int)MgaAckFields::InfoCode::NumOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_type());
    props.append(
        cc::property::field::ForField<MgaAckFields::version>().name("version").asMap());
    props.append(createProps_infoCode());
    props.append(
        cc::property::field::ForField<MgaAckFields::msgId>().name("msgId").asMap());
    props.append(
        cc::property::field::ForField<MgaAckFields::msgPayloadStart>().name("msgPayloadStart").asMap());

    assert(props.size() == MgaAck::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaAck::MgaAck() = default;
MgaAck::~MgaAck() = default;

MgaAck& MgaAck::operator=(const MgaAck&) = default;
MgaAck& MgaAck::operator=(MgaAck&&) = default;

const char* MgaAck::nameImpl() const
{
    static const char* Str = "MGA-ACK";
    return Str;
}

const QVariantList& MgaAck::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

