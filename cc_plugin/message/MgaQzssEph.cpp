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

#include "MgaQzssEph.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaQzssEph<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaQzssEph<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaQzssEph>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaQzssEphFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::version>().name("version").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::svId>().name("svId").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::fitInterval>().name("fitInterval").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::uraIndex>().name("uraIndex").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::svHealth>().name("svHealth").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::tgd>().name("tgd").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::iodc>().name("iodc").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::toc>().name("toc").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::af2>().name("af2").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::af1>().name("af1").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::af0>().name("af0").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::crs>().name("crs").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::deltaN>().name("deltaN").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::m0>().name("m0").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::cuc>().name("cuc").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::cus>().name("cus").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::e>().name("e").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::sqrtA>().name("sqrtA").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::toe>().name("toe").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::cic>().name("cic").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::omega0>().name("omega0").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::cis>().name("cis").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::crc>().name("crc").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::i0>().name("i0").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::omega>().name("omega").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::omegaDot>().name("omegaDot").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssEphFields::idot>().name("idot").asMap());
    props.append(cc_plugin::field::common::props_reserved(3));

    assert(props.size() == MgaQzssEph::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaQzssEph::MgaQzssEph() = default;
MgaQzssEph::~MgaQzssEph() = default;

MgaQzssEph& MgaQzssEph::operator=(const MgaQzssEph&) = default;
MgaQzssEph& MgaQzssEph::operator=(MgaQzssEph&&) = default;

const char* MgaQzssEph::nameImpl() const
{
    static const char* Str = "MGA-QZSS-EPH";
    return Str;
}

const QVariantList& MgaQzssEph::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

