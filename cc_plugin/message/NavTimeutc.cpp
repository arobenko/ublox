//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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

#include "NavTimeutc.h"

#include <cassert>

#include "cc_plugin/field/common.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavTimeutc<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavTimeutc<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavTimeutc>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::NavTimeutcFields;

QVariantMap createProps_valid()
{
    cc::property::field::ForField<NavTimeutcFields::validBits> props;
    props.name("valid")
         .add("validTOW")
         .add("validWKN")
         .add("validUTC");

    assert(props.bits().size() == NavTimeutcFields::validBits::BitIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(cc_plugin::field::nav::props_tAcc());
    props.append(cc_plugin::field::nav::props_nano());
    props.append(cc_plugin::field::nav::props_year());
    props.append(cc_plugin::field::nav::props_month());
    props.append(cc_plugin::field::nav::props_day());
    props.append(cc_plugin::field::nav::props_hour());
    props.append(cc_plugin::field::nav::props_min());
    props.append(cc_plugin::field::nav::props_sec());
    props.append(createProps_valid());

    assert(props.size() == NavTimeutc::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavTimeutc::NavTimeutc() = default;
NavTimeutc::~NavTimeutc() = default;

NavTimeutc& NavTimeutc::operator=(const NavTimeutc&) = default;
NavTimeutc& NavTimeutc::operator=(NavTimeutc&&) = default;

const char* NavTimeutc::nameImpl() const
{
    static const char* Str = "NAV-TIMEUTC";
    return Str;
}

const QVariantList& NavTimeutc::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

