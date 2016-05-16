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

QVariantMap createProps_flags()
{
    cc::property::field::ForField<CfgTp5Fields::flags> props;
    props.name("flags")
         .add("active")
         .add("lockGpsFreq")
         .add("lockedOtherSet")
         .add("isFreq")
         .add("isLength")
         .add("alignToTow")
         .add("polarity")
         .add("gridUtcGps");
    assert(props.bits().size() == CfgTp5Fields::flags_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::cfg::props_tpIdx());
    props.append(cc_plugin::field::common::props_reserved(0));
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<CfgTp5Fields::antCableDelay>().name("antCableDelay").asMap());
    props.append(
        cc::property::field::ForField<CfgTp5Fields::rfGroupDelay>().name("rfGroupDelay").asMap());
    props.append(
        cc::property::field::ForField<CfgTp5Fields::freqPeriod>().name("freqPeriod").asMap());
    props.append(
        cc::property::field::ForField<CfgTp5Fields::freqPeriodLock>().name("freqPeriodLock").asMap());
    props.append(
        cc::property::field::ForField<CfgTp5Fields::pulseLenRatio>().name("pulseLenRatio").asMap());
    props.append(
        cc::property::field::ForField<CfgTp5Fields::pulseLenRatioLock>().name("pulseLenRatioLock").asMap());
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

