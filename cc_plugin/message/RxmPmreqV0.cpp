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


#include "RxmPmreqV0.h"
#include "cc_plugin/field/common.h"

#include <cassert>

template class ublox::message::RxmPmreqV0<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::RxmPmreqV0<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::RxmPmreqV0>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::RxmPmreqV0Fields;

QVariantMap createProps_flags()
{
    using Field = RxmPmreqV0Fields::flags;
    auto props =
        cc::property::field::ForField<Field>()
            .name("flags")
            .add(Field::BitIdx_backup, "backup")
            .add("force");
    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_wakeupSources()
{
    using Field = RxmPmreqV0Fields::wakeupSources;
    auto props =
        cc::property::field::ForField<Field>()
            .name("wakeupSources")
            .add(Field::BitIdx_uartrx, "uartrx")
            .add(Field::BitIdx_extint0, "extint0")
            .add("extint1")
            .add("spics");
    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<RxmPmreqV0Fields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<RxmPmreqV0Fields::duration>().name("duration").asMap());
    props.append(createProps_flags());
    props.append(createProps_wakeupSources());
    assert(props.size() == RxmPmreqV0::FieldIdx_numOfValues);
    return props;
}

}  // namespace

RxmPmreqV0::RxmPmreqV0() = default;
RxmPmreqV0::~RxmPmreqV0() = default;

RxmPmreqV0& RxmPmreqV0::operator=(const RxmPmreqV0&) = default;
RxmPmreqV0& RxmPmreqV0::operator=(RxmPmreqV0&&) = default;

const char* RxmPmreqV0::nameImpl() const
{
    static const char* Str = "RXM-PMREQ (version 0)";
    return Str;
}

const QVariantList& RxmPmreqV0::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

