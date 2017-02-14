//
// Copyright 2017 (C). Alex Robenko. All rights reserved.
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

#include "CfgDynseed.h"

#include <cassert>

#include "cc_plugin/field/common.h"

template class ublox::message::CfgDynseed<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgDynseed<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgDynseed>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgDynseedFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<CfgDynseedFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<CfgDynseedFields::seedHi>().name("seedHi").asMap());
    props.append(
        cc::property::field::ForField<CfgDynseedFields::seedLo>().name("seedLo").asMap());

    assert(props.size() == CfgDynseed::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgDynseed::CfgDynseed() = default;
CfgDynseed::~CfgDynseed() = default;

CfgDynseed& CfgDynseed::operator=(const CfgDynseed&) = default;
CfgDynseed& CfgDynseed::operator=(CfgDynseed&&) = default;


const char* CfgDynseed::nameImpl() const
{
    static const char* Str = "CFG-DYNSEED";
    return Str;
}

const QVariantList& CfgDynseed::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

