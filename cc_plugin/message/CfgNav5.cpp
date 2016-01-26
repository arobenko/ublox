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

#include "CfgNav5.h"

#include <cassert>

#include <QtCore/QString>

#include "cc_plugin/field/common.h"

template class ublox::message::CfgNav5<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgNav5<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgNav5>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_mask()
{
    QVariantList bitNames;
    bitNames.append("dyn");
    bitNames.append("minEl");
    bitNames.append("posFixMode");
    bitNames.append("drLim");
    bitNames.append("posMask");
    bitNames.append("timeMask");
    bitNames.append("staticHoldMask");
    bitNames.append("dgpsMask");
    assert(bitNames.size() == ublox::message::CfgNav5Fields::mask_numOfValues);
    return cc::Property::createPropertiesMap("mask", std::move(bitNames));
}

QVariantMap createProps_dynModel()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "Portable", (int)ublox::message::CfgNav5Fields::DynModel::Portable);
    cc::Property::appendEnumValue(enumValues, "Stationary", (int)ublox::message::CfgNav5Fields::DynModel::Stationary);
    cc::Property::appendEnumValue(enumValues, "Pedestrian", (int)ublox::message::CfgNav5Fields::DynModel::Pedestrian);
    cc::Property::appendEnumValue(enumValues, "Automotive", (int)ublox::message::CfgNav5Fields::DynModel::Automotive);
    cc::Property::appendEnumValue(enumValues, "Sea", (int)ublox::message::CfgNav5Fields::DynModel::Sea);
    cc::Property::appendEnumValue(enumValues, "Airborne <1g Acceleration", (int)ublox::message::CfgNav5Fields::DynModel::Airborne_1g);
    cc::Property::appendEnumValue(enumValues, "Airborne <2g Acceleration", (int)ublox::message::CfgNav5Fields::DynModel::Airborne_2g);
    cc::Property::appendEnumValue(enumValues, "Airborne <4g Acceleration", (int)ublox::message::CfgNav5Fields::DynModel::Airborne_4g);
    return cc::Property::createPropertiesMap("dynModel", std::move(enumValues));
}

QVariantMap createProps_fixMode()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "2D Only", (int)ublox::message::CfgNav5Fields::FixMode::Only_2D);
    cc::Property::appendEnumValue(enumValues, "3D Only", (int)ublox::message::CfgNav5Fields::FixMode::Only_3D);
    cc::Property::appendEnumValue(enumValues, "Auto 2D/3D", (int)ublox::message::CfgNav5Fields::FixMode::Auto);
    return cc::Property::createPropertiesMap("fixMode", std::move(enumValues));
}

QVariantMap createProps_fixedAlt()
{
    auto props = cc::Property::createPropertiesMap("fixedAlt");
    cc::Property::setDisplayScaled(props);
    cc::Property::setFloatDecimals(props, 2);
    return props;
}

QVariantMap createProps_fixedAltVar()
{
    auto props = cc::Property::createPropertiesMap("fixedAltVar");
    cc::Property::setDisplayScaled(props);
    cc::Property::setFloatDecimals(props, 4);
    return props;
}

QVariantMap createProps_xDOP(char prefix)
{
    auto props = cc::Property::createPropertiesMap(QString("%1DOP").arg(prefix));
    cc::Property::setDisplayScaled(props);
    cc::Property::setFloatDecimals(props, 1);
    return props;
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_mask());
    props.append(createProps_dynModel());
    props.append(createProps_fixMode());
    props.append(createProps_fixedAlt());
    props.append(createProps_fixedAltVar());
    props.append(cc::Property::createPropertiesMap("minElev"));
    props.append(cc::Property::createPropertiesMap("drLimit"));
    props.append(createProps_xDOP('p'));
    props.append(createProps_xDOP('t'));
    props.append(cc::Property::createPropertiesMap("pAcc"));
    props.append(cc::Property::createPropertiesMap("tAcc"));
    props.append(cc::Property::createPropertiesMap("staticHoldThresh"));
    props.append(cc::Property::createPropertiesMap("dgpsTimeout"));
    props.append(cc::Property::createPropertiesMap("cnoThreshNumSVs"));
    props.append(cc::Property::createPropertiesMap("cnoThresh"));
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(cc_plugin::field::common::props_reserved(3));
    props.append(cc_plugin::field::common::props_reserved(4));
    assert(props.size() == CfgNav5::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgNav5::CfgNav5() = default;
CfgNav5::~CfgNav5() = default;

CfgNav5& CfgNav5::operator=(const CfgNav5&) = default;
CfgNav5& CfgNav5::operator=(CfgNav5&&) = default;


const char* CfgNav5::nameImpl() const
{
    static const char* Str = "CFG-NAV5";
    return Str;
}

const QVariantList& CfgNav5::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

