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

#include <cassert>

#include "MgaBdsHealth.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaBdsHealth<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaBdsHealth<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaBdsHealth>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaBdsHealthFields;

QVariantMap createProps_healthCode()
{
    auto props =
        cc::property::field::ForField<MgaBdsHealthFields::healthCode<> >()
            .name("healthCode")
            .serialisedHidden();

    static const auto ElemCount =
            MgaBdsHealthFields::healthCode<>::ParsedOptions::SequenceFixedSize;
    for (auto idx = 0U; idx < ElemCount; ++idx) {
        auto elemProps =
            cc::property::field::ForField<MgaBdsHealthFields::healthCode<>::ValueType::value_type>()
                .name(QString("%1").arg(idx));
        props.add(elemProps.asMap());
    }
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaBdsHealthFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaBdsHealthFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_healthCode());
    props.append(cc_plugin::field::common::props_reserved(2));

    assert(props.size() == MgaBdsHealth::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaBdsHealth::MgaBdsHealth() = default;
MgaBdsHealth::~MgaBdsHealth() = default;

MgaBdsHealth& MgaBdsHealth::operator=(const MgaBdsHealth&) = default;
MgaBdsHealth& MgaBdsHealth::operator=(MgaBdsHealth&&) = default;

const char* MgaBdsHealth::nameImpl() const
{
    static const char* Str = "MGA-BDS-HEALTH";
    return Str;
}

const QVariantList& MgaBdsHealth::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

