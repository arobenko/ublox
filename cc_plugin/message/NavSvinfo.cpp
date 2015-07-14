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

#include "NavSvinfo.h"
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

QVariantMap createSingleInfoProperties()
{
    QVariantMap props;
    props.insert(cc::Property::indexedData(0U), cc_plugin::field::nav::chNumProperties());
    props.insert(cc::Property::indexedData(1U), cc_plugin::field::nav::svidProperties());
    props.insert(cc::Property::indexedData(2U), cc_plugin::field::nav::infoFlagsProperties());
    props.insert(cc::Property::indexedData(3U), cc_plugin::field::nav::qiProperties());
    props.insert(cc::Property::indexedData(4U), cc_plugin::field::nav::cnoProperties());
    props.insert(cc::Property::indexedData(5U), cc_plugin::field::nav::elevProperties());
    props.insert(cc::Property::indexedData(6U), cc_plugin::field::nav::azimProperties());
    props.insert(cc::Property::indexedData(7U), cc_plugin::field::nav::prresProperties());

    return props;
}

QVariantMap createInfosListProperties()
{
    QVariantMap props;
    props.insert(cc::Property::name(), "Infos");
    props.insert(cc::Property::data(), createSingleInfoProperties());
    props.insert(cc::Property::serialisedHidden(), true);
    return props;
}


QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::itowProperties());
    props.append(cc_plugin::field::nav::nchProperties());
    props.append(cc_plugin::field::common::resProperties(1));
    props.append(cc_plugin::field::common::resProperties(2));
    props.append(createInfosListProperties());

    assert(props.size() == NavSvinfo::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

const char* NavSvinfo::nameImpl() const
{
    static const char* Str = "NAV-SVINFO";
    return Str;
}

const QVariantList& NavSvinfo::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

