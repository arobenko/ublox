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

#include "NavTimeutc.h"

#include <cassert>

#include "cc_plugin/field/common.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavTimeutc<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavTimeutc<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavTimeutc>;


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
    props.append(cc_plugin::field::nav::taccProperties());
    props.append(cc_plugin::field::nav::nanoProperties());
    props.append(cc_plugin::field::nav::yearProperties());
    props.append(cc_plugin::field::nav::monthProperties());
    props.append(cc_plugin::field::nav::dayProperties());
    props.append(cc_plugin::field::nav::hourProperties());
    props.append(cc_plugin::field::nav::minProperties());
    props.append(cc_plugin::field::nav::secProperties());
    props.append(cc_plugin::field::nav::timeValidProperties());

    assert(props.size() == NavTimeutc::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

NavTimeutc::NavTimeutc() = default;
NavTimeutc::~NavTimeutc() = default;

NavTimeutc& NavTimeutc::operator=(const NavTimeutc&) = default;
NavTimeutc& NavTimeutc::operator=(NavTimeutc&&) = default;

const char* NavTimeutc::nameImpl() const
{
    static const char* Str = "NAV-TIMEUTC";
    return Str;
}

const QVariantList& NavTimeutc::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

