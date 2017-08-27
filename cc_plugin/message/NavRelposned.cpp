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

#include "NavRelposned.h"
#include "cc_plugin/field/common.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavRelposned<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavRelposned<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavRelposned>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::NavRelposnedFields;

QVariantMap createProps_hp(char ch)
{
    auto props =
        cc::property::field::ForField<NavRelposnedFields::relPosHPN>()
            .name(QString("relPosHP%1").arg(ch))
            .scaledDecimals(1);
    return props.asMap();
}

QVariantMap createProps_acc(char ch)
{
    auto props =
        cc::property::field::ForField<NavRelposnedFields::accN>()
            .name(QString("acc%1").arg(ch))
            .scaledDecimals(1);
    return props.asMap();
}

QVariantMap createProps_flagsLow()
{
    using Field = NavRelposnedFields::flagsLow;
    auto props =
        cc::property::field::ForField<Field>()
            .name("flags")
            .serialisedHidden()
            .add("gnssFixOK")
            .add("diffSoln")
            .add("relPosValid");
    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_flagsHigh()
{
    using Field = NavRelposnedFields::flagsHigh;
    auto props =
        cc::property::field::ForField<Field>()
            .serialisedHidden()
            .add("isMoving")
            .add("refPosMiss")
            .add("refObsMiss");
    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}


QVariantMap createProps_flags()
{
    using Field = NavRelposnedFields::flags;
    auto props =
        cc::property::field::ForField<Field>()
            .add(createProps_flagsLow())
            .add(cc_plugin::field::nav::createProps_carrSoln())
            .add(createProps_flagsHigh());
    assert(props.members().size() == Field::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<NavRelposnedFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<NavRelposnedFields::refStationId>().name("refStationId").asMap());
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(
        cc::property::field::ForField<NavRelposnedFields::relPosN>().name("relPosN").asMap());
    props.append(
        cc::property::field::ForField<NavRelposnedFields::relPosE>().name("relPosE").asMap());
    props.append(
        cc::property::field::ForField<NavRelposnedFields::relPosD>().name("relPosD").asMap());
    props.append(createProps_hp('N'));
    props.append(createProps_hp('E'));
    props.append(createProps_hp('D'));
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(createProps_acc('N'));
    props.append(createProps_acc('E'));
    props.append(createProps_acc('D'));
    props.append(createProps_flags());

    assert(props.size() == NavRelposned::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavRelposned::NavRelposned() = default;
NavRelposned::~NavRelposned() = default;

NavRelposned& NavRelposned::operator=(const NavRelposned&) = default;
NavRelposned& NavRelposned::operator=(NavRelposned&&) = default;

const char* NavRelposned::nameImpl() const
{
    static const char* Str = "NAV-RELPOSNED";
    return Str;
}

const QVariantList& NavRelposned::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

