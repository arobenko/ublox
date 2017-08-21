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

#include "NavSvin.h"
#include "cc_plugin/field/common.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavSvin<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavSvin<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavSvin>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::NavSvinFields;

QVariantMap createProps_hp(char ch)
{
    auto props =
        cc::property::field::ForField<NavSvinFields::meanXHP>()
            .name(QString("mean%1HP").arg(ch))
            .scaledDecimals(1);
    return props.asMap();
}

QVariantMap createProps_meanAcc()
{
    auto props =
        cc::property::field::ForField<NavSvinFields::meanAcc>()
            .name("meanAcc")
            .scaledDecimals(1);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<NavSvinFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(
        cc::property::field::ForField<NavSvinFields::dur>().name("dur").asMap());
    props.append(
        cc::property::field::ForField<NavSvinFields::meanX>().name("meanX").asMap());
    props.append(
        cc::property::field::ForField<NavSvinFields::meanY>().name("meanY").asMap());
    props.append(
        cc::property::field::ForField<NavSvinFields::meanZ>().name("meanZ").asMap());
    props.append(createProps_hp('X'));
    props.append(createProps_hp('Y'));
    props.append(createProps_hp('Z'));
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(createProps_meanAcc());
    props.append(
        cc::property::field::ForField<NavSvinFields::obs>().name("obs").asMap());
    props.append(
        cc::property::field::ForField<NavSvinFields::isValid>().name("valid").asMap());
    props.append(
        cc::property::field::ForField<NavSvinFields::active>().name("active").asMap());
    props.append(cc_plugin::field::common::props_reserved(3));

    assert(props.size() == NavSvin::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavSvin::NavSvin() = default;
NavSvin::~NavSvin() = default;

NavSvin& NavSvin::operator=(const NavSvin&) = default;
NavSvin& NavSvin::operator=(NavSvin&&) = default;

const char* NavSvin::nameImpl() const
{
    static const char* Str = "NAV-SVIN";
    return Str;
}

const QVariantList& NavSvin::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

