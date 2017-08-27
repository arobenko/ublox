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

#include "CfgNmeaExtV1.h"
#include "cc_plugin/field/common.h"
#include "cc_plugin/field/cfg.h"

template class ublox::message::CfgNmeaExtV1<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgNmeaExtV1<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgNmeaExtV1>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgNmeaExtV1Fields;

QVariantMap createProps_nmeaVersion()
{
    return
        cc::property::field::ForField<ublox::message::CfgNmeaExtV1Fields::nmeaVersion>()
            .name("nmeaVersion")
            .add("NMEA version 2.1", (int)ublox::message::CfgNmeaExtV1Fields::NmeaVersion::v21)
            .add("NMEA version 2.3", (int)ublox::message::CfgNmeaExtV1Fields::NmeaVersion::v23)
            .add("NMEA version 4.0", (int)ublox::message::CfgNmeaExtV1Fields::NmeaVersion::v40)
            .add("NMEA version 4.1", (int)ublox::message::CfgNmeaExtV1Fields::NmeaVersion::v41)
            .asMap();
}

QVariantMap createProps_flags()
{
    cc::property::field::ForField<ublox::message::CfgNmeaExtV1Fields::flags> props;
    props.name("flags")
         .add("compat")
         .add("consider")
         .add("limit82")
         .add("highPrec");
    assert(props.bits().size() == ublox::message::CfgNmeaExtV1Fields::flags::BitIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::cfg::props_nmeaFilter());
    props.append(createProps_nmeaVersion());
    props.append(cc_plugin::field::cfg::props_nmeaNumSV());
    props.append(createProps_flags());
    props.append(cc_plugin::field::cfg::props_gnssToFilter());
    props.append(cc_plugin::field::cfg::props_svNumbering());
    props.append(cc_plugin::field::cfg::props_mainTalkerId());
    props.append(cc_plugin::field::cfg::props_gsvTalkerId());
    props.append(cc::property::field::ForField<CfgNmeaExtV1Fields::version>().name("version").asMap());
    props.append(cc::property::field::ForField<CfgNmeaExtV1Fields::bdsTalkerId<> >().name("bdsTalkerId").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc_plugin::field::common::props_reserved(1));
    assert(props.size() == CfgNmeaExtV1::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgNmeaExtV1::CfgNmeaExtV1() = default;
CfgNmeaExtV1::~CfgNmeaExtV1() = default;

CfgNmeaExtV1& CfgNmeaExtV1::operator=(const CfgNmeaExtV1&) = default;
CfgNmeaExtV1& CfgNmeaExtV1::operator=(CfgNmeaExtV1&&) = default;


const char* CfgNmeaExtV1::nameImpl() const
{
    static const char* Str = "CFG-NMEA (Extended V1)";
    return Str;
}

const QVariantList& CfgNmeaExtV1::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

