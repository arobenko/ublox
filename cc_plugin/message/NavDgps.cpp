//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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

#include "NavDgps.h"
#include "cc_plugin/field/nav.h"
#include "cc_plugin/field/common.h"

template class ublox::message::NavDgps<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavDgps<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavDgps>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::NavDgpsFields;

QVariantMap createProps_status()
{
    cc::property::field::ForField<NavDgpsFields::status> props;
    props.name("status")
         .add("none")
         .add("PR+PRR correction");
    assert(props.values().size() == (int)NavDgpsFields::Status::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_flags()
{
    cc::property::field::ForField<NavDgpsFields::channel> channelProps;
    channelProps.name("channel")
                .serialisedHidden();

    cc::property::field::ForField<NavDgpsFields::flagsBits> flagsBitsProps;
    flagsBitsProps.name("flags")
                  .add("dgpsUsed")
                  .serialisedHidden();
    assert(flagsBitsProps.bits().size() == NavDgpsFields::flagsBits::BitIdx_numOfValues);

    cc::property::field::ForField<NavDgpsFields::flags> props;
    props.name("flags")
         .add(channelProps.asMap())
         .add(flagsBitsProps.asMap());
    assert(props.members().size() == NavDgpsFields::flags::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_ageC()
{
    return
        cc::property::field::ForField<NavDgpsFields::ageC>()
            .name("ageC")
            .asMap();
}

QVariantMap createProps_prc()
{
    return
        cc::property::field::ForField<NavDgpsFields::prc>()
            .name("prc")
            .asMap();
}

QVariantMap createProps_prrc()
{
    return
        cc::property::field::ForField<NavDgpsFields::prrc>()
            .name("prrc")
            .asMap();
}

QVariantMap createProps_data()
{
    cc::property::field::ForField<NavDgpsFields::block> blockProps;
    blockProps.add(cc_plugin::field::nav::props_svid())
              .add(createProps_flags())
              .add(createProps_ageC())
              .add(createProps_prc())
              .add(createProps_prrc());
    assert(blockProps.members().size() == NavDgpsFields::block::FieldIdx_numOfValues);

    return
        cc::property::field::ForField<NavDgpsFields::data<> >()
            .name("data")
            .add(blockProps.asMap())
            .serialisedHidden()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(cc::property::field::ForField<NavDgpsFields::age>().name("age").asMap());
    props.append(cc::property::field::ForField<NavDgpsFields::baseId>().name("baseId").asMap());
    props.append(cc::property::field::ForField<NavDgpsFields::baseHealth>().name("baseHealth").asMap());
    props.append(cc_plugin::field::nav::props_numCh());
    props.append(createProps_status());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_data());

    assert(props.size() == NavDgps::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavDgps::NavDgps() = default;
NavDgps::~NavDgps() = default;

NavDgps& NavDgps::operator=(const NavDgps&) = default;
NavDgps& NavDgps::operator=(NavDgps&&) = default;

const char* NavDgps::nameImpl() const
{
    static const char* Str = "NAV-DGPS";
    return Str;
}

const QVariantList& NavDgps::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

