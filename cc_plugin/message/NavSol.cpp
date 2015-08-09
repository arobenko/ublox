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

#include "NavSol.h"
#include "cc_plugin/field/common.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavSol<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavSol<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavSol>;

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
    props.append(cc_plugin::field::nav::fracProperties());
    props.append(cc_plugin::field::nav::weekProperties());
    props.append(cc_plugin::field::nav::gpsFixProperties());
    props.append(cc_plugin::field::nav::flagsProperties());
    props.append(cc_plugin::field::nav::ecefPropertiesX());
    props.append(cc_plugin::field::nav::ecefPropertiesY());
    props.append(cc_plugin::field::nav::ecefPropertiesZ());
    props.append(cc_plugin::field::nav::paccProperties());
    props.append(cc_plugin::field::nav::ecefPropertiesVX());
    props.append(cc_plugin::field::nav::ecefPropertiesVY());
    props.append(cc_plugin::field::nav::ecefPropertiesVZ());
    props.append(cc_plugin::field::nav::saccProperties());
    props.append(cc_plugin::field::nav::pdopProperties());
    props.append(cc_plugin::field::common::resProperties(1));
    props.append(cc_plugin::field::nav::numSvProperties());
    props.append(cc_plugin::field::common::resProperties(2));

    assert(props.size() == NavSol::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

NavSol::NavSol() = default;
NavSol::~NavSol() = default;

NavSol& NavSol::operator=(const NavSol&) = default;
NavSol& NavSol::operator=(NavSol&&) = default;

const char* NavSol::nameImpl() const
{
    static const char* Str = "NAV-SOL";
    return Str;
}

const QVariantList& NavSol::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

