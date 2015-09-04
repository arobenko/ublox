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

#include <cassert>

#include "CfgMsgPoll.h"
#include "cc_plugin/field/MsgId.h"

template class ublox::message::CfgMsgPoll<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgMsgPoll<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgMsgPoll>;

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

    assert(props.size() == CfgMsgPoll::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgMsgPoll::CfgMsgPoll() = default;
CfgMsgPoll::~CfgMsgPoll() = default;

CfgMsgPoll& CfgMsgPoll::operator=(const CfgMsgPoll&) = default;
CfgMsgPoll& CfgMsgPoll::operator=(CfgMsgPoll&&) = default;


const char* CfgMsgPoll::nameImpl() const
{
    static const char* Str = "CFG-MSG (Poll)";
    return Str;
}

const QVariantList& CfgMsgPoll::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

