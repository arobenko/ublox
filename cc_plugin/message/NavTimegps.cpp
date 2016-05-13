//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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

#include "NavTimegps.h"

#include <cassert>

#include "cc_plugin/field/common.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavTimegps<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavTimegps<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavTimegps>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::NavTimegpsFields;

QVariantMap createProps_leapS()
{
    return
        cc::property::field::ForField<NavTimegpsFields::leapS>()
            .name("leapS")
            .asMap();
}


QVariantMap createProps_valid()
{
    cc::property::field::ForField<NavTimegpsFields::valid> props;
    props.name("valid")
         .add("towValid")
         .add("weekValid")
         .add("leapSValid");
    assert(props.bits().size() == NavTimegpsFields::valid_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(cc_plugin::field::nav::props_fTOW());
    props.append(cc_plugin::field::nav::props_week());
    props.append(createProps_leapS());
    props.append(createProps_valid());
    props.append(cc_plugin::field::nav::props_tAcc());

    assert(props.size() == NavTimegps::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavTimegps::NavTimegps() = default;
NavTimegps::~NavTimegps() = default;

NavTimegps& NavTimegps::operator=(const NavTimegps&) = default;
NavTimegps& NavTimegps::operator=(NavTimegps&&) = default;

const char* NavTimegps::nameImpl() const
{
    static const char* Str = "NAV-TIMEGPS";
    return Str;
}

const QVariantList& NavTimegps::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

