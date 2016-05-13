//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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

using ublox::message::CfgRstFields;

QVariantMap createProps_navBbrMask()
{
    cc::property::field::ForField<CfgRstFields::navBbrMask> props;
    props.name("navBbrMask")
         .add("eph")
         .add("alm")
         .add("health")
         .add("klob")
         .add("pos")
         .add("clkd")
         .add("osc")
         .add("utc")
         .add("rtc")
         .add(CfgRstFields::navBbrMask_sfdr, "sfdr")
         .add("vmon")
         .add("tct")
         .add(CfgRstFields::navBbrMask_aop, "aop");
    assert(props.bits().size() == CfgRstFields::navBbrMask_numOfValues);
    return props.asMap();
}

QVariantMap createProps_resetMode()
{
    return
        cc::property::field::ForField<CfgRstFields::resetMode>()
            .name("resetMode")
            .add("Hardware Reset (Watchdog)", (int)CfgRstFields::ResetMode::Hardware)
            .add("Controlled Software Reset", (int)CfgRstFields::ResetMode::Software)
            .add("Controlled Software Reset (GNSS Only)", (int)CfgRstFields::ResetMode::GnssOnly)
            .add("Hardware Reset (Watchdog) after shutdown", (int)CfgRstFields::ResetMode::HardwareAfterShutdown)
            .add("Controlled GNSS stop", (int)CfgRstFields::ResetMode::GnssStop)
            .add("Controlled GNSS start", (int)CfgRstFields::ResetMode::GnssStart)
            .asMap();
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

