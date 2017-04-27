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

#include "CfgTp5.h"

#include <cassert>

#include <QtCore/QString>

#include "cc_plugin/field/common.h"
#include "cc_plugin/field/cfg.h"

template class ublox::message::CfgTp5<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgTp5<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgTp5>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgTp5Fields;

QVariantMap createProps_optIntValue(const QString& name)
{
    return
        cc::property::field::Optional()
            .name(name)
            .uncheckable()
            .field(cc::property::field::IntValue().name(name).asMap())
            .asMap();
}

QVariantMap createProps_freqPeriod()
{
    auto props =
        cc::property::field::ForField<CfgTp5Fields::freqPeriod>()
            .name("freqPeriod")
            .serialisedHidden()
            .add(createProps_optIntValue("freq"))
            .add(createProps_optIntValue("period"));

    assert(props.members().size() == CfgTp5Fields::freqPeriod::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_freqPeriodLock()
{
    auto props =
        cc::property::field::ForField<CfgTp5Fields::freqPeriodLock>()
            .name("freqPeriodLock")
            .serialisedHidden()
            .add(createProps_optIntValue("freqLock"))
            .add(createProps_optIntValue("periodLock"));

    assert(props.members().size() == CfgTp5Fields::freqPeriodLock::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_pulseLenRatio()
{
    auto props =
        cc::property::field::ForField<CfgTp5Fields::pulseLenRatio>()
            .name("pulseLenRatio")
            .serialisedHidden()
            .add(createProps_optIntValue("pulseLen"))
            .add(createProps_optIntValue("ratio"));

    assert(props.members().size() == CfgTp5Fields::pulseLenRatio::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_pulseLenRatioLock()
{
    auto props =
        cc::property::field::ForField<CfgTp5Fields::pulseLenRatio>()
            .name("pulseLenRatioLock")
            .serialisedHidden()
            .add(createProps_optIntValue("pulseLenLock"))
            .add(createProps_optIntValue("ratioLock"));

    assert(props.members().size() == CfgTp5Fields::pulseLenRatioLock::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_flagsLow()
{
    cc::property::field::ForField<CfgTp5Fields::flagsLow> props;
    props.name("flags")
         .serialisedHidden()
         .add("active")
         .add("lockGnssFreq")
         .add("lockedOtherSet")
         .add("isFreq")
         .add("isLength")
         .add("alignToTow")
         .add("polarity");
    assert(props.bits().size() == CfgTp5Fields::flagsLow::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_gridUtcGnss()
{
    cc::property::field::ForField<CfgTp5Fields::gridUtcGnss> props;
    props.name("gridUtcGnss")
         .serialisedHidden()
         .add("UTC")
         .add("GPS")
         .add("GLONASS")
         .add("BeiDou")
         .add("Galileo");
    assert(props.values().size() == (int)CfgTp5Fields::GridUtcGnss::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_syncMode()
{
    cc::property::field::ForField<CfgTp5Fields::syncMode> props;
    props.name("syncMode")
         .serialisedHidden()
         .add("0")
         .add("1");
    assert(props.values().size() == (int)CfgTp5Fields::SyncMode::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_flags()
{
    cc::property::field::ForField<CfgTp5Fields::flags> props;
    props.add(createProps_flagsLow())
         .add(createProps_gridUtcGnss())
         .add(createProps_syncMode())
         .add(cc::property::field::IntValue().hidden().asMap());
    assert(props.members().size() == CfgTp5Fields::flags::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::cfg::props_tpIdx());
    props.append(
        cc::property::field::ForField<CfgTp5Fields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<CfgTp5Fields::antCableDelay>().name("antCableDelay").asMap());
    props.append(
        cc::property::field::ForField<CfgTp5Fields::rfGroupDelay>().name("rfGroupDelay").asMap());
    props.append(createProps_freqPeriod());
    props.append(createProps_freqPeriodLock());
    props.append(createProps_pulseLenRatio());
    props.append(createProps_pulseLenRatioLock());
    props.append(
        cc::property::field::ForField<CfgTp5Fields::userConfigDelay>().name("userConfigDelay").asMap());
    props.append(createProps_flags());
    assert(props.size() == CfgTp5::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgTp5::CfgTp5() = default;
CfgTp5::~CfgTp5() = default;

CfgTp5& CfgTp5::operator=(const CfgTp5&) = default;
CfgTp5& CfgTp5::operator=(CfgTp5&&) = default;


const char* CfgTp5::nameImpl() const
{
    static const char* Str = "CFG-TP5";
    return Str;
}

const QVariantList& CfgTp5::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

