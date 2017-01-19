//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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

using ublox::message::TimTm2Fields;

QVariantMap createProps_flags()
{
    cc::property::field::ForField<TimTm2Fields::flagsLowBits> lowFlagsProps;
    lowFlagsProps.name("flags")
                 .add("mode")
                 .add("run")
                 .add("newFallingEdge")
                 .serialisedHidden();
    assert(lowFlagsProps.bits().size() == TimTm2Fields::flagsLowBits::BitIdx_numOfValues);

    cc::property::field::ForField<TimTm2Fields::timeBase> timeBaseProps;
    timeBaseProps.name("timeBase")
                 .add("Receiver Time")
                 .add("GPS")
                 .add("UTC")
                 .serialisedHidden();
    assert(timeBaseProps.values().size() == (int)TimTm2Fields::TimeBase::NumOfValues);

    cc::property::field::ForField<TimTm2Fields::flagsHighBits> highFlagsProps;
    highFlagsProps.add("utc")
                  .add("time")
                  .add("newRisingEdge")
                  .serialisedHidden();
    assert(highFlagsProps.bits().size() == TimTm2Fields::flagsHighBits::BitIdx_numOfValues);

    cc::property::field::ForField<TimTm2Fields::flags> props;
    props.name("flags")
         .add(lowFlagsProps.asMap())
         .add(timeBaseProps.asMap())
         .add(highFlagsProps.asMap());
    assert(props.members().size() == TimTm2Fields::flags::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<TimTm2Fields::ch>().name("ch").asMap());
    props.append(createProps_flags());
    props.append(
        cc::property::field::ForField<TimTm2Fields::count>().name("count").asMap());
    props.append(
        cc::property::field::ForField<TimTm2Fields::wnR>().name("wnR").asMap());
    props.append(
        cc::property::field::ForField<TimTm2Fields::wnF>().name("wnF").asMap());
    props.append(
        cc::property::field::ForField<TimTm2Fields::towMsR>().name("towMsR").asMap());
    props.append(
        cc::property::field::ForField<TimTm2Fields::towSubMsR>().name("towSubMsR").asMap());
    props.append(
        cc::property::field::ForField<TimTm2Fields::towMsF>().name("towMsF").asMap());
    props.append(
        cc::property::field::ForField<TimTm2Fields::towSubMsF>().name("towSubMsF").asMap());
    props.append(
        cc::property::field::ForField<TimTm2Fields::accEst>().name("accEst").asMap());
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

