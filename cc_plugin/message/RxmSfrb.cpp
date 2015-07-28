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

#include "RxmSfrb.h"
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

QVariantMap createDataListProperties()
{
    auto props =
        cc::Property::createPropertiesMap(
            "Data",
            QVariant::fromValue(cc_plugin::field::rxm::dwordProperties()));
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::rxm::chnProperties());
    props.append(cc_plugin::field::rxm::svidProperties());
    props.append(createDataListProperties());

    assert(props.size() == RxmSfrb::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

const char* RxmSfrb::nameImpl() const
{
    static const char* Str = "RXM-SFRB";
    return Str;
}

const QVariantList& RxmSfrb::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

