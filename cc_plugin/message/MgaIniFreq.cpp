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

#include "MgaIniFreq.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaIniFreq<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaIniFreq<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaIniFreq>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaIniFreqFields;

QVariantMap createProps_source()
{
    auto props =
        cc::property::field::ForField<MgaIniFreqFields::source>()
            .name("source")
            .serialisedHidden()
            .add("EXTINT0")
            .add("EXTINT1");

    assert(props.values().size() == (int)MgaIniFreqFields::Source::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_flagsBits()
{
    auto props =
        cc::property::field::ForField<MgaIniFreqFields::flagsBits>()
            .serialisedHidden()
            .add("fall");

    assert(props.bits().size() == (int)MgaIniFreqFields::flagsBits::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_flags()
{
    auto props =
        cc::property::field::ForField<MgaIniFreqFields::flags>()
            .name("flags")
            .add(createProps_source())
            .add(createProps_flagsBits());
    assert(props.members().size() == MgaIniFreqFields::flags::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_freq()
{
    return
        cc::property::field::ForField<MgaIniFreqFields::freq>()
            .name("freq")
            .scaledDecimals(2)
            .asMap();
}


QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaIniFreqFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaIniFreqFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_flags());
    props.append(createProps_freq());
    props.append(
        cc::property::field::ForField<MgaIniFreqFields::freqAcc>().name("freqAcc").asMap());
    assert(props.size() == MgaIniFreq::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaIniFreq::MgaIniFreq() = default;
MgaIniFreq::~MgaIniFreq() = default;

MgaIniFreq& MgaIniFreq::operator=(const MgaIniFreq&) = default;
MgaIniFreq& MgaIniFreq::operator=(MgaIniFreq&&) = default;

const char* MgaIniFreq::nameImpl() const
{
    static const char* Str = "MGA-INI-FREQ";
    return Str;
}

const QVariantList& MgaIniFreq::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

