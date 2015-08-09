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

#include "RxmRaw.h"
#include "cc_plugin/field/rxm.h"
#include "cc_plugin/field/common.h"

template class ublox::message::RxmRaw<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::RxmRaw<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::RxmRaw>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createSingleDataElementProperties()
{
    QVariantList membersData;
    membersData.append(cc_plugin::field::rxm::cpMesProperties());
    membersData.append(cc_plugin::field::rxm::prMesProperties());
    membersData.append(cc_plugin::field::rxm::doMesProperties());
    membersData.append(cc_plugin::field::rxm::svProperties());
    membersData.append(cc_plugin::field::rxm::mesQiProperties());
    membersData.append(cc_plugin::field::rxm::cnoProperties());
    membersData.append(cc_plugin::field::rxm::lliProperties());

    QVariantMap props;
    cc::Property::setData(props, std::move(membersData));
    return props;
}

QVariantMap createDataListProperties()
{
    auto props = cc::Property::createPropertiesMap("Data", createSingleDataElementProperties());
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::rxm::itowProperties());
    props.append(cc_plugin::field::rxm::weekProperties());
    props.append(cc_plugin::field::rxm::nsvProperties());
    props.append(cc_plugin::field::common::resProperties(1));
    props.append(createDataListProperties());

    assert(props.size() == RxmRaw::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

RxmRaw::RxmRaw() = default;
RxmRaw::~RxmRaw() = default;

RxmRaw& RxmRaw::operator=(const RxmRaw&) = default;
RxmRaw& RxmRaw::operator=(RxmRaw&&) = default;

const char* RxmRaw::nameImpl() const
{
    static const char* Str = "RXM-RAW";
    return Str;
}

const QVariantList& RxmRaw::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

