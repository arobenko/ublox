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

QVariantMap createProps_timeMode()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "Disabled");
    cc::Property::appendEnumValue(enumValues, "Survey In");
    cc::Property::appendEnumValue(enumValues, "Fixed Mode");
    assert(enumValues.size() == (int)ublox::message::CfgTmodeFields::TimeMode::NumOfValues);
    return cc::Property::createPropertiesMap("timeMode", std::move(enumValues));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_timeMode());
    props.append(cc::Property::createPropertiesMap("fixedPosX"));
    props.append(cc::Property::createPropertiesMap("fixedPosY"));
    props.append(cc::Property::createPropertiesMap("fixedPosZ"));
    props.append(cc::Property::createPropertiesMap("fixedPosVar"));
    props.append(cc::Property::createPropertiesMap("svinMinDur"));
    props.append(cc::Property::createPropertiesMap("svinVarLimit"));

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

