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

#include "TimTp.h"
#include "cc_plugin/field/common.h"

template class ublox::message::TimTp<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::TimTp<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::TimTp>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::TimTpFields;

QVariantMap createProps_towSubMS()
{
    return
        cc::property::field::ForField<TimTpFields::towSubMS>()
            .name("towSubMS")
            .scaledDecimals(2)
            .asMap();
}

QVariantMap createProps_flags()
{
    cc::property::field::ForField<TimTpFields::flags> props;
    props.name("flags")
         .add("timeBase")
         .add("utc");
    assert(props.bits().size() == TimTpFields::flags_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<TimTpFields::towMS>().name("towMS").asMap());
    props.append(createProps_towSubMS());
    props.append(
        cc::property::field::ForField<TimTpFields::qErr>().name("qErr").asMap());
    props.append(
        cc::property::field::ForField<TimTpFields::week>().name("week").asMap());
    props.append(createProps_flags());
    props.append(cc_plugin::field::common::props_reserved(1));

    assert(props.size() == TimTp::FieldIdx_numOfValues);
    return props;
}

}  // namespace

TimTp::TimTp() = default;
TimTp::~TimTp() = default;

TimTp& TimTp::operator=(const TimTp&) = default;
TimTp& TimTp::operator=(TimTp&&) = default;

const char* TimTp::nameImpl() const
{
    static const char* Str = "TIM-TP";
    return Str;
}

const QVariantList& TimTp::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

