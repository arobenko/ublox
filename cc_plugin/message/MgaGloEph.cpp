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

#include "MgaGloEph.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaGloEph<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaGloEph<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaGloEph>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaGloEphFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaGloEphFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaGloEphFields::version>().name("version").asMap());
    props.append(
        cc::property::field::ForField<MgaGloEphFields::svId>().name("svId").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MgaGloEphFields::FT>().name("FT").asMap());
    props.append(
        cc::property::field::ForField<MgaGloEphFields::B>().name("B").asMap());
    props.append(
        cc::property::field::ForField<MgaGloEphFields::M>().name("M").asMap());
    props.append(
        cc::property::field::ForField<MgaGloEphFields::H>().name("H").asMap());
    props.append(
        cc::property::field::ForField<MgaGloEphFields::x>().name("x").asMap());
    props.append(
        cc::property::field::ForField<MgaGloEphFields::y>().name("y").asMap());
    props.append(
        cc::property::field::ForField<MgaGloEphFields::z>().name("z").asMap());
    props.append(
        cc::property::field::ForField<MgaGloEphFields::dx>().name("dx").asMap());
    props.append(
        cc::property::field::ForField<MgaGloEphFields::dy>().name("dy").asMap());
    props.append(
        cc::property::field::ForField<MgaGloEphFields::dz>().name("dz").asMap());
    props.append(
        cc::property::field::ForField<MgaGloEphFields::ddx>().name("ddx").asMap());
    props.append(
        cc::property::field::ForField<MgaGloEphFields::ddy>().name("ddy").asMap());
    props.append(
        cc::property::field::ForField<MgaGloEphFields::ddz>().name("ddz").asMap());
    props.append(
        cc::property::field::ForField<MgaGloEphFields::tb>().name("tb").asMap());
    props.append(
        cc::property::field::ForField<MgaGloEphFields::gamma>().name("gamma").asMap());
    props.append(
        cc::property::field::ForField<MgaGloEphFields::E>().name("E").asMap());
    props.append(
        cc::property::field::ForField<MgaGloEphFields::deltaTau>().name("deltaTau").asMap());
    props.append(
        cc::property::field::ForField<MgaGloEphFields::tau>().name("tau").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));

    assert(props.size() == MgaGloEph::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaGloEph::MgaGloEph() = default;
MgaGloEph::~MgaGloEph() = default;

MgaGloEph& MgaGloEph::operator=(const MgaGloEph&) = default;
MgaGloEph& MgaGloEph::operator=(MgaGloEph&&) = default;

const char* MgaGloEph::nameImpl() const
{
    static const char* Str = "MGA-GLO-EPH";
    return Str;
}

const QVariantList& MgaGloEph::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

