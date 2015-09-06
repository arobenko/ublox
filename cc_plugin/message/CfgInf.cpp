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

#include <type_traits>
#include <functional>
#include <cassert>

#include "CfgInf.h"
#include "cc_plugin/field/cfg.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgInf<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgInf<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgInf>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_infMsgMask()
{
    auto createBitmaskProps =
        [](const char* name) -> QVariantMap
        {
            QVariantList bitNames;
            bitNames.append("ERROR");
            bitNames.append("WARNING");
            bitNames.append("NOTICE");
            bitNames.append("DEBUG");
            bitNames.append("TEST");

            return cc::Property::createPropertiesMap(name, std::move(bitNames));
        };

    QVariantList propsList;
    propsList.append(createBitmaskProps("DDC"));
    propsList.append(createBitmaskProps("UART"));
    propsList.append(createBitmaskProps("UART2"));
    propsList.append(createBitmaskProps("USB"));
    propsList.append(createBitmaskProps("SPI"));
    propsList.append(createBitmaskProps("RESERVED"));
    assert(propsList.size() == ublox::message::CfgInfField_element_infMsgMask_numOfValues);
    auto props = cc::Property::createPropertiesMap("infMsgMask", std::move(propsList));
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantMap createProps_list()
{
    QVariantList membersProps;
    membersProps.append(field::cfg::props_protocolID());
    membersProps.append(field::common::props_reserved(0));
    membersProps.append(field::common::props_reserved(1));
    membersProps.append(createProps_infMsgMask());
    assert(membersProps.size() == ublox::message::CfgInfField_element_numOfValues);

    auto elementProps = cc::Property::createPropertiesMap("element", std::move(membersProps));

    auto props = cc::Property::createPropertiesMap("list", std::move(elementProps));
    cc::Property::setSerialisedHidden(props);
    return props;
}


QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_list());

    assert(props.size() == CfgInf::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgInf::CfgInf() = default;
CfgInf::~CfgInf() = default;

CfgInf& CfgInf::operator=(const CfgInf&) = default;
CfgInf& CfgInf::operator=(CfgInf&&) = default;


const char* CfgInf::nameImpl() const
{
    static const char* Str = "CFG-INF";
    return Str;
}

const QVariantList& CfgInf::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

