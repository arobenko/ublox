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

#include "CfgPrt.h"
#include "cc_plugin/field/cfg.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgPrt<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgPrt<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgPrt>;

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
    membersData.append(cc_plugin::field::cfg::portIdProperties());
    membersData.append(cc_plugin::field::common::resProperties(0));
    membersData.append(cc_plugin::field::common::resProperties(1));
    membersData.append(cc_plugin::field::cfg::prtModeProperties());
    membersData.append(cc_plugin::field::cfg::baudrateProperties());
    membersData.append(cc_plugin::field::cfg::inProtoMaskProperties());
    membersData.append(cc_plugin::field::cfg::outProtoMaskProperties());
    membersData.append(cc_plugin::field::cfg::prtFlagsProperties());
    membersData.append(cc_plugin::field::common::padProperties());

    QVariantMap props;
    cc::Property::setData(props, std::move(membersData));
    return props;
}

QVariantMap createDataListProperties()
{
    auto props = cc::Property::createPropertiesMap("List", createSingleDataElementProperties());
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createDataListProperties());

    assert(props.size() == CfgPrt::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

CfgPrt::CfgPrt() = default;
CfgPrt::~CfgPrt() = default;

CfgPrt& CfgPrt::operator=(const CfgPrt&) = default;
CfgPrt& CfgPrt::operator=(CfgPrt&&) = default;


const char* CfgPrt::nameImpl() const
{
    static const char* Str = "CFG-PRT";
    return Str;
}

const QVariantList& CfgPrt::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

