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

#include "CfgPrtUsb.h"
#include "cc_plugin/field/cfg.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgPrtUsb<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgPrtUsb<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgPrtUsb>;

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
    props.append(cc_plugin::field::cfg::props_readOnlyPortID());
    props.append(cc_plugin::field::common::props_reserved(0));
    props.append(cc_plugin::field::cfg::props_txReady());
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(cc_plugin::field::common::props_reserved(3));
    props.append(cc_plugin::field::cfg::props_inProtoMask());
    props.append(cc_plugin::field::cfg::props_outProtoMask());
    props.append(cc_plugin::field::common::props_reserved(4));
    props.append(cc_plugin::field::common::props_reserved(5));

    assert(props.size() == CfgPrtUsb::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgPrtUsb::CfgPrtUsb() = default;
CfgPrtUsb::~CfgPrtUsb() = default;

CfgPrtUsb& CfgPrtUsb::operator=(const CfgPrtUsb&) = default;
CfgPrtUsb& CfgPrtUsb::operator=(CfgPrtUsb&&) = default;


const char* CfgPrtUsb::nameImpl() const
{
    static const char* Str = "CFG-PRT (USB)";
    return Str;
}

const QVariantList& CfgPrtUsb::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

