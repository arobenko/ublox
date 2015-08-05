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

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createSingleRateProperties()
{
    QVariantList membersProps;
    membersProps.append(cc_plugin::field::msgIdProperties());
    membersProps.append(cc_plugin::field::cfg::rateProperties());

    static const QString Name("Single Rate");
    auto bundleProps = cc::Property::createPropertiesMap(Name, std::move(membersProps));
    return cc::Property::createPropertiesMap(Name, std::move(bundleProps));
}

QVariantMap createMultiRateProperties()
{
    QVariantList membersProps;
    membersProps.append(cc_plugin::field::msgIdProperties());
    membersProps.append(cc_plugin::field::cfg::rateProperties(0));
    membersProps.append(cc_plugin::field::cfg::rateProperties(1));
    membersProps.append(cc_plugin::field::cfg::rateProperties(2));
    membersProps.append(cc_plugin::field::cfg::rateProperties(3));

    static const QString Name("Multi Rate");
    auto bundleProps = cc::Property::createPropertiesMap(Name, std::move(membersProps));
    auto listProps = cc::Property::createPropertiesMap(Name, std::move(bundleProps));
    cc::Property::setSerialisedHidden(listProps);
    auto optListProps = cc::Property::createPropertiesMap(Name, std::move(listProps));
    cc::Property::setUncheckable(optListProps);
    return optListProps;
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createSingleRateProperties());
    props.append(createMultiRateProperties());

    assert(props.size() == CfgMsg::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

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

