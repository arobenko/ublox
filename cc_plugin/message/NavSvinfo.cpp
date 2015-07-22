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
    QVariantList membersData;
    membersData.append(cc_plugin::field::nav::chNumProperties());
    membersData.append(cc_plugin::field::nav::svidProperties());
    membersData.append(cc_plugin::field::nav::infoFlagsProperties());
    membersData.append(cc_plugin::field::nav::qiProperties());
    membersData.append(cc_plugin::field::nav::cnoProperties());
    membersData.append(cc_plugin::field::nav::elevProperties());
    membersData.append(cc_plugin::field::nav::azimProperties());
    membersData.append(cc_plugin::field::nav::prresProperties());

    QVariantMap props;
    cc::Property::setData(props, std::move(membersData));
    return props;
}

QVariantMap createInfosListProperties()
{
    auto props = cc::Property::createPropertiesMap("Infos", createSingleInfoProperties());
    cc::Property::setSerialisedHidden(props);
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

