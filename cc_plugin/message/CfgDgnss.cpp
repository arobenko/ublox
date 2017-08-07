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

#include "CfgDgnss.h"

#include <cassert>

#include "cc_plugin/field/common.h"

template class ublox::message::CfgDgnss<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgDgnss<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgDgnss>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgDgnssFields;

QVariantMap createProps_dgnssMode()
{
    using Field = CfgDgnssFields::dgnssMode;
    auto props =
        cc::property::field::ForField<Field>()
            .name("dngssMode")
            .add("RTK float")
            .add("RTK fixed")
        ;
    assert(props.values().size() == (int)Field::ValueType::NumOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_dgnssMode());
    props.append(cc_plugin::field::common::props_reserved(1));

    assert(props.size() == CfgDgnss::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgDgnss::CfgDgnss() = default;
CfgDgnss::~CfgDgnss() = default;

CfgDgnss& CfgDgnss::operator=(const CfgDgnss&) = default;
CfgDgnss& CfgDgnss::operator=(CfgDgnss&&) = default;

const char* CfgDgnss::nameImpl() const
{
    static const char* Str = "CFG-DGNSS";
    return Str;
}

const QVariantList& CfgDgnss::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

