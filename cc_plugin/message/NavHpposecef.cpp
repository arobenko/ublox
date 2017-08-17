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

#include "NavHpposecef.h"
#include "cc_plugin/field/nav.h"
#include "cc_plugin/field/common.h"

template class ublox::message::NavHpposecef<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavHpposecef<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavHpposecef>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

using NavHpposecefFields = ublox::message::NavHpposecefFields;
namespace
{

QVariantMap createProps_ecefHp(char dir)
{
    return
        cc::property::field::IntValue()
            .name(QString("edef%1Hp").arg(dir))
            .scaledDecimals(1)
            .asMap();
}

QVariantMap createProps_pAcc()
{
    return
        cc::property::field::IntValue()
            .name("pAcc")
            .scaledDecimals(1)
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<NavHpposecefFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(cc_plugin::field::nav::props_ecefX());
    props.append(cc_plugin::field::nav::props_ecefY());
    props.append(cc_plugin::field::nav::props_ecefZ());
    props.append(createProps_ecefHp('X'));
    props.append(createProps_ecefHp('Y'));
    props.append(createProps_ecefHp('Z'));
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(createProps_pAcc());

    assert(props.size() == NavHpposecef::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavHpposecef::NavHpposecef() = default;
NavHpposecef::~NavHpposecef() = default;

NavHpposecef& NavHpposecef::operator=(const NavHpposecef&) = default;
NavHpposecef& NavHpposecef::operator=(NavHpposecef&&) = default;

const char* NavHpposecef::nameImpl() const
{
    static const char* Str = "NAV-HPPOSECEF";
    return Str;
}

const QVariantList& NavHpposecef::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

