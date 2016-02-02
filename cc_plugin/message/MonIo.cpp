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

#include "MonIo.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MonIo<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MonIo<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MonIo>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_data()
{
    QVariantList membersData;
    membersData.append(cc::Property::createPropertiesMap("rxBytes"));
    membersData.append(cc::Property::createPropertiesMap("txBytes"));
    membersData.append(cc::Property::createPropertiesMap("parityErrs"));
    membersData.append(cc::Property::createPropertiesMap("framingErrs"));
    membersData.append(cc::Property::createPropertiesMap("overrunErrs"));
    membersData.append(cc::Property::createPropertiesMap("breakCond"));
    membersData.append(cc::Property::createPropertiesMap("rxBusy"));
    membersData.append(cc::Property::createPropertiesMap("txBusy"));
    membersData.append(cc_plugin::field::common::props_reserved(1));
    assert(membersData.size() == ublox::message::MonIoFields::block_numOfValues);

    auto bundleProps = cc::Property::createPropertiesMap("block", std::move(membersData));
    auto props = cc::Property::createPropertiesMap("data", std::move(bundleProps));
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_data());

    assert(props.size() == MonIo::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MonIo::MonIo() = default;
MonIo::~MonIo() = default;

MonIo& MonIo::operator=(const MonIo&) = default;
MonIo& MonIo::operator=(MonIo&&) = default;

const char* MonIo::nameImpl() const
{
    static const char* Str = "MON-IO";
    return Str;
}

const QVariantList& MonIo::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

