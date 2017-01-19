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

#include "CfgRxm.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgRxm<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgRxm<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgRxm>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgRxmFields;

QVariantMap createProps_lpMode()
{
    return
        cc::property::field::ForField<CfgRxmFields::lpMode>()
            .name("lpMode")
            .add("Max Performance", (int)CfgRxmFields::LowPowerMode::MaxPerformance)
            .add("Power Save", (int)CfgRxmFields::LowPowerMode::PowerSave)
            .add("Eco", (int)CfgRxmFields::LowPowerMode::Eco)
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_lpMode());

    assert(props.size() == CfgRxm::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgRxm::CfgRxm() = default;
CfgRxm::~CfgRxm() = default;

CfgRxm& CfgRxm::operator=(const CfgRxm&) = default;
CfgRxm& CfgRxm::operator=(CfgRxm&&) = default;


const char* CfgRxm::nameImpl() const
{
    static const char* Str = "CFG-RXM";
    return Str;
}

const QVariantList& CfgRxm::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

