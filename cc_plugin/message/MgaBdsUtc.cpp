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

#include "MgaBdsUtc.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaBdsUtc<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaBdsUtc<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaBdsUtc>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaBdsUtcFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaBdsUtcFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaBdsUtcFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MgaBdsUtcFields::a0UTC>().name("a0UTC").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsUtcFields::a1UTC>().name("a1UTC").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsUtcFields::dtLS>().name("dtLS").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(
        cc::property::field::ForField<MgaBdsUtcFields::wnRec>().name("wnRec").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsUtcFields::wnLSF>().name("wnLSF").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsUtcFields::dN>().name("dN").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsUtcFields::dtLSF>().name("dtLSF").asMap());
    props.append(cc_plugin::field::common::props_reserved(3));

    assert(props.size() == MgaBdsUtc::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaBdsUtc::MgaBdsUtc() = default;
MgaBdsUtc::~MgaBdsUtc() = default;

MgaBdsUtc& MgaBdsUtc::operator=(const MgaBdsUtc&) = default;
MgaBdsUtc& MgaBdsUtc::operator=(MgaBdsUtc&&) = default;

const char* MgaBdsUtc::nameImpl() const
{
    static const char* Str = "MGA-BDS-UTC";
    return Str;
}

const QVariantList& MgaBdsUtc::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

