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

#include <type_traits>
#include <functional>
#include <cassert>

#include "NavSbas.h"
#include "cc_plugin/field/nav.h"
#include "cc_plugin/field/common.h"

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createSingleDataElementProperties()
{
    QVariantList membersData;
    membersData.append(cc_plugin::field::nav::svidProperties());
    membersData.append(cc_plugin::field::nav::infoFlagsProperties());
    membersData.append(cc_plugin::field::nav::udreProperties());
    membersData.append(cc_plugin::field::nav::sysProperties());
    membersData.append(cc_plugin::field::nav::serviceProperties());
    membersData.append(cc_plugin::field::common::resProperties(1));
    membersData.append(cc_plugin::field::nav::prcProperties());
    membersData.append(cc_plugin::field::common::resProperties(2));
    membersData.append(cc_plugin::field::nav::icProperties());

    QVariantMap props;
    cc::Property::setData(props, std::move(membersData));
    return props;
}

QVariantMap createDataListProperties()
{
    auto props = cc::Property::createPropertiesMap("Data", createSingleDataElementProperties());
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::itowProperties());
    props.append(cc_plugin::field::nav::geoProperties());
    props.append(cc_plugin::field::nav::modeProperties());
    props.append(cc_plugin::field::nav::sysProperties());
    props.append(cc_plugin::field::nav::serviceProperties());
    props.append(cc_plugin::field::nav::cntProperties());
    props.append(cc_plugin::field::common::resProperties(0));
    props.append(createDataListProperties());

    assert(props.size() == NavSbas::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

const char* NavSbas::nameImpl() const
{
    static const char* Str = "NAV-SBAS";
    return Str;
}

const QVariantList& NavSbas::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

