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

#include "RxmSvsi.h"
#include "cc_plugin/field/rxm.h"
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
    membersData.append(cc_plugin::field::rxm::svidProperties());
    membersData.append(cc_plugin::field::rxm::statusInfoSvFlagProperties());
    membersData.append(cc_plugin::field::rxm::azimProperties());
    membersData.append(cc_plugin::field::rxm::elevProperties());
    membersData.append(cc_plugin::field::rxm::ageProperties());

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
    props.append(cc_plugin::field::rxm::itowProperties());
    props.append(cc_plugin::field::rxm::weekProperties());
    props.append(cc_plugin::field::rxm::numVisProperties());
    props.append(cc_plugin::field::rxm::numSvProperties());
    props.append(createDataListProperties());

    assert(props.size() == RxmSvsi::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

const char* RxmSvsi::nameImpl() const
{
    static const char* Str = "RXM-SVSI";
    return Str;
}

const QVariantList& RxmSvsi::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

