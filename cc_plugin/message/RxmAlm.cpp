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

#include "RxmAlm.h"
#include "cc_plugin/field/rxm.h"
#include "cc_plugin/field/common.h"

template class ublox::message::RxmAlm<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::RxmAlm<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::RxmAlm>;

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
    for (auto idx = 0U; idx < 8U; ++idx) {
        elemsProps.append(cc::Property::createPropertiesMap(QString("%1").arg(idx, 1, 10, QChar('0'))));
    }

    static const QString Name("dwrd");
    auto listProps =
        cc::Property::createPropertiesMap(
            Name,
            std::move(elemsProps));
    cc::Property::setSerialisedHidden(listProps);

    auto props = cc::Property::createPropertiesMap(Name, std::move(listProps));
    cc::Property::setUncheckable(props);
    return props;
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::rxm::props_svid());
    props.append(cc_plugin::field::rxm::props_week());
    props.append(createProps_dwrd());

    assert(props.size() == RxmAlm::FieldIdx_numOfValues);
    return props;
}

}  // namespace

RxmAlm::RxmAlm() = default;
RxmAlm::~RxmAlm() = default;

RxmAlm& RxmAlm::operator=(const RxmAlm&) = default;
RxmAlm& RxmAlm::operator=(RxmAlm&&) = default;


const char* RxmAlm::nameImpl() const
{
    static const char* Str = "RXM-ALM";
    return Str;
}

const QVariantList& RxmAlm::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

