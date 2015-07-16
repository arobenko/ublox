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

#include "NavDgps.h"
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
    props.insert(cc::Property::indexedData(1U), cc_plugin::field::nav::dgpsFlagsProperties());
    props.insert(cc::Property::indexedData(2U), cc_plugin::field::nav::agechProperties());
    props.insert(cc::Property::indexedData(3U), cc_plugin::field::nav::prcProperties());
    props.insert(cc::Property::indexedData(4U), cc_plugin::field::nav::prrcProperties());
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
    props.append(cc_plugin::field::nav::ageProperties());
    props.append(cc_plugin::field::nav::baseIdProperties());
    props.append(cc_plugin::field::nav::baseHealthProperties());
    props.append(cc_plugin::field::nav::nchProperties());
    props.append(cc_plugin::field::nav::dgpsStatusProperties());
    props.append(cc_plugin::field::common::resProperties(1));
    props.append(createDataListProperties());

    assert(props.size() == NavDgps::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

const char* NavDgps::nameImpl() const
{
    static const char* Str = "NAV-DGPS";
    return Str;
}

const QVariantList& NavDgps::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

