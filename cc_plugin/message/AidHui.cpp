//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
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

#include "AidHui.h"

template class ublox::message::AidHui<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::AidHui<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::AidHui>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::AidHuiFields;

QVariantMap createProps_flags()
{
    cc::property::field::ForField<AidHuiFields::flags> props;
    props.name("flags")
         .add("healthValid")
         .add("utcValid")
         .add("klobValid");
    assert(props.bits().size() == AidHuiFields::flags_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<AidHuiFields::health>().name("health").asMap());
    props.append(
        cc::property::field::ForField<AidHuiFields::utcA0>().name("utcA0").asMap());
    props.append(
        cc::property::field::ForField<AidHuiFields::utcA1>().name("utcA1").asMap());
    props.append(
        cc::property::field::ForField<AidHuiFields::utcTOW>().name("utcTOW").asMap());
    props.append(
        cc::property::field::ForField<AidHuiFields::utcWNT>().name("utcWNT").asMap());
    props.append(
        cc::property::field::ForField<AidHuiFields::utcLS>().name("utcLS").asMap());
    props.append(
        cc::property::field::ForField<AidHuiFields::utcWNF>().name("utcWNF").asMap());
    props.append(
        cc::property::field::ForField<AidHuiFields::utcDN>().name("utcDN").asMap());
    props.append(
        cc::property::field::ForField<AidHuiFields::utcLSF>().name("utcLSF").asMap());
    props.append(
        cc::property::field::ForField<AidHuiFields::utcSpare>().name("utcSpare").asMap());
    props.append(
        cc::property::field::ForField<AidHuiFields::klobA0>().name("klobA0").asMap());
    props.append(
        cc::property::field::ForField<AidHuiFields::klobA1>().name("klobA1").asMap());
    props.append(
        cc::property::field::ForField<AidHuiFields::klobA2>().name("klobA2").asMap());
    props.append(
        cc::property::field::ForField<AidHuiFields::klobA3>().name("klobA3").asMap());
    props.append(
        cc::property::field::ForField<AidHuiFields::klobB0>().name("klobB0").asMap());
    props.append(
        cc::property::field::ForField<AidHuiFields::klobB1>().name("klobB1").asMap());
    props.append(
        cc::property::field::ForField<AidHuiFields::klobB2>().name("klobB2").asMap());
    props.append(
        cc::property::field::ForField<AidHuiFields::klobB3>().name("klobB3").asMap());
    props.append(createProps_flags());
    assert(props.size() == AidHui::FieldIdx_numOfValues);
    return props;
}

}  // namespace

AidHui::AidHui() = default;
AidHui::~AidHui() = default;

AidHui& AidHui::operator=(const AidHui&) = default;
AidHui& AidHui::operator=(AidHui&&) = default;


const char* AidHui::nameImpl() const
{
    static const char* Str = "AID-HUI";
    return Str;
}

const QVariantList& AidHui::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

