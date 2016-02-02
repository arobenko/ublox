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

#include "MonHw2.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MonHw2<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MonHw2<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MonHw2>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_cfgSource()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "flash image", (int)ublox::message::MonHw2Fields::CfgSource::FlashImage);
    cc::Property::appendEnumValue(enumValues, "OTP", (int)ublox::message::MonHw2Fields::CfgSource::OTP);
    cc::Property::appendEnumValue(enumValues, "config pins", (int)ublox::message::MonHw2Fields::CfgSource::ConfigPins);
    cc::Property::appendEnumValue(enumValues, "ROM", (int)ublox::message::MonHw2Fields::CfgSource::ROM);
    return cc::Property::createPropertiesMap("cfgSource", std::move(enumValues));
}

QVariantMap createProps_reserved1()
{
    auto elemProps = cc::Property::createPropertiesMap(QString());
    cc::Property::setSerialisedHidden(elemProps);
    return cc::Property::createPropertiesMap("reserved1", std::move(elemProps));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::Property::createPropertiesMap("ofsI"));
    props.append(cc::Property::createPropertiesMap("magI"));
    props.append(cc::Property::createPropertiesMap("ofsQ"));
    props.append(cc::Property::createPropertiesMap("magQ"));
    props.append(createProps_cfgSource());
    props.append(cc_plugin::field::common::props_reserved(0));
    props.append(cc::Property::createPropertiesMap("lowLevelCfg"));
    props.append(createProps_reserved1());
    props.append(cc::Property::createPropertiesMap("postStatus"));
    props.append(cc_plugin::field::common::props_reserved(2));
    assert(props.size() == MonHw2::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MonHw2::MonHw2() = default;
MonHw2::~MonHw2() = default;

MonHw2& MonHw2::operator=(const MonHw2&) = default;
MonHw2& MonHw2::operator=(MonHw2&&) = default;

const char* MonHw2::nameImpl() const
{
    static const char* Str = "MON-HW2";
    return Str;
}

const QVariantList& MonHw2::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

