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

#include "MgaGpsAlm.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaGpsAlm<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaGpsAlm<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaGpsAlm>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaGpsAlmFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaGpsAlmFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaGpsAlmFields::version>().name("version").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsAlmFields::svId>().name("svId").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsAlmFields::svHealth>().name("svHealth").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsAlmFields::e>().name("e").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsAlmFields::almWNa>().name("almWNa").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsAlmFields::toa>().name("toa").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsAlmFields::deltaI>().name("deltaI").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsAlmFields::omegaDot>().name("omegaDot").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsAlmFields::sqrtA>().name("sqrtA").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsAlmFields::omega0>().name("omega0").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsAlmFields::omega>().name("omega").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsAlmFields::m0>().name("m0").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsAlmFields::af0>().name("af0").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsAlmFields::af1>().name("af1").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));

    assert(props.size() == MgaGpsAlm::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaGpsAlm::MgaGpsAlm() = default;
MgaGpsAlm::~MgaGpsAlm() = default;

MgaGpsAlm& MgaGpsAlm::operator=(const MgaGpsAlm&) = default;
MgaGpsAlm& MgaGpsAlm::operator=(MgaGpsAlm&&) = default;

const char* MgaGpsAlm::nameImpl() const
{
    static const char* Str = "MGA-GPS-ALM";
    return Str;
}

const QVariantList& MgaGpsAlm::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

