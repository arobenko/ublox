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

#include "MgaBdsEph.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaBdsEph<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaBdsEph<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaBdsEph>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaBdsEphFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::version>().name("version").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::svId>().name("svId").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::SatH1>().name("SatH1").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::IODC>().name("IODC").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::a2>().name("a2").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::a1>().name("a1").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::a0>().name("a0").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::toc>().name("toc").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::TGD1>().name("TGD1").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::URAI>().name("URAI").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::IODE>().name("IODE").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::toe>().name("toe").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::sqrtA>().name("sqrtA").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::e>().name("e").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::omega>().name("omega").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::Deltan>().name("Deltan").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::IDOT>().name("IDOT").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::M0>().name("M0").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::Omega0>().name("Omega0").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::OmegaDot>().name("OmegaDot").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::i0>().name("i0").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::Cuc>().name("Cuc").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::Cus>().name("Cus").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::Crc>().name("Crc").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::Crs>().name("Crs").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::Cic>().name("Cic").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsEphFields::Cis>().name("Cis").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));

    assert(props.size() == MgaBdsEph::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaBdsEph::MgaBdsEph() = default;
MgaBdsEph::~MgaBdsEph() = default;

MgaBdsEph& MgaBdsEph::operator=(const MgaBdsEph&) = default;
MgaBdsEph& MgaBdsEph::operator=(MgaBdsEph&&) = default;

const char* MgaBdsEph::nameImpl() const
{
    static const char* Str = "MGA-BDS-EPH";
    return Str;
}

const QVariantList& MgaBdsEph::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

