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

#include "MgaGpsUtc.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaGpsUtc<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaGpsUtc<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaGpsUtc>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaGpsUtcFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaGpsUtcFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaGpsUtcFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MgaGpsUtcFields::utcA0>().name("utcA0").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsUtcFields::utcA1>().name("utcA1").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsUtcFields::utcDtLS>().name("utcDtLS").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsUtcFields::utcTot>().name("utcTot").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsUtcFields::utcWNt>().name("utcWNt").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsUtcFields::utcWNlsf>().name("utcWNlsf").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsUtcFields::utcDn>().name("utcDn").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsUtcFields::utcDtLSF>().name("utcDtLSF").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));

    assert(props.size() == MgaGpsUtc::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaGpsUtc::MgaGpsUtc() = default;
MgaGpsUtc::~MgaGpsUtc() = default;

MgaGpsUtc& MgaGpsUtc::operator=(const MgaGpsUtc&) = default;
MgaGpsUtc& MgaGpsUtc::operator=(MgaGpsUtc&&) = default;

const char* MgaGpsUtc::nameImpl() const
{
    static const char* Str = "MGA-GPS-UTC";
    return Str;
}

const QVariantList& MgaGpsUtc::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

