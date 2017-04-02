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

#include "MgaGpsEph.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaGpsEph<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaGpsEph<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaGpsEph>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaGpsEphFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::version>().name("version").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::svId>().name("svId").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::fitInterval>().name("fitInterval").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::uraIndex>().name("uraIndex").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::svHealth>().name("svHealth").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::tgd>().name("tgd").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::iodc>().name("iodc").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::toc>().name("toc").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::af2>().name("af2").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::af1>().name("af1").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::af0>().name("af0").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::crs>().name("crs").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::deltaN>().name("deltaN").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::m0>().name("m0").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::cuc>().name("cuc").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::cus>().name("cus").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::e>().name("e").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::sqrtA>().name("sqrtA").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::toe>().name("toe").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::cic>().name("cic").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::omega0>().name("omega0").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::cis>().name("cis").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::crc>().name("crc").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::i0>().name("i0").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::omega>().name("omega").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::omegaDot>().name("omegaDot").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsEphFields::idot>().name("idot").asMap());
    props.append(cc_plugin::field::common::props_reserved(3));

    assert(props.size() == MgaGpsEph::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaGpsEph::MgaGpsEph() = default;
MgaGpsEph::~MgaGpsEph() = default;

MgaGpsEph& MgaGpsEph::operator=(const MgaGpsEph&) = default;
MgaGpsEph& MgaGpsEph::operator=(MgaGpsEph&&) = default;

const char* MgaGpsEph::nameImpl() const
{
    static const char* Str = "MGA-GPS-EPH";
    return Str;
}

const QVariantList& MgaGpsEph::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

