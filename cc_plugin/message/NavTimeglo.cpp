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

#include "NavTimeglo.h"

#include <cassert>

#include "cc_plugin/field/common.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavTimeglo<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavTimeglo<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavTimeglo>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::NavTimegloFields;

QVariantMap createProps_valid()
{
    cc::property::field::ForField<NavTimegloFields::validBits> props;
    props.name("valid")
         .add("todValid")
         .add("dateValid");
    assert(props.bits().size() == NavTimegloFields::validBits::BitIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(
        cc::property::field::ForField<NavTimegloFields::TOD>().name("TOD").asMap());
    props.append(
        cc::property::field::ForField<NavTimegloFields::fTOD>().name("fTOD").asMap());
    props.append(
        cc::property::field::ForField<NavTimegloFields::Nt>().name("Nt").asMap());
    props.append(
        cc::property::field::ForField<NavTimegloFields::N4>().name("N4").asMap());
    props.append(createProps_valid());
    props.append(cc_plugin::field::nav::props_tAcc());

    assert(props.size() == NavTimeglo::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavTimeglo::NavTimeglo() = default;
NavTimeglo::~NavTimeglo() = default;

NavTimeglo& NavTimeglo::operator=(const NavTimeglo&) = default;
NavTimeglo& NavTimeglo::operator=(NavTimeglo&&) = default;

const char* NavTimeglo::nameImpl() const
{
    static const char* Str = "NAV-TIMEGLO";
    return Str;
}

const QVariantList& NavTimeglo::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

