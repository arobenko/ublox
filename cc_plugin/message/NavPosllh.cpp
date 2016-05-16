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

#include <cassert>

#include "NavPosllh.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavPosllh<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavPosllh<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavPosllh>;


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
    props.append(cc_plugin::field::nav::props_lon());
    props.append(cc_plugin::field::nav::props_lat());
    props.append(cc_plugin::field::nav::props_height());
    props.append(cc_plugin::field::nav::props_hMSL());
    props.append(cc_plugin::field::nav::props_hAcc());
    props.append(cc_plugin::field::nav::props_vAcc());

    assert(props.size() == NavPosllh::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavPosllh::NavPosllh() = default;
NavPosllh::~NavPosllh() = default;

NavPosllh& NavPosllh::operator=(const NavPosllh&) = default;
NavPosllh& NavPosllh::operator=(NavPosllh&&) = default;


const char* NavPosllh::nameImpl() const
{
    static const char* Str = "NAV-POSLLH";
    return Str;
}

const QVariantList& NavPosllh::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

