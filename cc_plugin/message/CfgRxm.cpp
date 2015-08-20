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

#include "CfgRxm.h"
#include "cc_plugin/field/cfg.h"
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

QVariantMap createGpsModeProperties()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "Normal");
    cc::Property::appendEnumValue(enumValues, "Fast Acquisition");
    cc::Property::appendEnumValue(enumValues, "High Acquisition");
    cc::Property::appendEnumValue(enumValues, "Auto");

    return cc::Property::createPropertiesMap("gps_mode", std::move(enumValues));
}

QVariantMap createLowPowerModeProperties()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "Continuous Tracking");
    cc::Property::appendEnumValue(enumValues, "Fix Now");

    return cc::Property::createPropertiesMap("lp_mode", std::move(enumValues));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createGpsModeProperties());
    props.append(createLowPowerModeProperties());

    assert(props.size() == CfgRxm::FieldIdx_NumOfValues);
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

