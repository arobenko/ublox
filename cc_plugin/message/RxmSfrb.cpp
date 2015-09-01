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

#include "RxmSfrb.h"
#include "cc_plugin/field/rxm.h"
#include "cc_plugin/field/common.h"

template class ublox::message::RxmSfrb<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::RxmSfrb<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::RxmSfrb>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_dwrd()
{
    QVariantList elemsProps;
    for (auto idx = 0U; idx < 10U; ++idx) {
        elemsProps.append(cc::Property::createPropertiesMap(QString("%1").arg(idx, 1, 10, QChar('0'))));
    }

    auto props =
        cc::Property::createPropertiesMap(
            "dwrd",
            QVariant::fromValue(elemsProps));
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::Property::createPropertiesMap("chn"));
    props.append(cc_plugin::field::rxm::props_svid());
    props.append(createProps_dwrd());

    assert(props.size() == RxmSfrb::FieldIdx_numOfValues);
    return props;
}

}  // namespace

RxmSfrb::RxmSfrb() = default;
RxmSfrb::~RxmSfrb() = default;

RxmSfrb& RxmSfrb::operator=(const RxmSfrb&) = default;
RxmSfrb& RxmSfrb::operator=(RxmSfrb&&) = default;

const char* RxmSfrb::nameImpl() const
{
    static const char* Str = "RXM-SFRB";
    return Str;
}

const QVariantList& RxmSfrb::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

