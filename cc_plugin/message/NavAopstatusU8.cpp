//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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

#include <cassert>

#include "NavAopstatusU8.h"
#include "cc_plugin/field/common.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavAopstatusU8<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavAopstatusU8<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavAopstatusU8>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::NavAopstatusU8Fields;

QVariantMap createProps_aopCfg()
{
    cc::property::field::ForField<NavAopstatusU8Fields::aopCfg> props;
    props.name("aopCfg")
         .add("useAOP");
    assert(props.bits().size() == NavAopstatusU8Fields::aopCfg::BitIdx_numOfValues);
    return props.asMap();
}


QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(createProps_aopCfg());
    props.append(cc::property::field::ForField<NavAopstatusU8Fields::status>().name("status").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(cc_plugin::field::common::props_reserved(3));

    assert(props.size() == NavAopstatusU8::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavAopstatusU8::NavAopstatusU8() = default;
NavAopstatusU8::~NavAopstatusU8() = default;

NavAopstatusU8& NavAopstatusU8::operator=(const NavAopstatusU8&) = default;
NavAopstatusU8& NavAopstatusU8::operator=(NavAopstatusU8&&) = default;

const char* NavAopstatusU8::nameImpl() const
{
    static const char* Str = "NAV-AOPSTATUS (ublox-8)";
    return Str;
}

const QVariantList& NavAopstatusU8::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

