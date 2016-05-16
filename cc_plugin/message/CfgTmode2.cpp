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

#include <cassert>

#include "CfgTmode2.h"

#include "cc_plugin/field/common.h"

template class ublox::message::CfgTmode2<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgTmode2<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgTmode2>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgTmode2Fields;

QVariantMap createProps_timeMode()
{
    cc::property::field::ForField<CfgTmode2Fields::timeMode> props;
    props.name("timeMode")
         .add("Disabled")
         .add("Survey In")
         .add("Fixed Mode");
    assert(props.values().size() == (int)CfgTmode2Fields::TimeMode::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_flags()
{
    cc::property::field::ForField<CfgTmode2Fields::flags> props;
    props.name("flags")
         .add("lla")
         .add("altInv");
    assert(props.bits().size() == CfgTmode2Fields::flags_numOfValues);
    return props.asMap();
}

QVariantMap createProps_cartesian(char coord)
{
    auto name = QString("ecef%1").arg(coord);
    cc::property::field::IntValue coordProps;
    coordProps.name(name);

    return
        cc::property::field::Optional()
            .name(name)
            .field(coordProps.asMap())
            .uncheckable()
            .asMap();
}

QVariantMap createProps_geodetic(const char* name, int scaledDigits = 0)
{
    cc::property::field::IntValue coordProps;
    coordProps.name(name);
    if (0 < scaledDigits) {
        coordProps.scaledDecimals(scaledDigits);
    }

    return
        cc::property::field::Optional()
            .name(name)
            .field(coordProps.asMap())
            .uncheckable()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_timeMode());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_flags());
    props.append(createProps_cartesian('X'));
    props.append(createProps_geodetic("lat", 7));
    props.append(createProps_cartesian('Y'));
    props.append(createProps_geodetic("lon", 7));
    props.append(createProps_cartesian('Z'));
    props.append(createProps_geodetic("alt"));
    props.append(
        cc::property::field::ForField<CfgTmode2Fields::fixedPosAcc>().name("fixedPosAcc").asMap());
    props.append(
        cc::property::field::ForField<CfgTmode2Fields::svinMinDur>().name("svinMinDur").asMap());
    props.append(
        cc::property::field::ForField<CfgTmode2Fields::svinAccLimit>().name("svinAccLimit").asMap());

    assert(props.size() == CfgTmode2::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgTmode2::CfgTmode2() = default;
CfgTmode2::~CfgTmode2() = default;

CfgTmode2& CfgTmode2::operator=(const CfgTmode2&) = default;
CfgTmode2& CfgTmode2::operator=(CfgTmode2&&) = default;


const char* CfgTmode2::nameImpl() const
{
    static const char* Str = "CFG-TMODE2";
    return Str;
}

const QVariantList& CfgTmode2::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

