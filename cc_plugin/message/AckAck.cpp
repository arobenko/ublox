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

#include "AckAck.h"
#include "cc_plugin/field/MsgId.h"

template class ublox::message::AckAck<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::AckAck<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::AckAck>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::msgIdProperties());

    assert(props.size() == AckAck::FieldIdx_numOfValues);
    return props;
}

}  // namespace

AckAck::AckAck() = default;
AckAck::~AckAck() = default;

AckAck& AckAck::operator=(const AckAck&) = default;
AckAck& AckAck::operator=(AckAck&&) = default;

const char* AckAck::nameImpl() const
{
    static const char* Str = "ACK-ACK";
    return Str;
}

const QVariantList& AckAck::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

