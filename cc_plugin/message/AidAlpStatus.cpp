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

#include "AidAlpStatus.h"

#include "cc_plugin/field/common.h"

template class ublox::message::AidAlpStatus<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::AidAlpStatus<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::AidAlpStatus>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_status()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "NAK");
    cc::Property::appendEnumValue(enumValues, "ACK");
    assert(enumValues.size() == (int)ublox::message::AidAlpStatusFields::Status::NumOfValues);
    return cc::Property::createPropertiesMap("status", std::move(enumValues));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_status());
    assert(props.size() == AidAlpStatus::FieldIdx_numOfValues);
    return props;
}

}  // namespace

AidAlpStatus::AidAlpStatus() = default;
AidAlpStatus::~AidAlpStatus() = default;

AidAlpStatus& AidAlpStatus::operator=(const AidAlpStatus&) = default;
AidAlpStatus& AidAlpStatus::operator=(AidAlpStatus&&) = default;

const char* AidAlpStatus::nameImpl() const
{
    static const char* Str = "AID-ALP (Status)";
    return Str;
}

const QVariantList& AidAlpStatus::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

