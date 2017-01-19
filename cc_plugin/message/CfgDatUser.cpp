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

#include "CfgDatUser.h"
#include "cc_plugin/field/cfg.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgDatUser<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgDatUser<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgDatUser>;

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
    props.append(cc_plugin::field::cfg::props_datMajA());
    props.append(cc_plugin::field::cfg::props_datFlat());
    props.append(cc_plugin::field::cfg::props_datDX());
    props.append(cc_plugin::field::cfg::props_datDY());
    props.append(cc_plugin::field::cfg::props_datDZ());
    props.append(cc_plugin::field::cfg::props_datRotX());
    props.append(cc_plugin::field::cfg::props_datRotY());
    props.append(cc_plugin::field::cfg::props_datRotZ());
    props.append(cc_plugin::field::cfg::props_datScale());

    assert(props.size() == CfgDatUser::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgDatUser::CfgDatUser() = default;
CfgDatUser::~CfgDatUser() = default;

CfgDatUser& CfgDatUser::operator=(const CfgDatUser&) = default;
CfgDatUser& CfgDatUser::operator=(CfgDatUser&&) = default;


const char* CfgDatUser::nameImpl() const
{
    static const char* Str = "CFG-DAT (User)";
    return Str;
}

const QVariantList& CfgDatUser::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

