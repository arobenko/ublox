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

using ublox::message::CfgNav5Fields;

QVariantMap createProps_mask()
{
    cc::property::field::ForField<CfgNav5Fields::mask> props;
    props.name("mask")
         .add("dyn")
         .add("minEl")
         .add("posFixMode")
         .add("drLim")
         .add("posMask")
         .add("timeMask")
         .add("staticHoldMask")
         .add("dgpsMask");
    assert(props.bits().size() == CfgNav5Fields::mask_numOfValues);
    return props.asMap();
}

QVariantMap createProps_dynModel()
{
    return
        cc::property::field::ForField<CfgNav5Fields::dynModel>()
            .name("dynModel")
            .add("Portable", (int)CfgNav5Fields::DynModel::Portable)
            .add("Stationary", (int)CfgNav5Fields::DynModel::Stationary)
            .add("Pedestrian", (int)CfgNav5Fields::DynModel::Pedestrian)
            .add("Automotive", (int)CfgNav5Fields::DynModel::Automotive)
            .add("Sea", (int)CfgNav5Fields::DynModel::Sea)
            .add("Airborne <1g Acceleration", (int)CfgNav5Fields::DynModel::Airborne_1g)
            .add("Airborne <2g Acceleration", (int)CfgNav5Fields::DynModel::Airborne_2g)
            .add("Airborne <4g Acceleration", (int)CfgNav5Fields::DynModel::Airborne_4g)
            .asMap();
}

QVariantMap createProps_fixMode()
{
    return
        cc::property::field::ForField<CfgNav5Fields::fixMode>()
            .name("fixMode")
            .add("2D Only", (int)CfgNav5Fields::FixMode::Only_2D)
            .add("3D Only", (int)CfgNav5Fields::FixMode::Only_3D)
            .add("Auto 2D/3D", (int)CfgNav5Fields::FixMode::Auto)
            .asMap();
}

QVariantMap createProps_fixedAlt()
{
    return
        cc::property::field::ForField<CfgNav5Fields::fixedAlt>()
            .name("fixedAlt")
            .scaledDecimals(2)
            .asMap();
}

QVariantMap createProps_fixedAltVar()
{
    return
        cc::property::field::ForField<CfgNav5Fields::fixedAltVar>()
            .name("fixedAltVar")
            .scaledDecimals(4)
            .asMap();
}

QVariantMap createProps_xDOP(char prefix)
{
    return
        cc::property::field::ForField<CfgNav5Fields::pDOP>()
            .name(QString("%1DOP").arg(prefix))
            .scaledDecimals(1)
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_mask());
    props.append(createProps_dynModel());
    props.append(createProps_fixMode());
    props.append(createProps_fixedAlt());
    props.append(createProps_fixedAltVar());
    props.append(
        cc::property::field::ForField<CfgNav5Fields::minElev>().name("minElev").asMap());
    props.append(
        cc::property::field::ForField<CfgNav5Fields::drLimit>().name("drLimit").asMap());
    props.append(createProps_xDOP('p'));
    props.append(createProps_xDOP('t'));
    props.append(
        cc::property::field::ForField<CfgNav5Fields::pAcc>().name("pAcc").asMap());
    props.append(
        cc::property::field::ForField<CfgNav5Fields::tAcc>().name("tAcc").asMap());
    props.append(
        cc::property::field::ForField<CfgNav5Fields::staticHoldThreash>().name("staticHoldThresh").asMap());
    props.append(
        cc::property::field::ForField<CfgNav5Fields::dgpsTimeOut>().name("dgpsTimeOut").asMap());
    props.append(
        cc::property::field::ForField<CfgNav5Fields::cnoThreshNumSVs>().name("cnoThreshNumSVs").asMap());
    props.append(
        cc::property::field::ForField<CfgNav5Fields::cnoThresh>().name("cnoThresh").asMap());
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

