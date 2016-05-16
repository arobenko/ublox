//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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

#include "NavVelned.h"

#include <cassert>

#include "cc_plugin/field/nav.h"

template class ublox::message::NavVelned<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavVelned<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavVelned>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::NavVelnedFields;

QVariantMap createProps_speed()
{
    return
        cc::property::field::ForField<NavVelnedFields::speed>()
            .name("speed")
            .asMap();
}

QVariantMap createProps_cAcc()
{
    return
        cc::property::field::ForField<NavVelnedFields::cAcc>()
            .name("cAcc")
            .scaledDecimals(5)
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(cc_plugin::field::nav::props_velN());
    props.append(cc_plugin::field::nav::props_velE());
    props.append(cc_plugin::field::nav::props_velD());
    props.append(createProps_speed());
    props.append(cc_plugin::field::nav::props_gSpeed());
    props.append(cc_plugin::field::nav::props_heading());
    props.append(cc_plugin::field::nav::props_sAcc());
    props.append(createProps_cAcc());

    assert(props.size() == NavVelned::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavVelned::NavVelned() = default;
NavVelned::~NavVelned() = default;

NavVelned& NavVelned::operator=(const NavVelned&) = default;
NavVelned& NavVelned::operator=(NavVelned&&) = default;


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

