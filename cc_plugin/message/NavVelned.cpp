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

#include "NavVelned.h"
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
    props.append(cc_plugin::field::nav::velPropertiesN());
    props.append(cc_plugin::field::nav::velPropertiesE());
    props.append(cc_plugin::field::nav::velPropertiesD());
    props.append(cc_plugin::field::nav::speedProperties());
    props.append(cc_plugin::field::nav::groundSpeedProperties());
    props.append(cc_plugin::field::nav::headingProperties());
    props.append(cc_plugin::field::nav::saccProperties());
    props.append(cc_plugin::field::nav::caccProperties());

    assert(props.size() == NavVelned::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

const char* NavVelned::nameImpl() const
{
    static const char* Str = "NAV-VELNED";
    return Str;
}

const QVariantList& NavVelned::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

