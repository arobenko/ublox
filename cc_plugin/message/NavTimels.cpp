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

#include "NavTimels.h"
#include "cc_plugin/field/common.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavTimels<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavTimels<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavTimels>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::NavTimelsFields;
QVariantMap createProps_srcOfCurrLs()
{
    typedef NavTimelsFields::srcOfCurrLs Field;
    return
        cc::property::field::ForField<Field>()
            .name("srcOfCurrLs")
            .add("Default")
            .add("Derived")
            .add("GPS")
            .add("SBAS")
            .add("BeiDou")
            .add("Galileo")
            .add("Aided data")
            .add("Configured")
            .add("Unknown", (int)Field::ValueType::Unknown)
            .asMap();
}

QVariantMap createProps_srcOfLsChange()
{
    typedef NavTimelsFields::srcOfLsChange Field;
    auto props =
        cc::property::field::ForField<Field>()
            .name("srcOfLsChange")
            .add("No source")
            .add("GPS")
            .add("SBAS")
            .add("BeiDou")
            .add("Galileo")
            .add("GLONASS")
        ;

    assert(props.values().size() == (int)Field::ValueType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_valid()
{
    typedef NavTimelsFields::validBits Field;
    auto props =
        cc::property::field::ForField<Field>()
            .name("valid")
            .add("validCurrLs")
            .add("validTimeToLsEvent");

    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(
        cc::property::field::ForField<NavTimelsFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_srcOfCurrLs());
    props.append(
        cc::property::field::ForField<NavTimelsFields::currLs>().name("currLs").asMap());
    props.append(createProps_srcOfLsChange());
    props.append(
        cc::property::field::ForField<NavTimelsFields::lsChange>().name("lsChange").asMap());
    props.append(
        cc::property::field::ForField<NavTimelsFields::timeToLsEvent>().name("timeToLsEvent").asMap());
    props.append(
        cc::property::field::ForField<NavTimelsFields::dateOfLsGpsWn>().name("dateOfLsGpsWn").asMap());
    props.append(
        cc::property::field::ForField<NavTimelsFields::dateOfLsGpsDn>().name("dateOfLsGpsDn").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(createProps_valid());

    assert(props.size() == NavTimels::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavTimels::NavTimels() = default;
NavTimels::~NavTimels() = default;

NavTimels& NavTimels::operator=(const NavTimels&) = default;
NavTimels& NavTimels::operator=(NavTimels&&) = default;


const char* NavTimels::nameImpl() const
{
    static const char* Str = "NAV-TIMELS";
    return Str;
}

const QVariantList& NavTimels::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

