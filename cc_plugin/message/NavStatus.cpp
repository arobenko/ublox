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

QVariantMap createProps_flags()
{
    QVariantList bitNames;
    bitNames.append("gpsFixOk");
    bitNames.append("diffSoln");
    bitNames.append("wknSet");
    bitNames.append("towSet");

    return cc::Property::createPropertiesMap("flags", std::move(bitNames));
}

QVariantMap createProps_fixStat()
{
    QVariantList dgpsIStatEnumValues;
    cc::Property::appendEnumValue(dgpsIStatEnumValues, "none");
    cc::Property::appendEnumValue(dgpsIStatEnumValues, "PR+PRR Correction");
    assert(dgpsIStatEnumValues.size() == (int)ublox::message::DgpsIStat::NumOfValues);
    auto dgpsIStatProps = cc::Property::createPropertiesMap("dgpsIStat", std::move(dgpsIStatEnumValues));
    cc::Property::setSerialisedHidden(dgpsIStatProps);

    auto reservedProps = cc::Property::createPropertiesMap("reserved");
    cc::Property::setFieldHidden(reservedProps);

    QVariantList mapMatchingEnumValues;
    cc::Property::appendEnumValue(mapMatchingEnumValues, "none");
    cc::Property::appendEnumValue(mapMatchingEnumValues, "valid");
    cc::Property::appendEnumValue(mapMatchingEnumValues, "used");
    cc::Property::appendEnumValue(mapMatchingEnumValues, "DR");
    assert(mapMatchingEnumValues.size() == (int)ublox::message::MapMatching::NumOfValues);
    auto mapMatchingProps = cc::Property::createPropertiesMap("mapMatching", std::move(mapMatchingEnumValues));
    cc::Property::setSerialisedHidden(mapMatchingProps);

    QVariantList membersData;
    membersData.append(std::move(dgpsIStatProps));
    membersData.append(std::move(reservedProps));
    membersData.append(std::move(mapMatchingProps));
    assert(membersData.size() == ublox::message::NavStatusField_fixStat_numOfValues);

    return cc::Property::createPropertiesMap("fixStat", std::move(membersData));
}

QVariantMap createProps_flags2()
{
    QVariantList psmStateEnumValues;
    cc::Property::appendEnumValue(psmStateEnumValues, "ACQUISITION");
    cc::Property::appendEnumValue(psmStateEnumValues, "TRACKING");
    cc::Property::appendEnumValue(psmStateEnumValues, "POWER OPTIMIZED TRACKING");
    cc::Property::appendEnumValue(psmStateEnumValues, "INACTIVE");
    assert(psmStateEnumValues.size() == (int)ublox::message::PsmState::NumOfValues);
    auto psmStateProps = cc::Property::createPropertiesMap("psmState", std::move(psmStateEnumValues));
    cc::Property::setSerialisedHidden(psmStateProps);

    auto reservedProps = cc::Property::createPropertiesMap("reserved");
    cc::Property::setFieldHidden(reservedProps);

    QVariantList membersData;
    membersData.append(std::move(psmStateProps));
    membersData.append(std::move(reservedProps));
    assert(membersData.size() == ublox::message::NavStatusField_flags2_numOfValues);

    return cc::Property::createPropertiesMap("flags2", std::move(membersData));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(cc_plugin::field::nav::props_gpsFix());
    props.append(createProps_flags());
    props.append(createProps_fixStat());
    props.append(createProps_flags2());
    props.append(cc::Property::createPropertiesMap("ttff"));
    props.append(cc::Property::createPropertiesMap("msss"));

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

