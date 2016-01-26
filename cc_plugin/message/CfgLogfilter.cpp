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

#include <type_traits>
#include <functional>
#include <cassert>

#include "CfgLogfilter.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgLogfilter<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgLogfilter<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgLogfilter>;

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
    bitNames.append("recordEnabled");
    bitNames.append("psmOncePerWakupEnabled");
    bitNames.append("applyAllFilterSettings");
    assert(bitNames.size() == ublox::message::CfgLogfilterFields::flags_numOfValues);
    return cc::Property::createPropertiesMap("flags", std::move(bitNames));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::Property::createPropertiesMap("version"));
    props.append(createProps_flags());
    props.append(cc::Property::createPropertiesMap("minInterval"));
    props.append(cc::Property::createPropertiesMap("timeThreshold"));
    props.append(cc::Property::createPropertiesMap("speedThreshold"));
    props.append(cc::Property::createPropertiesMap("positionThreshold"));
    assert(props.size() == CfgLogfilter::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgLogfilter::CfgLogfilter() = default;
CfgLogfilter::~CfgLogfilter() = default;

CfgLogfilter& CfgLogfilter::operator=(const CfgLogfilter&) = default;
CfgLogfilter& CfgLogfilter::operator=(CfgLogfilter&&) = default;


const char* CfgLogfilter::nameImpl() const
{
    static const char* Str = "CFG-LOGFILTER";
    return Str;
}

const QVariantList& CfgLogfilter::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

