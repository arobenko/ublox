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

#include <cassert>

#include "MgaFlashAck.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaFlashAck<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaFlashAck<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaFlashAck>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaFlashAckFields;

QVariantMap createProps_ack()
{
    auto props =
        cc::property::field::ForField<MgaFlashAckFields::ack>()
            .name("ack")
            .add("ACK")
            .add("NACK (retransmit)")
            .add("NACK (give up)");
    assert(props.values().size() == (int)MgaFlashAckFields::Ack::NumOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;

    props.append(
        cc::property::field::ForField<MgaFlashAckFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaFlashAckFields::version>().name("version").asMap());
    props.append(createProps_ack());
    props.append(field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MgaFlashAckFields::sequence>().name("sequence").asMap());
    assert(props.size() == MgaFlashAck::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaFlashAck::MgaFlashAck() = default;
MgaFlashAck::~MgaFlashAck() = default;

MgaFlashAck& MgaFlashAck::operator=(const MgaFlashAck&) = default;
MgaFlashAck& MgaFlashAck::operator=(MgaFlashAck&&) = default;

const char* MgaFlashAck::nameImpl() const
{
    static const char* Str = "MGA-FLASH-ACK";
    return Str;
}

const QVariantList& MgaFlashAck::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

