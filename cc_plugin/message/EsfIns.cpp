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

#include "EsfIns.h"

#include <cassert>

#include "cc_plugin/field/common.h"

template class ublox::message::EsfIns<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::EsfIns<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::EsfIns>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::EsfInsFields;

QVariantMap createProps_bitfield0()
{
    using Field = EsfInsFields::bitfield0;
    auto props =
        cc::property::field::ForField<Field>()
            .name("bitfield0")
            .add("xAngRateValid")
            .add("yAngRateValid")
            .add("zAngRateValid")
            .add("xAccelValid")
            .add("yAccelValid")
            .add("zAccelValid");
    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<EsfInsFields::version>().name("version").asMap());
    props.append(createProps_bitfield0());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc_plugin::field::common::props_iTOW());
    props.append(
        cc::property::field::ForField<EsfInsFields::xAngRate>().name("xAngRate").asMap());
    props.append(
        cc::property::field::ForField<EsfInsFields::yAngRate>().name("yAngRate").asMap());
    props.append(
        cc::property::field::ForField<EsfInsFields::zAngRate>().name("zAngRate").asMap());
    props.append(
        cc::property::field::ForField<EsfInsFields::xAccel>().name("xAccel").asMap());
    props.append(
        cc::property::field::ForField<EsfInsFields::yAccel>().name("yAccel").asMap());
    props.append(
        cc::property::field::ForField<EsfInsFields::zAccel>().name("zAccel").asMap());

    assert(props.size() == EsfIns::FieldIdx_numOfValues);
    return props;
}

}  // namespace

EsfIns::EsfIns() = default;
EsfIns::~EsfIns() = default;

EsfIns& EsfIns::operator=(const EsfIns&) = default;
EsfIns& EsfIns::operator=(EsfIns&&) = default;

const char* EsfIns::nameImpl() const
{
    static const char* Str = "ESF-INS";
    return Str;
}

const QVariantList& EsfIns::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

