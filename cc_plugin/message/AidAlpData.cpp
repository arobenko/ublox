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

#include "AidAlpData.h"

#include "cc_plugin/field/common.h"

template class ublox::message::AidAlpData<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::AidAlpData<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::AidAlpData>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_alpData()
{
    auto elemProps = cc::Property::createPropertiesMap(QString());
    auto props = cc::Property::createPropertiesMap("alpData", std::move(elemProps));
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_alpData());
    assert(props.size() == AidAlpData::FieldIdx_numOfValues);
    return props;
}

}  // namespace

AidAlpData::AidAlpData() = default;
AidAlpData::~AidAlpData() = default;

AidAlpData& AidAlpData::operator=(const AidAlpData&) = default;
AidAlpData& AidAlpData::operator=(AidAlpData&&) = default;

const char* AidAlpData::nameImpl() const
{
    static const char* Str = "AID-ALP (Data)";
    return Str;
}

const QVariantList& AidAlpData::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

