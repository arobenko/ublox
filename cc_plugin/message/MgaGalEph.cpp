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

#include "MgaGalEph.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaGalEph<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaGalEph<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaGalEph>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaGalEphFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaGalEphFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::version>().name("version").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::svId>().name("svId").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MgaGalEphFields::iodNav>().name("iodNav").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::deltaN>().name("deltaN").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::m0>().name("m0").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::e>().name("e").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::sqrtA>().name("sqrtA").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::omega0>().name("omega0").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::i0>().name("i0").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::omega>().name("omega").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::omegaDot>().name("omegaDot").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::iDot>().name("iDot").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::cuc>().name("cuc").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::cus>().name("cus").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::crc>().name("crc").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::crs>().name("crs").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::cic>().name("cic").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::cis>().name("cis").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::toe>().name("toe").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::af0>().name("af0").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::af1>().name("af1").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::af2>().name("af2").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::sisaIndexE1E5b>().name("sisaIndexE1E5b").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::toc>().name("toc").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::bgdE1E5b>().name("bgdE1E5b").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(
        cc::property::field::ForField<MgaGalEphFields::healthE1B>().name("healthE1B").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::dataValidityE1B>().name("dataValidityE1B").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::healthE5B>().name("healthE5B").asMap());
    props.append(
        cc::property::field::ForField<MgaGalEphFields::dataValidityE5B>().name("dataValidityE5B").asMap());
    props.append(cc_plugin::field::common::props_reserved(3));

    //assert(props.size() == MgaGalEph::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaGalEph::MgaGalEph() = default;
MgaGalEph::~MgaGalEph() = default;

MgaGalEph& MgaGalEph::operator=(const MgaGalEph&) = default;
MgaGalEph& MgaGalEph::operator=(MgaGalEph&&) = default;

const char* MgaGalEph::nameImpl() const
{
    static const char* Str = "MGA-GAL-EPH";
    return Str;
}

const QVariantList& MgaGalEph::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

