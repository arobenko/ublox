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


#include "RxmRtcm.h"

#include <cassert>

#include "cc_plugin/field/common.h"

template class ublox::message::RxmRtcm<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::RxmRtcm<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::RxmRtcm>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::RxmRtcmFields;

QVariantMap createProps_flags()
{
    using Field = RxmRtcmFields::flags;
    auto props =
        cc::property::field::ForField<Field>()
            .name("flags")
            .add("crcFailed");
    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<RxmRtcmFields::version>().name("version").asMap());
    props.append(createProps_flags());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<RxmRtcmFields::refStation>().name("refStation").asMap());
    props.append(
        cc::property::field::ForField<RxmRtcmFields::msgType>().name("msgType").asMap());

    assert(props.size() == RxmRtcm::FieldIdx_numOfValues);
    return props;
}

}  // namespace

RxmRtcm::RxmRtcm() = default;
RxmRtcm::~RxmRtcm() = default;

RxmRtcm& RxmRtcm::operator=(const RxmRtcm&) = default;
RxmRtcm& RxmRtcm::operator=(RxmRtcm&&) = default;

const char* RxmRtcm::nameImpl() const
{
    static const char* Str = "RXM-RTCM";
    return Str;
}

const QVariantList& RxmRtcm::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

