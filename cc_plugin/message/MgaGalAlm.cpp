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

#include "MgaGalAlm.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaGalAlm<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaGalAlm<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaGalAlm>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaGalAlmFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaGalAlmFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaGalAlmFields::version>().name("version").asMap());
    props.append(
        cc::property::field::ForField<MgaGalAlmFields::svId>().name("svId").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MgaGalAlmFields::ioda>().name("ioda").asMap());
    props.append(
        cc::property::field::ForField<MgaGalAlmFields::almWNa>().name("almWNa").asMap());
    props.append(
        cc::property::field::ForField<MgaGalAlmFields::toa>().name("toa").asMap());
    props.append(
        cc::property::field::ForField<MgaGalAlmFields::deltaSqrtA>().name("deltaSqrtA").asMap());
    props.append(
        cc::property::field::ForField<MgaGalAlmFields::e>().name("e").asMap());
    props.append(
        cc::property::field::ForField<MgaGalAlmFields::deltaI>().name("deltaI").asMap());
    props.append(
        cc::property::field::ForField<MgaGalAlmFields::omega0>().name("omega0").asMap());
    props.append(
        cc::property::field::ForField<MgaGalAlmFields::omegaDot>().name("omegaDot").asMap());
    props.append(
        cc::property::field::ForField<MgaGalAlmFields::omega>().name("omega").asMap());
    props.append(
        cc::property::field::ForField<MgaGalAlmFields::m0>().name("m0").asMap());
    props.append(
        cc::property::field::ForField<MgaGalAlmFields::af0>().name("af0").asMap());
    props.append(
        cc::property::field::ForField<MgaGalAlmFields::af1>().name("af1").asMap());
    props.append(
        cc::property::field::ForField<MgaGalAlmFields::healthE1B>().name("healthE1B").asMap());
    props.append(
        cc::property::field::ForField<MgaGalAlmFields::healthE5b>().name("healthE5b").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));

    assert(props.size() == MgaGalAlm::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaGalAlm::MgaGalAlm() = default;
MgaGalAlm::~MgaGalAlm() = default;

MgaGalAlm& MgaGalAlm::operator=(const MgaGalAlm&) = default;
MgaGalAlm& MgaGalAlm::operator=(MgaGalAlm&&) = default;

const char* MgaGalAlm::nameImpl() const
{
    static const char* Str = "MGA-GAL-ALM";
    return Str;
}

const QVariantList& MgaGalAlm::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

