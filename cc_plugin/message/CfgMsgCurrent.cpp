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

#include "CfgMsgCurrent.h"
#include "cc_plugin/field/MsgId.h"
#include "cc_plugin/field/cfg.h"

template class ublox::message::CfgMsgCurrent<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgMsgCurrent<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgMsgCurrent>;


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
    props.append(cc_plugin::field::cfg::rateProperties());

    assert(props.size() == CfgMsgCurrent::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

CfgMsgCurrent::CfgMsgCurrent() = default;
CfgMsgCurrent::~CfgMsgCurrent() = default;

CfgMsgCurrent& CfgMsgCurrent::operator=(const CfgMsgCurrent&) = default;
CfgMsgCurrent& CfgMsgCurrent::operator=(CfgMsgCurrent&&) = default;


const char* CfgMsgCurrent::nameImpl() const
{
    static const char* Str = "CFG-MSG (Current)";
    return Str;
}

const QVariantList& CfgMsgCurrent::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

