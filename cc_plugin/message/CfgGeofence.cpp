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

#include "CfgGeofence.h"

#include <cassert>

#include "cc_plugin/field/common.h"
#include "cc_plugin/field/MsgId.h"

template class ublox::message::CfgGeofence<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgGeofence<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgGeofence>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgGeofenceFields;

QVariantMap createProps_numFences()
{
    return
        cc::property::field::ForField<CfgGeofenceFields::numFences>()
            .name("numFences")
            .readOnly()
            .asMap();
}

QVariantMap createProps_pioEnabled()
{
    auto props =
        cc::property::field::ForField<CfgGeofenceFields::pioEnabled>()
            .name("pioEnabled")
            .add("disabled")
            .add("enabled");

    assert(props.values().size() == (int)CfgGeofenceFields::pioEnabled::ValueType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_pioPolarity()
{
    auto props =
        cc::property::field::ForField<CfgGeofenceFields::pioPolarity>()
            .name("pioPolarity")
            .add("LowInside")
            .add("LowOutside");

    assert(props.values().size() == (int)CfgGeofenceFields::pioPolarity::ValueType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_lat()
{
    return
        cc::property::field::ForField<CfgGeofenceFields::lat>()
            .name("lat")
            .scaledDecimals(7)
            .asMap();
}

QVariantMap createProps_lon()
{
    return
        cc::property::field::ForField<CfgGeofenceFields::lon>()
            .name("lon")
            .scaledDecimals(7)
            .asMap();
}

QVariantMap createProps_radius()
{
    return
        cc::property::field::ForField<CfgGeofenceFields::radius>()
            .name("radius")
            .scaledDecimals(2)
            .asMap();
}

QVariantMap createProps_data()
{
    auto blockProps =
        cc::property::field::ForField<CfgGeofenceFields::block>()
            .add(createProps_lat())
            .add(createProps_lon())
            .add(createProps_radius());

    assert(blockProps.members().size() == (int)CfgGeofenceFields::block::FieldIdx_numOfValues);
    return
        cc::property::field::ForField<CfgGeofenceFields::data<> >()
            .name("data")
            .add(blockProps.asMap())
            .serialisedHidden()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;

    props.append(cc::property::field::ForField<CfgGeofenceFields::version>().name("version").asMap());
    props.append(createProps_numFences());
    props.append(cc::property::field::ForField<CfgGeofenceFields::confLvl>().name("confLvl").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_pioEnabled());
    props.append(createProps_pioPolarity());
    props.append(cc::property::field::ForField<CfgGeofenceFields::pioPolarity>().name("pin ").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(createProps_data());

    assert(props.size() == CfgGeofence::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgGeofence::CfgGeofence() = default;
CfgGeofence::~CfgGeofence() = default;

CfgGeofence& CfgGeofence::operator=(const CfgGeofence&) = default;
CfgGeofence& CfgGeofence::operator=(CfgGeofence&&) = default;

const char* CfgGeofence::nameImpl() const
{
    static const char* Str = "CFG-GEOFENCE";
    return Str;
}

const QVariantList& CfgGeofence::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

