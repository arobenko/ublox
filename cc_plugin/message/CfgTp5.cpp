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

QVariantMap createProps_flags()
{
    QVariantList bitNames;
    bitNames.append("active");
    bitNames.append("lockGpsFreq");
    bitNames.append("lockedOtherSet");
    bitNames.append("isFreq");
    bitNames.append("isLength");
    bitNames.append("alignToTow");
    bitNames.append("polarity");
    bitNames.append("gridUtcGps");
    assert(bitNames.size() == ublox::message::CfgTp5Field_flags_numOfValues);
    return cc::Property::createPropertiesMap("mask", std::move(bitNames));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::cfg::props_tpIdx());
    props.append(cc_plugin::field::common::props_reserved(0));
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc::Property::createPropertiesMap("antCableDelay"));
    props.append(cc::Property::createPropertiesMap("rfGroupDelay"));
    props.append(cc::Property::createPropertiesMap("frepPeriod"));
    props.append(cc::Property::createPropertiesMap("frepPeriodLock"));
    props.append(cc::Property::createPropertiesMap("pulseLenRatio"));
    props.append(cc::Property::createPropertiesMap("pulseLenRatioLock"));
    props.append(cc::Property::createPropertiesMap("userConfigDelay"));
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

