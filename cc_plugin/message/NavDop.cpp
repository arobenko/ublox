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

#include "NavDop.h"
#include "cc_plugin/field/nav.h"

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::itowProperties());
    props.append(cc_plugin::field::nav::gdopProperties());
    props.append(cc_plugin::field::nav::pdopProperties());
    props.append(cc_plugin::field::nav::tdopProperties());
    props.append(cc_plugin::field::nav::vdopProperties());
    props.append(cc_plugin::field::nav::hdopProperties());
    props.append(cc_plugin::field::nav::ndopProperties());
    props.append(cc_plugin::field::nav::edopProperties());

    assert(props.size() == NavDop::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

const char* NavDop::nameImpl() const
{
    static const char* Str = "NAV-DOP";
    return Str;
}

const QVariantList& NavDop::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

