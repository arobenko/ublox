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

#include "CfgAnt.h"

template class ublox::message::CfgAnt<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgAnt<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgAnt>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_flags()
{
    QVariantList bitNames;
    bitNames.append("svcs");
    bitNames.append("scd");
    bitNames.append("ocd");
    bitNames.append("pdwnOnSCD");
    bitNames.append("recovery");
    assert(bitNames.size() == ublox::message::CfgAntField_flags_numOfValues);
    return cc::Property::createPropertiesMap("flags", std::move(bitNames));
}

QVariantMap createProps_pins()
{
    auto createPinPropsFunc =
        [](const char* name) -> QVariantMap
        {
            QVariantMap props = cc::Property::createPropertiesMap(name);
            cc::Property::setSerialisedHidden(props);
            return props;
        };

    QVariantList bitNames;
    bitNames.append("reconfig");
    assert(bitNames.size() == ublox::message::CfgAntField_pins_reconfig_numOfValues);
    auto reconfigProps = cc::Property::createPropertiesMap(QString(), std::move(bitNames));
    cc::Property::setSerialisedHidden(reconfigProps);

    QVariantList membersData;
    membersData.append(createPinPropsFunc("pinSwitch"));
    membersData.append(createPinPropsFunc("pinSCD"));
    membersData.append(createPinPropsFunc("pinOCD"));
    membersData.append(std::move(reconfigProps));
    assert(membersData.size() == ublox::message::CfgAntField_pins_numOfValues);
    return cc::Property::createPropertiesMap("pins", std::move(membersData));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_flags());
    props.append(createProps_pins());
    assert(props.size() == CfgAnt::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgAnt::CfgAnt() = default;
CfgAnt::~CfgAnt() = default;

CfgAnt& CfgAnt::operator=(const CfgAnt&) = default;
CfgAnt& CfgAnt::operator=(CfgAnt&&) = default;


const char* CfgAnt::nameImpl() const
{
    static const char* Str = "CFG-ANT";
    return Str;
}

const QVariantList& CfgAnt::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

