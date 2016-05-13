//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
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

#include "CfgNavx5.h"

#include "cc_plugin/field/common.h"

template class ublox::message::CfgNavx5<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgNavx5<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgNavx5>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgNavx5Fields;

QVariantMap createProps_mask1()
{
    cc::property::field::ForField<CfgNavx5Fields::mask1> props;
    props.name("mask1")
         .add(CfgNavx5Fields::mask1_minMax, "manMax")
         .add(CfgNavx5Fields::mask1_minCno, "minCno")
         .add(CfgNavx5Fields::mask1_initial3dfix, "initial3dfix")
         .add(CfgNavx5Fields::mask1_wknRoll, "wknRoll")
         .add(CfgNavx5Fields::mask1_ppp, "ppp")
         .add(CfgNavx5Fields::mask1_aop, "aop");

    assert(props.bits().size() == CfgNavx5Fields::mask1_numOfValues);
    return props.asMap();
}

QVariantMap createProps_boolVal(const char* name)
{
    cc::property::field::EnumValue props;
    props.name(name)
         .add("false")
         .add("true");
    assert(props.values().size() == (int)CfgNavx5Fields::BoolVal::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_aopCfg()
{
    cc::property::field::ForField<CfgNavx5Fields::aopCfg> props;
    props.name("aopCfg")
         .add("useAOP");
    assert(props.bits().size() == CfgNavx5Fields::aopCfg_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<CfgNavx5Fields::version>().name("version").asMap());
    props.append(createProps_mask1());
    props.append(cc_plugin::field::common::props_reserved(0));
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(
        cc::property::field::ForField<CfgNavx5Fields::minSVs>().name("minSVs").asMap());
    props.append(
        cc::property::field::ForField<CfgNavx5Fields::maxSVs>().name("maxSVs").asMap());
    props.append(
        cc::property::field::ForField<CfgNavx5Fields::minCNO>().name("minCNO").asMap());
    props.append(cc_plugin::field::common::props_reserved(5));
    props.append(createProps_boolVal("iniFix3D"));
    props.append(cc_plugin::field::common::props_reserved(6));
    props.append(cc_plugin::field::common::props_reserved(7));
    props.append(cc_plugin::field::common::props_reserved(8));
    props.append(
        cc::property::field::ForField<CfgNavx5Fields::wknRollover>().name("wknRollover").asMap());
    props.append(cc_plugin::field::common::props_reserved(9));
    props.append(cc_plugin::field::common::props_reserved(10));
    props.append(cc_plugin::field::common::props_reserved(11));
    props.append(createProps_boolVal("usePPP"));
    props.append(createProps_aopCfg());
    props.append(cc_plugin::field::common::props_reserved(12));
    props.append(cc_plugin::field::common::props_reserved(13));
    props.append(
        cc::property::field::ForField<CfgNavx5Fields::aopOrbMaxErr>().name("aopOrbMaxErr").asMap());
    props.append(cc_plugin::field::common::props_reserved(14));
    props.append(cc_plugin::field::common::props_reserved(15));
    props.append(cc_plugin::field::common::props_reserved(3));
    props.append(cc_plugin::field::common::props_reserved(4));
    assert(props.size() == CfgNavx5::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgNavx5::CfgNavx5() = default;
CfgNavx5::~CfgNavx5() = default;

CfgNavx5& CfgNavx5::operator=(const CfgNavx5&) = default;
CfgNavx5& CfgNavx5::operator=(CfgNavx5&&) = default;


const char* CfgNavx5::nameImpl() const
{
    static const char* Str = "CFG-NAVX5";
    return Str;
}

const QVariantList& CfgNavx5::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

