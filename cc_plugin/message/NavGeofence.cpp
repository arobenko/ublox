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

#include "NavGeofence.h"

#include <cassert>

#include "cc_plugin/field/nav.h"
#include "cc_plugin/field/common.h"

template class ublox::message::NavGeofence<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavGeofence<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavGeofence>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::NavGeofenceFields;

QVariantMap createProps_status()
{
    auto props =
        cc::property::field::ForField<NavGeofenceFields::status>()
            .name("status")
            .add("Not active")
            .add("Active");
    assert(props.values().size() == (int)NavGeofenceFields::Status::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_state(const char* name)
{
    auto props =
        cc::property::field::ForField<NavGeofenceFields::state>()
            .name(name)
            .add("Unknown")
            .add("Inside")
            .add("Outside");
    assert(props.values().size() == (int)NavGeofenceFields::State::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_data()
{
    auto blockProps =
        cc::property::field::ForField<NavGeofenceFields::block>()
              .add(createProps_state("state"))
              .add(cc_plugin::field::common::props_reserved(1));
    assert(blockProps.members().size() == NavGeofenceFields::block::FieldIdx_numOfValues);

    return
        cc::property::field::ForField<NavGeofenceFields::data<> >()
            .name("data")
            .add(blockProps.asMap())
            .serialisedHidden()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(
        cc::property::field::ForField<NavGeofenceFields::version>().name("version").asMap());
    props.append(createProps_status());
    props.append(
        cc::property::field::ForField<NavGeofenceFields::numFences>().name("numFences").readOnly().asMap());
    props.append(createProps_state("combState"));
    props.append(createProps_data());

    assert(props.size() == NavGeofence::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavGeofence::NavGeofence() = default;
NavGeofence::~NavGeofence() = default;

NavGeofence& NavGeofence::operator=(const NavGeofence&) = default;
NavGeofence& NavGeofence::operator=(NavGeofence&&) = default;

const char* NavGeofence::nameImpl() const
{
    static const char* Str = "NAV-GEOFENCE";
    return Str;
}

const QVariantList& NavGeofence::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

