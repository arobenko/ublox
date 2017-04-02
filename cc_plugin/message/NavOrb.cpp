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

#include "NavOrb.h"

#include <cassert>

#include "cc_plugin/field/nav.h"
#include "cc_plugin/field/common.h"

template class ublox::message::NavOrb<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavOrb<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavOrb>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::NavOrbFields;


QVariantMap createProps_health()
{
    auto props =
        cc::property::field::ForField<NavOrbFields::health>()
            .name("health")
            .serialisedHidden()
            .add("Unknown")
            .add("Healthy")
            .add("Not healthy");
    assert(props.values().size() == (int)NavOrbFields::Health::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_visibility()
{
    auto props =
        cc::property::field::ForField<NavOrbFields::visibility>()
            .name("visibility")
            .serialisedHidden()
            .add("Unknown")
            .add("Below horizon")
            .add("Above horizon")
            .add("Above elevation mask");
    assert(props.values().size() == (int)NavOrbFields::Visibility::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_svFlag()
{
    auto props =
        cc::property::field::ForField<NavOrbFields::svFlag>()
            .name("svFlag")
            .add(createProps_health())
            .add(createProps_visibility())
            .add(cc::property::field::IntValue().hidden().asMap());
    assert(props.members().size() == NavOrbFields::svFlag::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_usability(const QString& prefix)
{
    return
        cc::property::field::ForField<NavOrbFields::ephUsability>()
            .name(prefix + "Usability")
            .serialisedHidden()
            .asMap();
}

QVariantMap createProps_source(const QString& prefix)
{
    auto props =
        cc::property::field::ForField<NavOrbFields::ephSource>()
            .name(prefix + "Source")
            .serialisedHidden()
            .add("not available")
            .add("GNSS transmission")
            .add("external aiding");
    assert(props.values().size() == (int)NavOrbFields::Source::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_eph()
{
    auto props =
        cc::property::field::ForField<NavOrbFields::eph>()
            .name("eph")
            .add(createProps_usability("eph"))
            .add(createProps_source("eph"));
    assert(props.members().size() == NavOrbFields::eph::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_alm()
{
    auto props =
        cc::property::field::ForField<NavOrbFields::alm>()
            .name("alm")
            .add(createProps_usability("alm"))
            .add(createProps_source("alm"));
    assert(props.members().size() == NavOrbFields::alm::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_type()
{
    auto props =
        cc::property::field::ForField<NavOrbFields::type>()
            .name("type")
            .serialisedHidden()
            .add("no data")
            .add("offline data")
            .add("autonomous data");
    assert(props.values().size() == (int)NavOrbFields::OrbType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_otherOrb()
{
    auto props =
        cc::property::field::ForField<NavOrbFields::otherOrb>()
            .name("otherOrb")
            .add(createProps_usability("anoAop"))
            .add(createProps_type());
    assert(props.members().size() == NavOrbFields::alm::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_data()
{
    auto blockProps =
        cc::property::field::ForField<NavOrbFields::block>()
            .add(cc_plugin::field::common::props_gnssId())
            .add(cc::property::field::ForField<NavOrbFields::svId>().name("svId").asMap())
            .add(createProps_svFlag())
            .add(createProps_eph())
            .add(createProps_alm())
            .add(createProps_otherOrb());
    assert(blockProps.members().size() == NavOrbFields::block::FieldIdx_numOfValues);

    return
        cc::property::field::ForField<NavOrbFields::data<> >()
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
        cc::property::field::ForField<NavOrbFields::version>().name("version").asMap());
    props.append(
        cc::property::field::ForField<NavOrbFields::numSv>().name("numSv").readOnly().asMap());
    props.append(field::common::props_reserved(1));
    props.append(createProps_data());

    assert(props.size() == NavOrb::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavOrb::NavOrb() = default;
NavOrb::~NavOrb() = default;

NavOrb& NavOrb::operator=(const NavOrb&) = default;
NavOrb& NavOrb::operator=(NavOrb&&) = default;

const char* NavOrb::nameImpl() const
{
    static const char* Str = "NAV-ORB";
    return Str;
}

const QVariantList& NavOrb::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

