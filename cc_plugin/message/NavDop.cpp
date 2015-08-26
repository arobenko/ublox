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

#include <cassert>

#include "NavDop.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavDop<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavDop<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavDop>;


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
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(cc_plugin::field::nav::createProps_xDOP('g'));
    props.append(cc_plugin::field::nav::props_pDOP());
    props.append(cc_plugin::field::nav::createProps_xDOP('t'));
    props.append(cc_plugin::field::nav::createProps_xDOP('v'));
    props.append(cc_plugin::field::nav::createProps_xDOP('h'));
    props.append(cc_plugin::field::nav::createProps_xDOP('n'));
    props.append(cc_plugin::field::nav::createProps_xDOP('e'));

    assert(props.size() == NavDop::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavDop::NavDop() = default;
NavDop::~NavDop() = default;

NavDop& NavDop::operator=(const NavDop&) = default;
NavDop& NavDop::operator=(NavDop&&) = default;

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

