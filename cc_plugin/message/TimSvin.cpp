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

#include "TimSvin.h"
#include "cc_plugin/field/common.h"

template class ublox::message::TimSvin<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::TimSvin<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::TimSvin>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{


QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::Property::createPropertiesMap("dur"));
    props.append(cc::Property::createPropertiesMap("meanX"));
    props.append(cc::Property::createPropertiesMap("meanY"));
    props.append(cc::Property::createPropertiesMap("meanZ"));
    props.append(cc::Property::createPropertiesMap("meanV"));
    props.append(cc::Property::createPropertiesMap("obs"));
    props.append(cc::Property::createPropertiesMap("valid"));
    props.append(cc::Property::createPropertiesMap("active"));
    props.append(cc_plugin::field::common::props_reserved(1));

    assert(props.size() == TimSvin::FieldIdx_numOfValues);
    return props;
}

}  // namespace

TimSvin::TimSvin() = default;
TimSvin::~TimSvin() = default;

TimSvin& TimSvin::operator=(const TimSvin&) = default;
TimSvin& TimSvin::operator=(TimSvin&&) = default;

const char* TimSvin::nameImpl() const
{
    static const char* Str = "TIM-SVIN";
    return Str;
}

const QVariantList& TimSvin::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

