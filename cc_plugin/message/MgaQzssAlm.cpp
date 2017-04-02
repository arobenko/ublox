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

#include "MgaQzssAlm.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaQzssAlm<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaQzssAlm<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaQzssAlm>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaQzssAlmFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaQzssAlmFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaQzssAlmFields::version>().name("version").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssAlmFields::svId>().name("svId").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssAlmFields::svHealth>().name("svHealth").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssAlmFields::e>().name("e").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssAlmFields::almWNa>().name("almWNa").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssAlmFields::toa>().name("toa").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssAlmFields::deltaI>().name("deltaI").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssAlmFields::omegaDot>().name("omegaDot").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssAlmFields::sqrtA>().name("sqrtA").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssAlmFields::omega0>().name("omega0").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssAlmFields::omega>().name("omega").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssAlmFields::m0>().name("m0").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssAlmFields::af0>().name("af0").asMap());
    props.append(
        cc::property::field::ForField<MgaQzssAlmFields::af1>().name("af1").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));

    assert(props.size() == MgaQzssAlm::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaQzssAlm::MgaQzssAlm() = default;
MgaQzssAlm::~MgaQzssAlm() = default;

MgaQzssAlm& MgaQzssAlm::operator=(const MgaQzssAlm&) = default;
MgaQzssAlm& MgaQzssAlm::operator=(MgaQzssAlm&&) = default;

const char* MgaQzssAlm::nameImpl() const
{
    static const char* Str = "MGA-QZSS-ALM";
    return Str;
}

const QVariantList& MgaQzssAlm::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

