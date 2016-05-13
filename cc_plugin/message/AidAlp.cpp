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

#include "AidAlp.h"

#include "cc_plugin/field/common.h"

template class ublox::message::AidAlp<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::AidAlp<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::AidAlp>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::AidAlpFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<AidAlpFields::predTow>().name("predTow").asMap());
    props.append(
        cc::property::field::ForField<AidAlpFields::predDur>().name("predDur").asMap());
    props.append(
        cc::property::field::ForField<AidAlpFields::age>().name("age").asMap());
    props.append(
        cc::property::field::ForField<AidAlpFields::predWno>().name("predWno").asMap());
    props.append(
        cc::property::field::ForField<AidAlpFields::almWno>().name("almWno").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<AidAlpFields::svs>().name("svs").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(cc_plugin::field::common::props_reserved(3));
    assert(props.size() == AidAlp::FieldIdx_numOfValues);
    return props;
}

}  // namespace

AidAlp::AidAlp() = default;
AidAlp::~AidAlp() = default;

AidAlp& AidAlp::operator=(const AidAlp&) = default;
AidAlp& AidAlp::operator=(AidAlp&&) = default;

const char* AidAlp::nameImpl() const
{
    static const char* Str = "AID-ALP";
    return Str;
}

const QVariantList& AidAlp::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

