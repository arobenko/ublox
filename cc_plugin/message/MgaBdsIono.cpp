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

#include "MgaBdsIono.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaBdsIono<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaBdsIono<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaBdsIono>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaBdsIonoFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaBdsIonoFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaBdsIonoFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MgaBdsIonoFields::alpha0>().name("alpha0").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsIonoFields::alpha1>().name("alpha1").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsIonoFields::alpha2>().name("alpha2").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsIonoFields::alpha3>().name("alpha3").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsIonoFields::beta0>().name("beta0").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsIonoFields::beta1>().name("beta1").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsIonoFields::beta2>().name("beta2").asMap());
    props.append(
        cc::property::field::ForField<MgaBdsIonoFields::beta3>().name("beta3").asMap());
    props.append(cc_plugin::field::common::props_reserved(3));

    assert(props.size() == MgaBdsIono::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaBdsIono::MgaBdsIono() = default;
MgaBdsIono::~MgaBdsIono() = default;

MgaBdsIono& MgaBdsIono::operator=(const MgaBdsIono&) = default;
MgaBdsIono& MgaBdsIono::operator=(MgaBdsIono&&) = default;

const char* MgaBdsIono::nameImpl() const
{
    static const char* Str = "MGA-BDS-IONO";
    return Str;
}

const QVariantList& MgaBdsIono::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

