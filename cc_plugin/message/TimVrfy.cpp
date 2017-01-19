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

using ublox::message::TimVrfyFields;

QVariantMap createProps_flags()
{
    return
        cc::property::field::ForField<TimVrfyFields::src>()
            .name("src")
            .add("None", (int)TimVrfyFields::Src::None)
            .add("RTC", (int)TimVrfyFields::Src::Rtc)
            .add("AID-INI", (int)TimVrfyFields::Src::AidIni)
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<TimVrfyFields::itow>().name("itow").asMap());
    props.append(
        cc::property::field::ForField<TimVrfyFields::frac>().name("frac").asMap());
    props.append(
        cc::property::field::ForField<TimVrfyFields::deltaMS>().name("deltaMS").asMap());
    props.append(
        cc::property::field::ForField<TimVrfyFields::deltaNS>().name("deltaNS").asMap());
    props.append(
        cc::property::field::ForField<TimVrfyFields::wno>().name("wno").asMap());
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

