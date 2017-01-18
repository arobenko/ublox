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

#include "CfgNmeaExt.h"
#include "cc_plugin/field/common.h"
#include "cc_plugin/field/cfg.h"

template class ublox::message::CfgNmeaExt<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgNmeaExt<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgNmeaExt>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgNmeaExtFields;

QVariantMap createProps_gnssToFilter()
{
    cc::property::field::ForField<CfgNmeaExtFields::gnssToFilter> props;
    props.name("gnssToFilter")
         .add("gps")
         .add("sbas")
         .add(CfgNmeaExtFields::gnssToFilter::BitIdx_qzss, "qzss")
         .add("qlonass");
    assert(props.bits().size() == CfgNmeaExtFields::gnssToFilter::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_svNumbering()
{
    cc::property::field::ForField<CfgNmeaExtFields::svNumbering> props;
    props.name("svNumbering")
         .add("Strict")
         .add("Extended");
    assert(props.values().size() == (int)CfgNmeaExtFields::SvNumbering::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_mainTalkerId()
{
    cc::property::field::ForField<CfgNmeaExtFields::mainTalkerId> props;
    props.name("mainTalkerId")
         .add("Not overridden")
         .add("GP")
         .add("GL")
         .add("GN");
    assert(props.values().size() == (int)CfgNmeaExtFields::MainTalkerId::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_gsvTalkerId()
{
    cc::property::field::ForField<CfgNmeaExtFields::gsvTalkerId> props;
    props.name("gsvTalkerId")
         .add("GNSS Specific")
         .add("Main");
    assert(props.values().size() == (int)CfgNmeaExtFields::GsvTalkerId::NumOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::cfg::props_nmeaFilter());
    props.append(cc_plugin::field::cfg::props_nmeaVersion());
    props.append(cc_plugin::field::cfg::props_nmeaNumSV());
    props.append(cc_plugin::field::cfg::props_nmeaFlags());
    props.append(createProps_gnssToFilter());
    props.append(createProps_svNumbering());
    props.append(createProps_mainTalkerId());
    props.append(createProps_gsvTalkerId());
    props.append(cc_plugin::field::common::props_reserved(0));
    assert(props.size() == CfgNmeaExt::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgNmeaExt::CfgNmeaExt() = default;
CfgNmeaExt::~CfgNmeaExt() = default;

CfgNmeaExt& CfgNmeaExt::operator=(const CfgNmeaExt&) = default;
CfgNmeaExt& CfgNmeaExt::operator=(CfgNmeaExt&&) = default;


const char* CfgNmeaExt::nameImpl() const
{
    static const char* Str = "CFG-NMEA (Extended)";
    return Str;
}

const QVariantList& CfgNmeaExt::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

