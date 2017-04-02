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

#include "MgaAno.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaAno<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaAno<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaAno>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaAnoFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaAnoFields::type>().name("type").asMap());
    props.append(
        cc::property::field::ForField<MgaAnoFields::version>().name("version").asMap());
    props.append(
        cc::property::field::ForField<MgaAnoFields::svId>().name("svId").asMap());
    props.append(cc_plugin::field::common::props_gnssId());
    props.append(
        cc::property::field::ForField<MgaAnoFields::year>().name("year").asMap());
    props.append(
        cc::property::field::ForField<MgaAnoFields::month>().name("month").asMap());
    props.append(
        cc::property::field::ForField<MgaAnoFields::day>().name("day").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MgaAnoFields::data<> >().name("data").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));

    assert(props.size() == MgaAno::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaAno::MgaAno() = default;
MgaAno::~MgaAno() = default;

MgaAno& MgaAno::operator=(const MgaAno&) = default;
MgaAno& MgaAno::operator=(MgaAno&&) = default;

const char* MgaAno::nameImpl() const
{
    static const char* Str = "MGA-ANO";
    return Str;
}

const QVariantList& MgaAno::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

