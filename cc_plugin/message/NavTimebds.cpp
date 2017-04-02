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

#include "NavTimebds.h"

#include <cassert>

#include "cc_plugin/field/common.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavTimebds<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavTimebds<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavTimebds>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::NavTimebdsFields;

QVariantMap createProps_valid()
{
    cc::property::field::ForField<NavTimebdsFields::validBits> props;
    props.name("valid")
         .add("sowValid")
         .add("weekValid")
         .add("leapSValid");
    assert(props.bits().size() == NavTimebdsFields::validBits::BitIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(
        cc::property::field::ForField<NavTimebdsFields::SOW>().name("SOW").asMap());
    props.append(
        cc::property::field::ForField<NavTimebdsFields::fSOW>().name("fSOW").asMap());
    props.append(cc_plugin::field::nav::props_week());
    props.append(
        cc::property::field::ForField<NavTimebdsFields::leapS>().name("leapS").asMap());
    props.append(createProps_valid());
    props.append(cc_plugin::field::nav::props_tAcc());

    assert(props.size() == NavTimebds::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavTimebds::NavTimebds() = default;
NavTimebds::~NavTimebds() = default;

NavTimebds& NavTimebds::operator=(const NavTimebds&) = default;
NavTimebds& NavTimebds::operator=(NavTimebds&&) = default;

const char* NavTimebds::nameImpl() const
{
    static const char* Str = "NAV-TIMEBDS";
    return Str;
}

const QVariantList& NavTimebds::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

