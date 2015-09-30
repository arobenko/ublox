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

#include "TimVrfy.h"
#include "cc_plugin/field/common.h"

template class ublox::message::TimVrfy<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::TimVrfy<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::TimVrfy>;

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
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "None", (int)ublox::message::TimVrfy_Src::None);
    cc::Property::appendEnumValue(enumValues, "RTC", (int)ublox::message::TimVrfy_Src::Rtc);
    cc::Property::appendEnumValue(enumValues, "AID-INI", (int)ublox::message::TimVrfy_Src::AidIni);
    return cc::Property::createPropertiesMap("src", std::move(enumValues));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::Property::createPropertiesMap("itow"));
    props.append(cc::Property::createPropertiesMap("frac"));
    props.append(cc::Property::createPropertiesMap("deltaMS"));
    props.append(cc::Property::createPropertiesMap("deltaNS"));
    props.append(cc::Property::createPropertiesMap("wno"));
    props.append(createProps_flags());
    props.append(cc_plugin::field::common::props_reserved(1));

    assert(props.size() == TimVrfy::FieldIdx_numOfValues);
    return props;
}

}  // namespace

TimVrfy::TimVrfy() = default;
TimVrfy::~TimVrfy() = default;

TimVrfy& TimVrfy::operator=(const TimVrfy&) = default;
TimVrfy& TimVrfy::operator=(TimVrfy&&) = default;

const char* TimVrfy::nameImpl() const
{
    static const char* Str = "TIM-VRFY";
    return Str;
}

const QVariantList& TimVrfy::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

