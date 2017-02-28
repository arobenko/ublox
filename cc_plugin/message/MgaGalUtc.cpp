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

#include "MgaGalUtc.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaGalUtc<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaGalUtc<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaGalUtc>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaGalUtcFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaGalUtcFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaGalUtcFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MgaGalUtcFields::a0>().name("a0").asMap());
    props.append(
        cc::property::field::ForField<MgaGalUtcFields::a1>().name("a1").asMap());
    props.append(
        cc::property::field::ForField<MgaGalUtcFields::dtLS>().name("dtLS").asMap());
    props.append(
        cc::property::field::ForField<MgaGalUtcFields::tot>().name("tot").asMap());
    props.append(
        cc::property::field::ForField<MgaGalUtcFields::wnt>().name("wnt").asMap());
    props.append(
        cc::property::field::ForField<MgaGalUtcFields::wnLSF>().name("wnLSF").asMap());
    props.append(
        cc::property::field::ForField<MgaGalUtcFields::dN>().name("dN").asMap());
    props.append(
        cc::property::field::ForField<MgaGalUtcFields::dTLSF>().name("dTLSF").asMap());

    props.append(cc_plugin::field::common::props_reserved(2));

    assert(props.size() == MgaGalUtc::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaGalUtc::MgaGalUtc() = default;
MgaGalUtc::~MgaGalUtc() = default;

MgaGalUtc& MgaGalUtc::operator=(const MgaGalUtc&) = default;
MgaGalUtc& MgaGalUtc::operator=(MgaGalUtc&&) = default;

const char* MgaGalUtc::nameImpl() const
{
    static const char* Str = "MGA-GAL-UTC";
    return Str;
}

const QVariantList& MgaGalUtc::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

