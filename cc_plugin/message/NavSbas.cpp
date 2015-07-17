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
    QVariantMap props;
    props.insert(cc::Property::indexedData(0U), cc_plugin::field::nav::svidProperties());
    props.insert(cc::Property::indexedData(1U), cc_plugin::field::nav::infoFlagsProperties());
    props.insert(cc::Property::indexedData(2U), cc_plugin::field::nav::udreProperties());
    props.insert(cc::Property::indexedData(3U), cc_plugin::field::nav::sysProperties());
    props.insert(cc::Property::indexedData(4U), cc_plugin::field::nav::serviceProperties());
    props.insert(cc::Property::indexedData(5U), cc_plugin::field::common::resProperties(1));
    props.insert(cc::Property::indexedData(6U), cc_plugin::field::nav::prcProperties());
    props.insert(cc::Property::indexedData(7U), cc_plugin::field::common::resProperties(2));
    props.insert(cc::Property::indexedData(8U), cc_plugin::field::nav::icProperties());
    return props;
}

QVariantMap createDataListProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "Data");
    props.insert(cc::Property::data(), createSingleDataElementProperties());
    props.insert(cc::Property::serialisedHidden(), true);
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

