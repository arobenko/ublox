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

using ublox::message::MonHw2Fields;

QVariantMap createProps_cfgSource()
{
    return
        cc::property::field::ForField<MonHw2Fields::cfgSource>()
            .name("cfgSource")
            .add("flash image", (int)MonHw2Fields::CfgSource::FlashImage)
            .add("OTP", (int)MonHw2Fields::CfgSource::OTP)
            .add("config pins", (int)MonHw2Fields::CfgSource::ConfigPins)
            .add("ROM", (int)MonHw2Fields::CfgSource::ROM)
            .asMap();
}

QVariantMap createProps_reserved1()
{
    return
        cc::property::field::ForField<MonHw2Fields::reserved1>()
            .name("reserved1")
            .add(cc::property::field::IntValue().serialisedHidden().asMap())
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MonHw2Fields::ofsI>().name("ofsI").asMap());
    props.append(
        cc::property::field::ForField<MonHw2Fields::magI>().name("magI").asMap());
    props.append(
        cc::property::field::ForField<MonHw2Fields::ofsQ>().name("ofsQ").asMap());
    props.append(
        cc::property::field::ForField<MonHw2Fields::magQ>().name("magQ").asMap());
    props.append(createProps_cfgSource());
    props.append(cc_plugin::field::common::props_reserved(0));
    props.append(
        cc::property::field::ForField<MonHw2Fields::lowLevelCfg>().name("lowLevelCfg").asMap());
    props.append(createProps_reserved1());
    props.append(
        cc::property::field::ForField<MonHw2Fields::postStatus>().name("postStatus").asMap());
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

