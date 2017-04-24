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

#include "NavSat.h"

#include <cassert>

#include "cc_plugin/field/nav.h"
#include "cc_plugin/field/common.h"

template class ublox::message::NavSat<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavSat<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavSat>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::NavSatFields;

QVariantMap createProps_prRes()
{
    return
        cc::property::field::ForField<NavSatFields::prRes>()
            .name("prRes")
            .scaledDecimals(1)
            .asMap();
}

QVariantMap createProps_qualityInd()
{
    using Field = NavSatFields::qualityInd;
    auto props =
        cc::property::field::ForField<Field>()
            .name("qualityInd")
            .serialisedHidden()
            .add("Idle")
            .add("Searching")
            .add("Signal acquired")
            .add("Signal unusable")
            .add("Code Lock")
            .add("Code and Carrier Locked")
            .add("Code and Carrier Locked")
            .add("Code and Carrier Locked");
    assert(props.values().size() == (int)Field::ValueType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_flagsLow()
{
    using Field = NavSatFields::flagsLow;
    auto props =
        cc::property::field::ForField<Field>()
            .serialisedHidden()
            .add("svUsed");
    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_health()
{
    using Field = NavSatFields::health;
    auto props =
        cc::property::field::ForField<Field>()
            .name("health")
            .serialisedHidden()
            .add("Unknown")
            .add("Healthy")
            .add("Unhealthy");
    assert(props.values().size() == (int)Field::ValueType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_flagsMid()
{
    using Field = NavSatFields::flagsMid;
    auto props =
        cc::property::field::ForField<Field>()
            .serialisedHidden()
            .add("diffCorr")
            .add("smoothed");
    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_orbitSource()
{
    using Field = NavSatFields::orbitSource;
    auto props =
        cc::property::field::ForField<Field>()
            .name("orbitSource")
            .serialisedHidden()
            .add("No info")
            .add("Ephemeris")
            .add("Almanac")
            .add("AssistNow Offline")
            .add("AssistNow Autonomous");
    assert(props.values().size() == (int)Field::ValueType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_flagsHigh()
{
    using Field = NavSatFields::flagsHigh;
    auto props =
        cc::property::field::ForField<Field>()
            .serialisedHidden()
            .add("ephAvail")
            .add("almAvail")
            .add("anoAvail")
            .add("aopAvail");
    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_flags()
{
    using Field = NavSatFields::flags;
    auto props =
        cc::property::field::ForField<Field>()
            .name("flags")
            .add(createProps_qualityInd())
            .add(createProps_flagsLow())
            .add(createProps_health())
            .add(createProps_flagsMid())
            .add(createProps_orbitSource())
            .add(createProps_flagsHigh());
    assert(props.members().size() == Field::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_data()
{
    auto blockProps =
        cc::property::field::ForField<NavSatFields::block>()
            .add(cc_plugin::field::common::props_gnssId())
            .add(cc::property::field::ForField<NavSatFields::svId>().name("svId").asMap())
            .add(cc::property::field::ForField<NavSatFields::cno>().name("cno").asMap())
            .add(cc::property::field::ForField<NavSatFields::elev>().name("elev").asMap())
            .add(cc::property::field::ForField<NavSatFields::azim>().name("azim").asMap())
            .add(createProps_prRes())
            .add(createProps_flags());
    assert(blockProps.members().size() == NavSatFields::block::FieldIdx_numOfValues);

    return
        cc::property::field::ForField<NavSatFields::data<> >()
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
        cc::property::field::ForField<NavSatFields::version>().name("version").asMap());
    props.append(
        cc::property::field::ForField<NavSatFields::numSvs>().name("numSvs").readOnly().asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_data());

    assert(props.size() == NavSat::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavSat::NavSat() = default;
NavSat::~NavSat() = default;

NavSat& NavSat::operator=(const NavSat&) = default;
NavSat& NavSat::operator=(NavSat&&) = default;

const char* NavSat::nameImpl() const
{
    static const char* Str = "NAV-SAT";
    return Str;
}

const QVariantList& NavSat::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

