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

QVariantMap createSingleDataElementProperties()
{
    QVariantList membersData;
    membersData.append(cc_plugin::field::cfg::protocolIdProperties());
    membersData.append(cc_plugin::field::common::resProperties(0));
    membersData.append(cc_plugin::field::common::resProperties(1));
    membersData.append(cc_plugin::field::cfg::infMsgMaskProperties(0));
    membersData.append(cc_plugin::field::cfg::infMsgMaskProperties(1));
    membersData.append(cc_plugin::field::cfg::infMsgMaskProperties(2));
    membersData.append(cc_plugin::field::cfg::infMsgMaskProperties(3));

    QVariantMap props;
    cc::Property::setData(props, std::move(membersData));
    return props;
}

QVariantMap createListProperties()
{
    auto props = cc::Property::createPropertiesMap("List", createSingleDataElementProperties());
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createListProperties());

    assert(props.size() == CfgInf::FieldIdx_NumOfValues);
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

