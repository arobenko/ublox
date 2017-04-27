//
// Copyright 2017 (C). Alex Robenko. All rights reserved.
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

#include "TimTos.h"
#include "cc_plugin/field/common.h"

template class ublox::message::TimTos<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::TimTos<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::TimTos>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::TimTosFields;

QVariantMap createProps_flagsLow()
{
    using Field = TimTosFields::flagsLow;
    auto props =
        cc::property::field::ForField<Field>()
            .name("flags")
            .serialisedHidden()
            .add("leapNow")
            .add("leapSoon")
            .add("leapPositive")
            .add("timeInLimit")
            .add("intOscInLimit")
            .add("extOscInLimit")
            .add("gnssTimeValid")
            .add("UTCTimeValid");
    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_discSrc()
{
    using Field = TimTosFields::discSrc;
    auto props =
        cc::property::field::ForField<Field>()
            .name("discSrc")
            .serialisedHidden()
            .add("internal")
            .add("GNSS")
            .add("EXTINT0")
            .add("EXTINT1")
            .add("host internal")
            .add("host external");
    assert(props.values().size() == (int)Field::ValueType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_flagsHigh()
{
    using Field = TimTosFields::flagsHigh;
    auto props =
        cc::property::field::ForField<Field>()
            .serialisedHidden()
            .add("raim")
            .add("cohPulse")
            .add("lockedPulse");
    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_flags()
{
    using Field = TimTosFields::flags;
    auto props =
        cc::property::field::ForField<Field>()
            .name("flags")
            .add(createProps_flagsLow())
            .add(createProps_discSrc())
            .add(createProps_flagsHigh());
    assert(props.members().size() == Field::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<TimTosFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_gnssId());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_flags());
    props.append(
        cc::property::field::ForField<TimTosFields::year>().name("year").asMap());
    props.append(
        cc::property::field::ForField<TimTosFields::month>().name("month").asMap());
    props.append(
        cc::property::field::ForField<TimTosFields::day>().name("day").asMap());
    props.append(
        cc::property::field::ForField<TimTosFields::hour>().name("hour").asMap());
    props.append(
        cc::property::field::ForField<TimTosFields::minute>().name("minute").asMap());
    props.append(
        cc::property::field::ForField<TimTosFields::second>().name("second").asMap());
    props.append(cc_plugin::field::common::createProps_utcStandard());
    props.append(
        cc::property::field::ForField<TimTosFields::utcOffset>().name("utcOffset").asMap());
    props.append(
        cc::property::field::ForField<TimTosFields::utcUncertainty>().name("utcUncertainty").asMap());
    props.append(
        cc::property::field::ForField<TimTosFields::week>().name("week").asMap());
    props.append(
        cc::property::field::ForField<TimTosFields::TOW>().name("TOW").asMap());
    props.append(
        cc::property::field::ForField<TimTosFields::gnssOffset>().name("gnssOffset").asMap());
    props.append(
        cc::property::field::ForField<TimTosFields::gnssUncertainty>().name("gnssUncertainty").asMap());
    props.append(
        cc::property::field::ForField<TimTosFields::intOscOffset>()
            .name("intOscOffset")
            .scaledDecimals(4)
            .asMap());
    props.append(
        cc::property::field::ForField<TimTosFields::intOscUncertainty>()
            .name("intOscUncertainty")
            .scaledDecimals(4)
            .asMap());
    props.append(
        cc::property::field::ForField<TimTosFields::extOscOffset>()
            .name("extOscOffset")
            .scaledDecimals(4)
            .asMap());
    props.append(
        cc::property::field::ForField<TimTosFields::extOscUncertainty>()
            .name("extOscUncertainty")
            .scaledDecimals(4)
            .asMap());

    assert(props.size() == TimTos::FieldIdx_numOfValues);
    return props;
}

}  // namespace

TimTos::TimTos() = default;
TimTos::~TimTos() = default;

TimTos& TimTos::operator=(const TimTos&) = default;
TimTos& TimTos::operator=(TimTos&&) = default;

const char* TimTos::nameImpl() const
{
    static const char* Str = "TIM-TOS";
    return Str;
}

const QVariantList& TimTos::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

