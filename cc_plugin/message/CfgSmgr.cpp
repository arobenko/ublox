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

#include "CfgSmgr.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgSmgr<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgSmgr<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgSmgr>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgSmgrFields;

QVariantMap createProps_messageCfg()
{
    auto props =
        cc::property::field::ForField<CfgSmgrFields::messageCfg>()
            .name("messageCfg")
            .add("measInternal")
            .add("measGNSS")
            .add("measEXTINT0")
            .add("measEXTINT1");
    assert(props.bits().size() == CfgSmgrFields::messageCfg::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_flagsLow()
{
    auto props =
        cc::property::field::ForField<CfgSmgrFields::flagsLow>()
            .name("flags")
            .serialisedHidden()
            .add("disableInternal")
            .add("disableExternal")
            .add("preferenceMode")
            .add("enableGNSS")
            .add("enableEXTINT0")
            .add("enableEXTINT1")
            .add("enableHostMeasInt")
            .add("enableHostMeasExt")
            .add(CfgSmgrFields::flagsLow::BitIdx_useAnyFix, "useAnyFix")
            .add("disableMaxSlewRate")
            .add("issueFreqWarning")
            .add("issueTimeWarning");
    assert(props.bits().size() == CfgSmgrFields::flagsLow::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_TPCoherent()
{
    auto props =
        cc::property::field::ForField<CfgSmgrFields::TPCoherent>()
            .name("TPCoherent")
            .serialisedHidden()
            .add("Coherent pulses")
            .add("Non-coherent pulses")
            .add("Post-initialization");
    assert(props.values().size() == (int)CfgSmgrFields::TPCoherentVal::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_flagsHigh()
{
    auto props =
        cc::property::field::ForField<CfgSmgrFields::flagsHigh>()
            .serialisedHidden()
            .add("disableOffset");
    assert(props.bits().size() == CfgSmgrFields::flagsHigh::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_flags()
{
    auto props =
        cc::property::field::ForField<CfgSmgrFields::flags>()
            .add(createProps_flagsLow())
            .add(createProps_TPCoherent())
            .add(createProps_flagsHigh());
    assert(props.members().size() == CfgSmgrFields::flags::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<CfgSmgrFields::version>().name("version").asMap());
    props.append(
        cc::property::field::ForField<CfgSmgrFields::minGNSSFix>().name("minGNSSFix").asMap());
    props.append(
        cc::property::field::ForField<CfgSmgrFields::maxFreqChangeRate>().name("maxFreqChangeRate").asMap());
    props.append(
        cc::property::field::ForField<CfgSmgrFields::maxPhaseCorrRate>().name("maxPhaseCorrRate").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<CfgSmgrFields::freqTolerance>().name("freqTolerance").asMap());
    props.append(
        cc::property::field::ForField<CfgSmgrFields::timeTolerance>().name("timeTolerance").asMap());
    props.append(createProps_messageCfg());
    props.append(
        cc::property::field::ForField<CfgSmgrFields::maxSlewRate>().name("maxSlewRate").asMap());
    props.append(createProps_flags());


    assert(props.size() == CfgSmgr::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgSmgr::CfgSmgr() = default;
CfgSmgr::~CfgSmgr() = default;

CfgSmgr& CfgSmgr::operator=(const CfgSmgr&) = default;
CfgSmgr& CfgSmgr::operator=(CfgSmgr&&) = default;


const char* CfgSmgr::nameImpl() const
{
    static const char* Str = "CFG-SMGR";
    return Str;
}

const QVariantList& CfgSmgr::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

