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

QVariantMap createProps_mask1()
{
    QVariantList bitNames;

    auto fillBitNamesUntilFunc =
        [&bitNames](int limit)
        {
            while (bitNames.size() < limit) {
                bitNames.append(QVariant());
            }
        };

    fillBitNamesUntilFunc(ublox::message::CfgNavx5Fields::mask1_minMax);
    bitNames.append("minMax");
    bitNames.append("minCno");
    fillBitNamesUntilFunc(ublox::message::CfgNavx5Fields::mask1_initial3dfix);
    bitNames.append("initial3dfix");
    fillBitNamesUntilFunc(ublox::message::CfgNavx5Fields::mask1_wknRoll);
    bitNames.append("wknRoll");
    fillBitNamesUntilFunc(ublox::message::CfgNavx5Fields::mask1_ppp);
    bitNames.append("ppp");
    bitNames.append("aop");
    assert(bitNames.size() == ublox::message::CfgNavx5Fields::mask1_numOfValues);
    return cc::Property::createPropertiesMap("mask1", std::move(bitNames));
}

QVariantMap createProps_boolVal(const char* name)
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "false");
    cc::Property::appendEnumValue(enumValues, "true");
    assert(enumValues.size() == (int)ublox::message::CfgNavx5Fields::BoolVal::NumOfValues);
    return cc::Property::createPropertiesMap(name, std::move(enumValues));
}

QVariantMap createProps_aopCfg()
{
    QVariantList bitNames;
    bitNames.append("useAOP");
    assert(bitNames.size() == ublox::message::CfgNavx5Fields::aopCfg_numOfValues);
    return cc::Property::createPropertiesMap("aopCfg", std::move(bitNames));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::Property::createPropertiesMap("version"));
    props.append(createProps_mask1());
    props.append(cc_plugin::field::common::props_reserved(0));
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(cc::Property::createPropertiesMap("minSVs"));
    props.append(cc::Property::createPropertiesMap("maxSVs"));
    props.append(cc::Property::createPropertiesMap("minCNO"));
    props.append(cc_plugin::field::common::props_reserved(5));
    props.append(createProps_boolVal("iniFix3D"));
    props.append(cc_plugin::field::common::props_reserved(6));
    props.append(cc_plugin::field::common::props_reserved(7));
    props.append(cc_plugin::field::common::props_reserved(8));
    props.append(cc::Property::createPropertiesMap("wknRollover"));
    props.append(cc_plugin::field::common::props_reserved(9));
    props.append(cc_plugin::field::common::props_reserved(10));
    props.append(cc_plugin::field::common::props_reserved(11));
    props.append(createProps_boolVal("usePPP"));
    props.append(createProps_aopCfg());
    props.append(cc_plugin::field::common::props_reserved(12));
    props.append(cc_plugin::field::common::props_reserved(13));
    props.append(cc::Property::createPropertiesMap("aopOrbMaxErr"));
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

