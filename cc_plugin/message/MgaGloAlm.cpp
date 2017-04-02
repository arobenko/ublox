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

#include "MgaGloAlm.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaGloAlm<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaGloAlm<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaGloAlm>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaGloAlmFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaGloAlmFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaGloAlmFields::version>().name("version").asMap());
    props.append(
        cc::property::field::ForField<MgaGloAlmFields::svId>().name("svId").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MgaGloAlmFields::N>().name("N").asMap());
    props.append(
        cc::property::field::ForField<MgaGloAlmFields::M>().name("M").asMap());
    props.append(
        cc::property::field::ForField<MgaGloAlmFields::C>().name("C").asMap());
    props.append(
        cc::property::field::ForField<MgaGloAlmFields::tau>().name("tau").asMap());
    props.append(
        cc::property::field::ForField<MgaGloAlmFields::epsilon>().name("epsilon").asMap());
    props.append(
        cc::property::field::ForField<MgaGloAlmFields::lambda>().name("lambda").asMap());
    props.append(
        cc::property::field::ForField<MgaGloAlmFields::deltaI>().name("deltaI").asMap());
    props.append(
        cc::property::field::ForField<MgaGloAlmFields::tLambda>().name("tLambda").asMap());
    props.append(
        cc::property::field::ForField<MgaGloAlmFields::deltaT>().name("deltaT").asMap());
    props.append(
        cc::property::field::ForField<MgaGloAlmFields::deltaDT>().name("deltaDT").asMap());
    props.append(
        cc::property::field::ForField<MgaGloAlmFields::H>().name("H").asMap());
    props.append(
        cc::property::field::ForField<MgaGloAlmFields::omega>().name("omega").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));

    assert(props.size() == MgaGloAlm::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaGloAlm::MgaGloAlm() = default;
MgaGloAlm::~MgaGloAlm() = default;

MgaGloAlm& MgaGloAlm::operator=(const MgaGloAlm&) = default;
MgaGloAlm& MgaGloAlm::operator=(MgaGloAlm&&) = default;

const char* MgaGloAlm::nameImpl() const
{
    static const char* Str = "MGA-GLO-ALM";
    return Str;
}

const QVariantList& MgaGloAlm::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

