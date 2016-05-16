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

#include "CfgGnss.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgGnss<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgGnss<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgGnss>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgGnssFields;

QVariantMap createProps_numConfigBlocks()
{
    return
        cc::property::field::ForField<CfgGnssFields::numConfigBlocks>()
            .name("numConfigBlocks")
            .readOnly()
            .asMap();
}

QVariantMap createProps_gnssId()
{
    return
        cc::property::field::ForField<CfgGnssFields::gnssId>()
            .name("gnssId")
            .add("GPS", (int)CfgGnssFields::GnssId::GPS)
            .add("SBAS", (int)CfgGnssFields::GnssId::SBAS)
            .add("QZSS", (int)CfgGnssFields::GnssId::QZSS)
            .add("GLONASS", (int)CfgGnssFields::GnssId::GLONASS)
            .asMap();
}

QVariantMap createProps_flags()
{
    cc::property::field::ForField<CfgGnssFields::flags> props;
    props.name("flags")
         .add("enable");
    assert(props.bits().size() == CfgGnssFields::flags_numOfValues);
    return props.asMap();
}

QVariantMap createProps_data()
{
    cc::property::field::ForField<CfgGnssFields::block> blockProps;
    blockProps
        .add(createProps_gnssId())
        .add(cc::property::field::ForField<CfgGnssFields::resTrkCh>().name("resTrkCh").asMap())
        .add(cc::property::field::ForField<CfgGnssFields::maxTrkCh>().name("maxTrkCh").asMap())
        .add(cc_plugin::field::common::props_reserved(1))
        .add(createProps_flags());
    assert(blockProps.members().size() == CfgGnssFields::block_numOfValues);

    return
        cc::property::field::ForField<CfgGnssFields::blocksList>()
            .name("data")
            .add(blockProps.asMap())
            .serialisedHidden()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<CfgGnssFields::msgVer>().name("msgVer").asMap());
    props.append(
        cc::property::field::ForField<CfgGnssFields::numTrkChHw>().name("numTrkChHw").asMap());
    props.append(
        cc::property::field::ForField<CfgGnssFields::numTrkChUse>().name("numTrkChUse").asMap());
    props.append(createProps_numConfigBlocks());
    props.append(createProps_data());
    assert(props.size() == CfgGnss::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgGnss::CfgGnss() = default;
CfgGnss::~CfgGnss() = default;

CfgGnss& CfgGnss::operator=(const CfgGnss&) = default;
CfgGnss& CfgGnss::operator=(CfgGnss&&) = default;


const char* CfgGnss::nameImpl() const
{
    static const char* Str = "CFG-GNSS";
    return Str;
}

const QVariantList& CfgGnss::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

