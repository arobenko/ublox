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

#include "HnrPvt.h"
#include "cc_plugin/field/common.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::HnrPvt<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::HnrPvt<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::HnrPvt>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::HnrPvtFields;

QVariantMap createProps_valid()
{
    cc::property::field::ForField<HnrPvtFields::validBits> props;
    props.name("valid")
         .add("validDate")
         .add("validTime")
         .add("fullyResolved");

    assert(props.bits().size() == HnrPvtFields::validBits::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_flags()
{
    using Field = HnrPvtFields::flags;
    auto props =
        cc::property::field::ForField<Field>()
            .name("flags")
            .add("gnssFixOK")
            .add("diffSoln")
            .add("WKNSET")
            .add("TOWSET")
            .add("headVehValid");

    assert(props.bits().size() == Field::BitIdx_numOfValues);
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
    props.append(cc_plugin::field::nav::props_nano());
    props.append(cc_plugin::field::nav::props_gpsFix());
    props.append(createProps_flags());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc_plugin::field::nav::props_lon());
    props.append(cc_plugin::field::nav::props_lat());
    props.append(cc_plugin::field::nav::props_height());
    props.append(cc_plugin::field::nav::props_hMSL());
    props.append(cc_plugin::field::nav::props_gSpeed());
    props.append(
        cc::property::field::ForField<HnrPvtFields::speed>().name("speed").asMap());
    props.append(createProps_heading("headMot"));
    props.append(createProps_heading("headVeh"));
    props.append(cc_plugin::field::nav::props_hAcc());
    props.append(cc_plugin::field::nav::props_vAcc());
    props.append(cc_plugin::field::nav::props_sAcc());
    props.append(createProps_heading("headAcc"));
    props.append(cc_plugin::field::common::props_reserved(2));

    assert(props.size() == HnrPvt::FieldIdx_numOfValues);
    return props;
}

}  // namespace

HnrPvt::HnrPvt() = default;
HnrPvt::~HnrPvt() = default;

HnrPvt& HnrPvt::operator=(const HnrPvt&) = default;
HnrPvt& HnrPvt::operator=(HnrPvt&&) = default;

const char* HnrPvt::nameImpl() const
{
    static const char* Str = "HNR-PVT";
    return Str;
}

const QVariantList& HnrPvt::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

