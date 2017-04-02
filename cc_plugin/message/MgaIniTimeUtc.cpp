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

#include "MgaIniTimeUtc.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaIniTimeUtc<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaIniTimeUtc<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaIniTimeUtc>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaIniTimeUtcFields;

QVariantMap createProps_source()
{
    auto props =
        cc::property::field::ForField<MgaIniTimeUtcFields::source>()
            .name("source")
            .serialisedHidden()
            .add("none")
            .add("EXTINT0")
            .add("EXTINT1");
    assert(props.values().size() == (int)MgaIniTimeUtcFields::Source::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_flags()
{
    auto props =
        cc::property::field::ForField<MgaIniTimeUtcFields::flags>()
            .serialisedHidden()
            .add("fall")
            .add("last");
    assert(props.bits().size() == (int)MgaIniTimeUtcFields::flags::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_ref()
{
    auto props =
        cc::property::field::ForField<MgaIniTimeUtcFields::ref>()
            .name("ref")
            .add(createProps_source())
            .add(createProps_flags());
    assert(props.members().size() == (int)MgaIniTimeUtcFields::ref::FieldIdx_numOfValues);
    return props.asMap();
}


QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaIniTimeUtcFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaIniTimeUtcFields::version>().name("version").asMap());
    props.append(createProps_ref());
    props.append(
        cc::property::field::ForField<MgaIniTimeUtcFields::leapSecs>().name("leapSecs").asMap());
    props.append(
        cc::property::field::ForField<MgaIniTimeUtcFields::year>().name("year").asMap());
    props.append(
        cc::property::field::ForField<MgaIniTimeUtcFields::month>().name("month").asMap());
    props.append(
        cc::property::field::ForField<MgaIniTimeUtcFields::day>().name("day").asMap());
    props.append(
        cc::property::field::ForField<MgaIniTimeUtcFields::hour>().name("hour").asMap());
    props.append(
        cc::property::field::ForField<MgaIniTimeUtcFields::minute>().name("minute").asMap());
    props.append(
        cc::property::field::ForField<MgaIniTimeUtcFields::second>().name("second").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MgaIniTimeUtcFields::ns>().name("ns").asMap());
    props.append(
        cc::property::field::ForField<MgaIniTimeUtcFields::tAccS>().name("tAccS").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(
        cc::property::field::ForField<MgaIniTimeUtcFields::tAccNs>().name("tAccNs").asMap());

    assert(props.size() == MgaIniTimeUtc::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaIniTimeUtc::MgaIniTimeUtc() = default;
MgaIniTimeUtc::~MgaIniTimeUtc() = default;

MgaIniTimeUtc& MgaIniTimeUtc::operator=(const MgaIniTimeUtc&) = default;
MgaIniTimeUtc& MgaIniTimeUtc::operator=(MgaIniTimeUtc&&) = default;

const char* MgaIniTimeUtc::nameImpl() const
{
    static const char* Str = "MGA-INI-TIME_UTC";
    return Str;
}

const QVariantList& MgaIniTimeUtc::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

