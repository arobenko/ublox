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

#include "MgaIniTimeGnss.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaIniTimeGnss<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaIniTimeGnss<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaIniTimeGnss>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaIniTimeGnssFields;

QVariantMap createProps_source()
{
    auto props =
        cc::property::field::ForField<MgaIniTimeGnssFields::source>()
            .name("source")
            .serialisedHidden()
            .add("none")
            .add("EXTINT0")
            .add("EXTINT1");
    assert(props.values().size() == (int)MgaIniTimeGnssFields::Source::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_flags()
{
    auto props =
        cc::property::field::ForField<MgaIniTimeGnssFields::flags>()
            .serialisedHidden()
            .add("fall")
            .add("last");
    assert(props.bits().size() == (int)MgaIniTimeGnssFields::flags::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_ref()
{
    auto props =
        cc::property::field::ForField<MgaIniTimeGnssFields::ref>()
            .name("ref")
            .add(createProps_source())
            .add(createProps_flags());
    assert(props.members().size() == (int)MgaIniTimeGnssFields::ref::FieldIdx_numOfValues);
    return props.asMap();
}


QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaIniTimeGnssFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaIniTimeGnssFields::version>().name("version").asMap());
    props.append(createProps_ref());
    props.append(cc_plugin::field::common::props_gnssId());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MgaIniTimeGnssFields::week>().name("week").asMap());
    props.append(
        cc::property::field::ForField<MgaIniTimeGnssFields::tow>().name("tow").asMap());
    props.append(
        cc::property::field::ForField<MgaIniTimeGnssFields::ns>().name("ns").asMap());
    props.append(
        cc::property::field::ForField<MgaIniTimeGnssFields::tAccS>().name("tAccS").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(
        cc::property::field::ForField<MgaIniTimeGnssFields::tAccNs>().name("tAccNs").asMap());

    assert(props.size() == MgaIniTimeGnss::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaIniTimeGnss::MgaIniTimeGnss() = default;
MgaIniTimeGnss::~MgaIniTimeGnss() = default;

MgaIniTimeGnss& MgaIniTimeGnss::operator=(const MgaIniTimeGnss&) = default;
MgaIniTimeGnss& MgaIniTimeGnss::operator=(MgaIniTimeGnss&&) = default;

const char* MgaIniTimeGnss::nameImpl() const
{
    static const char* Str = "MGA-INI-TIME_GNSS";
    return Str;
}

const QVariantList& MgaIniTimeGnss::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

