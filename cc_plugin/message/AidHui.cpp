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

#include "AidHui.h"

template class ublox::message::AidHui<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::AidHui<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::AidHui>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_flags()
{
    QVariantList bitNames;
    bitNames.append("healthValid");
    bitNames.append("utcValid");
    bitNames.append("klobValid");
    assert(bitNames.size() == ublox::message::AidHuiField_flags_numOfValues);
    return cc::Property::createPropertiesMap("flags", std::move(bitNames));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::Property::createPropertiesMap("health"));
    props.append(cc::Property::createPropertiesMap("utcA0"));
    props.append(cc::Property::createPropertiesMap("utcA1"));
    props.append(cc::Property::createPropertiesMap("utcTOW"));
    props.append(cc::Property::createPropertiesMap("utcWNT"));
    props.append(cc::Property::createPropertiesMap("utcLS"));
    props.append(cc::Property::createPropertiesMap("utcWNF"));
    props.append(cc::Property::createPropertiesMap("utcDN"));
    props.append(cc::Property::createPropertiesMap("utcLSF"));
    props.append(cc::Property::createPropertiesMap("utcSpare"));
    props.append(cc::Property::createPropertiesMap("klobA0"));
    props.append(cc::Property::createPropertiesMap("klobA1"));
    props.append(cc::Property::createPropertiesMap("klobA2"));
    props.append(cc::Property::createPropertiesMap("klobA3"));
    props.append(cc::Property::createPropertiesMap("klobB0"));
    props.append(cc::Property::createPropertiesMap("klobB1"));
    props.append(cc::Property::createPropertiesMap("klobB2"));
    props.append(cc::Property::createPropertiesMap("klobB3"));
    props.append(createProps_flags());
    assert(props.size() == AidHui::FieldIdx_numOfValues);
    return props;
}

}  // namespace

AidHui::AidHui() = default;
AidHui::~AidHui() = default;

AidHui& AidHui::operator=(const AidHui&) = default;
AidHui& AidHui::operator=(AidHui&&) = default;


const char* AidHui::nameImpl() const
{
    static const char* Str = "AID-HUI";
    return Str;
}

const QVariantList& AidHui::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

