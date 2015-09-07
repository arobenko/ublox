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

#include "CfgRst.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgRst<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgRst<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgRst>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_navBbrMask()
{
    QVariantList bitNames;
    bitNames.append("eph");
    bitNames.append("alm");
    bitNames.append("health");
    bitNames.append("klob");
    bitNames.append("pos");
    bitNames.append("clkd");
    bitNames.append("osc");
    bitNames.append("utc");
    bitNames.append("rtc");
    bitNames.append(QVariant());
    bitNames.append(QVariant());
    bitNames.append("sfdr");
    bitNames.append("vmon");
    bitNames.append("tct");
    bitNames.append(QVariant());
    bitNames.append("aop");
    assert(bitNames.size() == ublox::message::CfgRstField_navBbrMask_numOfValues);

    return cc::Property::createPropertiesMap("navBbrMask", std::move(bitNames));
}

QVariantMap createProps_resetMode()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "Hardware Reset (Watchdog)", (int)ublox::message::CfgRst_ResetMode::Hardware);
    cc::Property::appendEnumValue(enumValues, "Controlled Software Reset", (int)ublox::message::CfgRst_ResetMode::Software);
    cc::Property::appendEnumValue(enumValues, "Controlled Software Reset (GNSS Only)", (int)ublox::message::CfgRst_ResetMode::GnssOnly);
    cc::Property::appendEnumValue(enumValues, "Hardware Reset (Watchdog) after shutdown", (int)ublox::message::CfgRst_ResetMode::HardwareAfterShutdown);
    cc::Property::appendEnumValue(enumValues, "Controlled GNSS stop", (int)ublox::message::CfgRst_ResetMode::GnssStop);
    cc::Property::appendEnumValue(enumValues, "Controlled GNSS start", (int)ublox::message::CfgRst_ResetMode::GnssStart);

    return cc::Property::createPropertiesMap("resetMode", std::move(enumValues));
}


QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_navBbrMask());
    props.append(createProps_resetMode());
    props.append(cc_plugin::field::common::props_reserved(1));

    assert(props.size() == CfgRst::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgRst::CfgRst() = default;
CfgRst::~CfgRst() = default;

CfgRst& CfgRst::operator=(const CfgRst&) = default;
CfgRst& CfgRst::operator=(CfgRst&&) = default;


const char* CfgRst::nameImpl() const
{
    static const char* Str = "CFG-RST";
    return Str;
}

const QVariantList& CfgRst::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

