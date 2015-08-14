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

#include "CfgMsg.h"
#include "cc_plugin/field/MsgId.h"
#include "cc_plugin/field/cfg.h"

template class ublox::message::CfgMsg<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgMsg<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgMsg>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createListProperties()
{
    QVariantList membersProps;
    membersProps.append(cc_plugin::field::msgIdProperties());
    membersProps.append(cc_plugin::field::cfg::rateProperties(0));
    membersProps.append(cc_plugin::field::cfg::rateProperties(1));
    membersProps.append(cc_plugin::field::cfg::rateProperties(2));
    membersProps.append(cc_plugin::field::cfg::rateProperties(3));

    static const QString Name("List");
    auto bundleProps = cc::Property::createPropertiesMap(Name, std::move(membersProps));
    auto props = cc::Property::createPropertiesMap(Name, std::move(bundleProps));
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createListProperties());

    assert(props.size() == CfgMsg::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

CfgMsg::CfgMsg() = default;
CfgMsg::~CfgMsg() = default;

CfgMsg& CfgMsg::operator=(const CfgMsg&) = default;
CfgMsg& CfgMsg::operator=(CfgMsg&&) = default;


const char* CfgMsg::nameImpl() const
{
    static const char* Str = "CFG-MSG";
    return Str;
}

const QVariantList& CfgMsg::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

