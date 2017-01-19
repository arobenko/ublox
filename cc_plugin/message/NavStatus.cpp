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

#include <cassert>

#include "NavStatus.h"
#include "cc_plugin/field/common.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavStatus<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavStatus<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavStatus>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::NavStatusFields;
QVariantMap createProps_flags()
{
    auto props =
        cc::property::field::ForField<NavStatusFields::flags>()
            .name("flags")
            .add("gpsFixOk")
            .add("diffSoln")
            .add("wknSet")
            .add("towSet");

    assert(props.bits().size() == NavStatusFields::flags::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_fixStat()
{
    auto dgpsIStatProps =
        cc::property::field::ForField<NavStatusFields::dgpsIStat>()
            .name("dgpsIStat")
            .add("none")
            .add("PR+PRR Correction")
            .serialisedHidden();
    assert(dgpsIStatProps.values().size() == (int)NavStatusFields::DgpsIStat::NumOfValues);

    auto reservedProps =
        cc::property::field::IntValue().name("reserved").hidden();

    auto mapMatchingProps =
        cc::property::field::ForField<NavStatusFields::mapMatching>()
            .name("mapMatching")
            .add("none")
            .add("valid")
            .add("used")
            .add("DR")
            .serialisedHidden();
    assert(mapMatchingProps.values().size() == (int)NavStatusFields::MapMatching::NumOfValues);

    auto fixStatProps =
        cc::property::field::ForField<NavStatusFields::fixStat>()
            .name("fixStat")
            .add(dgpsIStatProps.asMap())
            .add(reservedProps.asMap())
            .add(mapMatchingProps.asMap());
    assert(fixStatProps.members().size() == NavStatusFields::fixStat::FieldIdx_numOfValues);
    return fixStatProps.asMap();
}

QVariantMap createProps_flags2()
{
    auto psmStateProps =
        cc::property::field::ForField<NavStatusFields::psmState>()
            .name("psmState")
            .add("ACQUISITION")
            .add("TRACKING")
            .add("POWER OPTIMIZED TRACKING")
            .add("INACTIVE")
            .serialisedHidden();
    assert(psmStateProps.values().size() == (int)NavStatusFields::PsmState::NumOfValues);

    auto reservedProps =
        cc::property::field::IntValue().name("reserved").hidden();

    auto flags2Props =
        cc::property::field::ForField<NavStatusFields::flags2>()
            .add(psmStateProps.asMap())
            .add(reservedProps.asMap());
    assert(flags2Props.members().size() == NavStatusFields::flags2::FieldIdx_numOfValues);
    return flags2Props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(cc_plugin::field::nav::props_gpsFix());
    props.append(createProps_flags());
    props.append(createProps_fixStat());
    props.append(createProps_flags2());
    props.append(cc::property::field::ForField<NavStatusFields::ttff>().name("ttff").asMap());
    props.append(cc::property::field::ForField<NavStatusFields::msss>().name("msss").asMap());

    assert(props.size() == NavStatus::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavStatus::NavStatus() = default;
NavStatus::~NavStatus() = default;

NavStatus& NavStatus::operator=(const NavStatus&) = default;
NavStatus& NavStatus::operator=(NavStatus&&) = default;


const char* NavStatus::nameImpl() const
{
    static const char* Str = "NAV-STATUS";
    return Str;
}

const QVariantList& NavStatus::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

