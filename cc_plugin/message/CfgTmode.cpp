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

#include "CfgTmode.h"

template class ublox::message::CfgTmode<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgTmode<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgTmode>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgTmodeFields;

QVariantMap createProps_timeMode()
{
    cc::property::field::ForField<CfgTmodeFields::timeMode> props;
    props.name("timeMode")
         .add("Disabled")
         .add("Survey In")
         .add("Fixed Mode");
    assert(props.values().size() == (int)CfgTmodeFields::TimeMode::NumOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_timeMode());
    props.append(
        cc::property::field::ForField<CfgTmodeFields::fixedPosX>().name("fixedPosX").asMap());
    props.append(
        cc::property::field::ForField<CfgTmodeFields::fixedPosY>().name("fixedPosY").asMap());
    props.append(
        cc::property::field::ForField<CfgTmodeFields::fixedPosZ>().name("fixedPosZ").asMap());
    props.append(
        cc::property::field::ForField<CfgTmodeFields::fixedPosVar>().name("fixedPosVar").asMap());
    props.append(
        cc::property::field::ForField<CfgTmodeFields::svinMinDur>().name("svinMinDur").asMap());
    props.append(
        cc::property::field::ForField<CfgTmodeFields::svinVarLimit>().name("svinVarLimit").asMap());

    assert(props.size() == CfgTmode::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgTmode::CfgTmode() = default;
CfgTmode::~CfgTmode() = default;

CfgTmode& CfgTmode::operator=(const CfgTmode&) = default;
CfgTmode& CfgTmode::operator=(CfgTmode&&) = default;


const char* CfgTmode::nameImpl() const
{
    static const char* Str = "CFG-TMODE";
    return Str;
}

const QVariantList& CfgTmode::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

