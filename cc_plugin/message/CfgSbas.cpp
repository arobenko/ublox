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

#include "CfgSbas.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgSbas<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgSbas<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgSbas>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgSbasFields;

QVariantMap createProps_mode()
{
    cc::property::field::ForField<CfgSbasFields::mode> props;
    props.name("mode")
         .add("enabled")
         .add("test");
    assert(props.bits().size() == CfgSbasFields::mode::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_usage()
{
    cc::property::field::ForField<CfgSbasFields::usage> props;
    props.name("usage")
         .add("range")
         .add("diffCorr")
         .add("integrity");
    assert(props.bits().size() == CfgSbasFields::usage::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_scanmode(int idx, int base, int count)
{
    cc::property::field::BitmaskValue props;
    props.name(QString("scanmode%1").arg(idx));
    QVariantList bitNames;
    for (auto prnIdx = 0; prnIdx < count; ++prnIdx) {
        props.add(QString("PRN%1").arg(base + prnIdx));
    }
    return props.asMap();
}


QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_mode());
    props.append(createProps_usage());
    props.append(
        cc::property::field::ForField<CfgSbasFields::maxSBAS>().name("maxSBAS").asMap());
    props.append(createProps_scanmode(2, 152, CfgSbasFields::scanmode2::BitIdx_numOfValues));
    props.append(createProps_scanmode(1, 120, CfgSbasFields::scanmode1::BitIdx_numOfValues));
    assert(props.size() == CfgSbas::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgSbas::CfgSbas() = default;
CfgSbas::~CfgSbas() = default;

CfgSbas& CfgSbas::operator=(const CfgSbas&) = default;
CfgSbas& CfgSbas::operator=(CfgSbas&&) = default;


const char* CfgSbas::nameImpl() const
{
    static const char* Str = "CFG-SBAS";
    return Str;
}

const QVariantList& CfgSbas::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

