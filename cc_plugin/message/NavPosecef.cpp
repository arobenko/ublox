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

#include "NavPosecef.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavPosecef<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavPosecef<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavPosecef>;

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
    props.append(cc_plugin::field::nav::props_ecefX());
    props.append(cc_plugin::field::nav::props_ecefY());
    props.append(cc_plugin::field::nav::props_ecefZ());
    props.append(cc_plugin::field::nav::props_pAcc());

    assert(props.size() == NavPosecef::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

NavPosecef::NavPosecef() = default;
NavPosecef::~NavPosecef() = default;

NavPosecef& NavPosecef::operator=(const NavPosecef&) = default;
NavPosecef& NavPosecef::operator=(NavPosecef&&) = default;

const char* NavPosecef::nameImpl() const
{
    static const char* Str = "NAV-POSECEF";
    return Str;
}

const QVariantList& NavPosecef::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

