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

#include "AidAop.h"

template class ublox::message::AidAop<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::AidAop<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::AidAop>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_optional()
{
    static const QString Name("optional");
    auto valProps = cc::Property::createPropertiesMap(Name);
    return cc::Property::createPropertiesMap(Name, std::move(valProps));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::Property::createPropertiesMap("svid"));
    props.append(cc::Property::createPropertiesMap("data"));
    props.append(createProps_optional());

    assert(props.size() == AidAop::FieldIdx_numOfValues);
    return props;
}

}  // namespace

AidAop::AidAop() = default;
AidAop::~AidAop() = default;

AidAop& AidAop::operator=(const AidAop&) = default;
AidAop& AidAop::operator=(AidAop&&) = default;


const char* AidAop::nameImpl() const
{
    static const char* Str = "AID-AOP";
    return Str;
}

const QVariantList& AidAop::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

