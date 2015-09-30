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

#include "TimTm2.h"

template class ublox::message::TimTm2<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::TimTm2<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::TimTm2>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_towSubMS()
{
    auto props = cc::Property::createPropertiesMap("towSubMS");
    cc::Property::setDisplayScaled(props);
    cc::Property::setFloatDecimals(props, 2);
    return props;
}

QVariantMap createProps_flags()
{
    QVariantList lowBitNames;
    lowBitNames.append("mode");
    lowBitNames.append("run");
    lowBitNames.append("newFallingEdge");
    assert(lowBitNames.size() == ublox::message::TimTm2Field_flags_low_numOfValues);
    auto lowFlagsProps = cc::Property::createPropertiesMap("flags", std::move(lowBitNames));
    cc::Property::setSerialisedHidden(lowFlagsProps);

    QVariantList timeBaseEnumValues;
    cc::Property::appendEnumValue(timeBaseEnumValues, "Receiver Time");
    cc::Property::appendEnumValue(timeBaseEnumValues, "GPS");
    cc::Property::appendEnumValue(timeBaseEnumValues, "UTC");
    assert(timeBaseEnumValues.size() == (int)ublox::message::TimTm2_TimeBase::NumOfValues);
    auto timeBaseProps = cc::Property::createPropertiesMap("timeBase", std::move(timeBaseEnumValues));
    cc::Property::setSerialisedHidden(timeBaseProps);

    QVariantList highBitNames;
    highBitNames.append("utc");
    highBitNames.append("time");
    highBitNames.append("newRisingEdge");
    assert(highBitNames.size() == ublox::message::TimTm2Field_flags_high_numOfValues);
    auto highFlagsProps = cc::Property::createPropertiesMap(QString(), std::move(highBitNames));
    cc::Property::setSerialisedHidden(highFlagsProps);

    QVariantList membersData;
    membersData.append(std::move(lowFlagsProps));
    membersData.append(std::move(timeBaseProps));
    membersData.append(std::move(highFlagsProps));
    assert(membersData.size() == ublox::message::TimTm2Field_flags_numOfValues);
    return cc::Property::createPropertiesMap("flags", std::move(membersData));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::Property::createPropertiesMap("ch"));
    props.append(createProps_flags());
    props.append(cc::Property::createPropertiesMap("count"));
    props.append(cc::Property::createPropertiesMap("wnR"));
    props.append(cc::Property::createPropertiesMap("wnF"));
    props.append(cc::Property::createPropertiesMap("towMsR"));
    props.append(cc::Property::createPropertiesMap("towSubMsR"));
    props.append(cc::Property::createPropertiesMap("towMsF"));
    props.append(cc::Property::createPropertiesMap("towSubMsF"));
    props.append(cc::Property::createPropertiesMap("accEst"));
    assert(props.size() == TimTm2::FieldIdx_numOfValues);
    return props;
}

}  // namespace

TimTm2::TimTm2() = default;
TimTm2::~TimTm2() = default;

TimTm2& TimTm2::operator=(const TimTm2&) = default;
TimTm2& TimTm2::operator=(TimTm2&&) = default;

const char* TimTm2::nameImpl() const
{
    static const char* Str = "TIM-TM2";
    return Str;
}

const QVariantList& TimTm2::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

