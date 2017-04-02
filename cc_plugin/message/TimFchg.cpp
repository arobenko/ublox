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

#include "TimFchg.h"
#include "cc_plugin/field/common.h"

template class ublox::message::TimFchg<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::TimFchg<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::TimFchg>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::TimFchgFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<TimFchgFields::version>().name("version").asMap());
        props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<TimFchgFields::iTOW>().name("iTOW").asMap());
    props.append(
        cc::property::field::ForField<TimFchgFields::intDeltaFreq>().name("intDeltaFreq").scaledDecimals(4).asMap());
    props.append(
        cc::property::field::ForField<TimFchgFields::intDeltaFreqUnc>().name("intDeltaFreqUnc").scaledDecimals(4).asMap());
    props.append(
        cc::property::field::ForField<TimFchgFields::intRaw>().name("intRaw").asMap());
    props.append(
        cc::property::field::ForField<TimFchgFields::extDeltaFreq>().name("extDeltaFreq").scaledDecimals(4).asMap());
    props.append(
        cc::property::field::ForField<TimFchgFields::extDeltaFreqUnc>().name("extDeltaFreqUnc").scaledDecimals(4).asMap());
    props.append(
        cc::property::field::ForField<TimFchgFields::extRaw>().name("extRaw").asMap());

    assert(props.size() == TimFchg::FieldIdx_numOfValues);
    return props;
}

}  // namespace

TimFchg::TimFchg() = default;
TimFchg::~TimFchg() = default;

TimFchg& TimFchg::operator=(const TimFchg&) = default;
TimFchg& TimFchg::operator=(TimFchg&&) = default;

const char* TimFchg::nameImpl() const
{
    static const char* Str = "TIM-FCHG";
    return Str;
}

const QVariantList& TimFchg::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

