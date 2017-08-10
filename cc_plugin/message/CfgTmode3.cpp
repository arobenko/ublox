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

#include "CfgTmode3.h"

#include "cc_plugin/field/common.h"
#include "cc_plugin/field/cfg.h"

template class ublox::message::CfgTmode3<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgTmode3<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgTmode3>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgTmode3Fields;

QVariantMap createProps_flags()
{
    using Field = CfgTmode3Fields::flags;
    cc::property::field::ForField<Field> props;
    props.name("flags")
         .add("lla");
    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_cartesian(const char* coord)
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
    props.append(
        cc::property::field::ForField<CfgTmode3Fields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc_plugin::field::cfg::props_timeMode());
    props.append(createProps_flags());
    props.append(createProps_cartesian("X"));
    props.append(createProps_geodetic("lat", 7));
    props.append(createProps_cartesian("Y"));
    props.append(createProps_geodetic("lon", 7));
    props.append(createProps_cartesian("Z"));
    props.append(createProps_geodetic("alt"));
    props.append(createProps_cartesian("XHP"));
    props.append(createProps_geodetic("latHP", 9));
    props.append(createProps_cartesian("YHP"));
    props.append(createProps_geodetic("lonHP", 9));
    props.append(createProps_cartesian("ZHP"));
    props.append(createProps_geodetic("altHP"));
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(
        cc::property::field::ForField<CfgTmode3Fields::fixedPosAcc>().name("fixedPosAcc").asMap());
    props.append(
        cc::property::field::ForField<CfgTmode3Fields::svinMinDur>().name("svinMinDur").asMap());
    props.append(
        cc::property::field::ForField<CfgTmode3Fields::svinAccLimit>().name("svinAccLimit").asMap());
    props.append(cc_plugin::field::common::props_reserved(3));
    props.append(cc_plugin::field::common::props_reserved(4));
    assert(props.size() == CfgTmode3::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgTmode3::CfgTmode3() = default;
CfgTmode3::~CfgTmode3() = default;

CfgTmode3& CfgTmode3::operator=(const CfgTmode3&) = default;
CfgTmode3& CfgTmode3::operator=(CfgTmode3&&) = default;


const char* CfgTmode3::nameImpl() const
{
    static const char* Str = "CFG-TMODE3";
    return Str;
}

const QVariantList& CfgTmode3::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

