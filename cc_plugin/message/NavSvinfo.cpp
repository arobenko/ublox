//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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

#include "NavSvinfo.h"

#include <cassert>

#include "cc_plugin/field/nav.h"
#include "cc_plugin/field/common.h"

template class ublox::message::NavSvinfo<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavSvinfo<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavSvinfo>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::NavSvinfoFields;

QVariantMap createProps_chn()
{
    return
        cc::property::field::ForField<NavSvinfoFields::chn>()
            .name("chn")
            .asMap();
}

QVariantMap createProps_globalFlags()
{
    cc::property::field::ForField<NavSvinfoFields::chipGen> chipGenProps;
    chipGenProps.name("chipGen")
                .add("Antaris")
                .add("ublox-5")
                .add("ublox-6")
                .serialisedHidden();
    assert(chipGenProps.values().size() == (int)NavSvinfoFields::ChipGen::NumOfValues);

    auto reservedProps =
        cc::property::field::IntValue().name("reserved").hidden();

    cc::property::field::ForField<NavSvinfoFields::globalFlags> props;
    props.name("globalFlags")
         .add(chipGenProps.asMap())
         .add(reservedProps.asMap());
    assert(props.members().size() == NavSvinfoFields::globalFlags_numOfValues);
    return props.asMap();
}

QVariantMap createProps_flags()
{
    cc::property::field::ForField<NavSvinfoFields::flags> props;
    props.name("flags")
         .add("svUsed")
         .add("diffCorr")
         .add("orbitAvail")
         .add("orbitEph")
         .add("unhealthy")
         .add("orbitAlm")
         .add("orbitAop")
         .add("smoothed");
    assert(props.bits().size() == NavSvinfoFields::flags_numOfValues);
    return props.asMap();
}

QVariantMap createProps_quality()
{
    cc::property::field::ForField<NavSvinfoFields::quality> props;
    props.name("quality")
         .add("Idle")
         .add("Searching")
         .add("Signal acquired")
         .add("Signal unusable")
         .add("Code Lock")
         .add("Code and Carrier Locked")
         .add("Code and Carrier Locked")
         .add("Code and Carrier Locked");
    assert(props.values().size() == (int)NavSvinfoFields::QualityInd::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_cno()
{
    return
        cc::property::field::ForField<NavSvinfoFields::cno>()
            .name("cno")
            .asMap();
}

QVariantMap createProps_elev()
{
    return
        cc::property::field::ForField<NavSvinfoFields::elev>()
            .name("elev")
            .asMap();
}

QVariantMap createProps_azim()
{
    return
        cc::property::field::ForField<NavSvinfoFields::azim>()
            .name("azim")
            .asMap();
}

QVariantMap createProps_prRes()
{
    return
        cc::property::field::ForField<NavSvinfoFields::prRes>()
            .name("prRes")
            .asMap();
}

QVariantMap createProps_data()
{
    cc::property::field::ForField<NavSvinfoFields::block> blockProps;
    blockProps.add(createProps_chn())
              .add(cc_plugin::field::nav::props_svid())
              .add(createProps_flags())
              .add(createProps_quality())
              .add(createProps_cno())
              .add(createProps_elev())
              .add(createProps_azim())
              .add(createProps_prRes());
    assert(blockProps.members().size() == NavSvinfoFields::block_numOfValues);

    return
        cc::property::field::ForField<NavSvinfoFields::data>()
            .name("data")
            .add(blockProps.asMap())
            .serialisedHidden()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(cc_plugin::field::nav::props_numCh());
    props.append(createProps_globalFlags());
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(createProps_data());

    assert(props.size() == NavSvinfo::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavSvinfo::NavSvinfo() = default;
NavSvinfo::~NavSvinfo() = default;

NavSvinfo& NavSvinfo::operator=(const NavSvinfo&) = default;
NavSvinfo& NavSvinfo::operator=(NavSvinfo&&) = default;

const char* NavSvinfo::nameImpl() const
{
    static const char* Str = "NAV-SVINFO";
    return Str;
}

const QVariantList& NavSvinfo::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

