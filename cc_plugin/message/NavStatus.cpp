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

#include "NavStatus.h"
#include "cc_plugin/field/common.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavStatus<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavStatus<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavStatus>;


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
    props.append(cc_plugin::field::nav::gpsFixProperties());
    props.append(cc_plugin::field::nav::flagsProperties());
    props.append(cc_plugin::field::nav::diffStatusProperties());
    props.append(cc_plugin::field::common::resProperties());
    props.append(cc_plugin::field::nav::ttffProperties());
    props.append(cc_plugin::field::nav::msssProperties());

    assert(props.size() == NavStatus::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

NavStatus::NavStatus() = default;
NavStatus::~NavStatus() = default;

NavStatus& NavStatus::operator=(const NavStatus&) = default;
NavStatus& NavStatus::operator=(NavStatus&&) = default;


const char* NavStatus::nameImpl() const
{
    static const char* Str = "NAV-STATUS";
    return Str;
}

const QVariantList& NavStatus::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

