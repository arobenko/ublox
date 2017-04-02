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

#include "MgaBdsAlm.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaBdsAlm<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaBdsAlm<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaBdsAlm>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaBdsAlmFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaBdsAlmFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaBdsAlmFields::version>().name("version").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsAlmFields::svId>().name("svId").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MgaBdsAlmFields::Wna>().name("Wna").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsAlmFields::toa>().name("toa").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsAlmFields::deltaI>().name("deltaI").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsAlmFields::sqrtA>().name("sqrtA").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsAlmFields::e>().name("e").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsAlmFields::omega>().name("omega").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsAlmFields::M0>().name("M0").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsAlmFields::Omega0>().name("Omega0").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsAlmFields::OmegaDot>().name("OmegaDot").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsAlmFields::a0>().name("a0").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsAlmFields::a1>().name("a1").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));

    assert(props.size() == MgaBdsAlm::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaBdsAlm::MgaBdsAlm() = default;
MgaBdsAlm::~MgaBdsAlm() = default;

MgaBdsAlm& MgaBdsAlm::operator=(const MgaBdsAlm&) = default;
MgaBdsAlm& MgaBdsAlm::operator=(MgaBdsAlm&&) = default;

const char* MgaBdsAlm::nameImpl() const
{
    static const char* Str = "MGA-BDS-ALM";
    return Str;
}

const QVariantList& MgaBdsAlm::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

