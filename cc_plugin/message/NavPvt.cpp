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

#include "NavPvt.h"
#include "cc_plugin/field/common.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavPvt<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavPvt<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavPvt>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::NavPvtFields;

QVariantMap createProps_valid()
{
    cc::property::field::ForField<NavPvtFields::validBits> props;
    props.name("valid")
         .add("validDate")
         .add("validTime")
         .add("fullyResolved");

    assert(props.bits().size() == NavPvtFields::validBits::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_flags()
{
    auto flagsLowProps =
        cc::property::field::ForField<NavPvtFields::flagsLow>()
            .name("flags")
            .add("gnssFixOK")
            .add("diffSoln")
            .serialisedHidden();

    assert(flagsLowProps.bits().size() == NavPvtFields::flagsLow::BitIdx_numOfValues);

    auto psmStateProps =
        cc::property::field::ForField<NavPvtFields::psmState>()
            .name("psmState")
            .add("n/a")
            .add("ENABLED")
            .add("ACQUISITION")
            .add("TRACKING")
            .add("POWER OPTIMIZED TRACKING")
            .add("INACTIVE")
            .serialisedHidden();
    assert(psmStateProps.values().size() == (int)NavPvtFields::PsmState::NumOfValues);

    auto flagsHighProps =
        cc::property::field::ForField<NavPvtFields::flagsHigh>()
            .add("headVehValid")
            .serialisedHidden();

    assert(flagsHighProps.bits().size() == NavPvtFields::flagsHigh::BitIdx_numOfValues);


    auto props =
        cc::property::field::ForField<NavPvtFields::flags>()
            .name("flags")
            .add(flagsLowProps.asMap())
            .add(psmStateProps.asMap())
            .add(flagsHighProps.asMap());
    assert(props.members().size() == (int)NavPvtFields::flags::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_flags2()
{
    auto props =
        cc::property::field::ForField<NavPvtFields::flags2>()
            .name("flags2")
            .add(NavPvtFields::flags2::BitIdx_confirmedAvai, "confirmedAvai")
            .add("confirmedDate")
            .add("confirmedTime")
            .serialisedHidden();

    assert(props.bits().size() == NavPvtFields::flags2::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_heading(const QString& name)
{
    return
        cc::property::field::IntValue()
            .name(name)
            .scaledDecimals(5)
            .asMap();
}

QVariantMap createProps_headVeh()
{
    return
        cc::property::field::ForField<NavPvtFields::headVeh>()
            .name("headVeh")
            .field(createProps_heading("headVeh"))
            .asMap();
}

QVariantMap createProps_reserved3()
{
    return
        cc::property::field::ForField<NavPvtFields::reserved3>()
            .name("reserved3")
            .field(cc_plugin::field::common::props_reserved(3))
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(cc_plugin::field::nav::props_year());
    props.append(cc_plugin::field::nav::props_month());
    props.append(cc_plugin::field::nav::props_day());
    props.append(cc_plugin::field::nav::props_hour());
    props.append(cc_plugin::field::nav::props_min());
    props.append(cc_plugin::field::nav::props_sec());
    props.append(createProps_valid());
    props.append(cc_plugin::field::nav::props_tAcc());
    props.append(cc_plugin::field::nav::props_nano());
    props.append(cc_plugin::field::nav::props_fixType());
    props.append(createProps_flags());
    props.append(createProps_flags2());
    props.append(cc_plugin::field::nav::props_numSV());
    props.append(cc_plugin::field::nav::props_lon());
    props.append(cc_plugin::field::nav::props_lat());
    props.append(cc_plugin::field::nav::props_height());
    props.append(cc_plugin::field::nav::props_hMSL());
    props.append(cc_plugin::field::nav::props_hAcc());
    props.append(cc_plugin::field::nav::props_vAcc());
    props.append(cc_plugin::field::nav::props_velN());
    props.append(cc_plugin::field::nav::props_velE());
    props.append(cc_plugin::field::nav::props_velD());
    props.append(cc_plugin::field::nav::props_gSpeed());
    props.append(createProps_heading("headMot"));
    props.append(cc_plugin::field::nav::props_sAcc());
    props.append(createProps_heading("headAcc"));
    props.append(cc_plugin::field::nav::props_pDOP());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(createProps_headVeh());
    props.append(createProps_reserved3());

    assert(props.size() == NavPvt::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavPvt::NavPvt() = default;
NavPvt::~NavPvt() = default;

NavPvt& NavPvt::operator=(const NavPvt&) = default;
NavPvt& NavPvt::operator=(NavPvt&&) = default;

const char* NavPvt::nameImpl() const
{
    static const char* Str = "NAV-PVT";
    return Str;
}

const QVariantList& NavPvt::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

