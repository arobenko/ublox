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

#include "cfg.h"

CC_DISABLE_WARNINGS()
#include <QtCore/QString>
#include <QtCore/QVariantList>
CC_ENABLE_WARNINGS()

#include "comms_champion/comms_champion.h"
#include "ublox/field/cfg.h"
#include "ublox/message/CfgPrt.h"
#include "ublox/message/CfgInf.h"
#include "ublox/message/CfgNmea.h"

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace field
{

namespace cfg
{

namespace
{

cc::property::field::EnumValue createPropsInternal_portID()
{
    return cc::property::field::EnumValue()
        .name("portID")
        .add("DDC", (int)ublox::message::CfgPrtFields::PortId::DDC)
        .add("UART", (int)ublox::message::CfgPrtFields::PortId::UART)
        .add("UART2", (int)ublox::message::CfgPrtFields::PortId::UART2)
        .add("USB", (int)ublox::message::CfgPrtFields::PortId::USB)
        .add("SPI", (int)ublox::message::CfgPrtFields::PortId::SPI);
}

QVariantMap createProps_portID()
{
    return createPropsInternal_portID().asMap();
}

QVariantMap createProps_readOnlyPortID()
{
    return createPropsInternal_portID().readOnly().asMap();
}

QVariantMap createProps_txReady()
{
    auto enProps =
        cc::property::field::ForField<ublox::message::CfgPrtFields::en>()
            .name("txReady")
            .add("en")
            .serialisedHidden();
    assert(enProps.bits().size() == ublox::message::CfgPrtFields::en::BitIdx_numOfValues);

    auto polProps =
        cc::property::field::ForField<ublox::message::CfgPrtFields::pol>()
            .name("pol")
            .add("High-active")
            .add("Low-active")
            .serialisedHidden();
    assert(polProps.values().size() == (int)ublox::message::CfgPrtFields::Polarity::NumOfValues);

    auto pinProps =
        cc::property::field::ForField<ublox::message::CfgPrtFields::pin>()
            .name("pin")
            .serialisedHidden();

    auto thresProps =
        cc::property::field::ForField<ublox::message::CfgPrtFields::thres>()
            .name("thres")
            .serialisedHidden();

    auto txReadyProps =
        cc::property::field::ForField<ublox::message::CfgPrtFields::txReady>()
            .name("txReady")
            .add(enProps.asMap())
            .add(polProps.asMap())
            .add(pinProps.asMap())
            .add(thresProps.asMap());

    assert(txReadyProps.members().size() == ublox::message::CfgPrtFields::txReady::FieldIdx_numOfValues);
    return txReadyProps.asMap();
}

QVariantMap createProps_inProtoMask()
{
    cc::property::field::ForField<ublox::message::CfgPrtFields::inProtoMask> props;
    props.name("inProtoMask")
         .add("inUbx")
         .add("inNmea")
         .add("inRtcm");
    assert(props.bits().size() == ublox::message::CfgPrtFields::inProtoMask::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_outProtoMask()
{
    cc::property::field::ForField<ublox::message::CfgPrtFields::outProtoMask> props;
    props.name("outProtoMask")
        .add("outUbx")
        .add("outNmea");
    assert(props.bits().size() == ublox::message::CfgPrtFields::outProtoMask::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_prtFlags()
{
    cc::property::field::ForField<ublox::message::CfgPrtFields::flags> props;
    props.name("flags")
         .add(ublox::message::CfgPrtFields::flags::BitIdx_extendedTxTimeout, "extendedTxTimeout");
    assert(props.bits().size() == ublox::message::CfgPrtFields::flags::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_protocolID()
{
    cc::property::field::ForField<ublox::message::CfgInfFields::protocolID> props;
    props.name("protocolID")
         .add("UBX")
         .add("NMEA");
    assert(props.values().size() == (int)ublox::field::cfg::ProtocolId::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_nmeaFilter()
{
    cc::property::field::ForField<ublox::message::CfgNmeaFields::filter> props;
    props.name("filter")
         .add("posFilt")
         .add("mskPosFilt")
         .add("timeFilt")
         .add("dateFilt")
         .add("gpsOnlyFilter")
         .add("trackFilt");
    assert(props.bits().size() == ublox::message::CfgNmeaFields::filter::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_nmeaVersion()
{
    return
        cc::property::field::ForField<ublox::message::CfgNmeaFields::nmeaVersion>()
            .name("nmeaVersion")
            .add("NMEA version 2.1", (int)ublox::message::CfgNmeaFields::NmeaVersion::v21)
            .add("NMEA version 2.3", (int)ublox::message::CfgNmeaFields::NmeaVersion::v23)
            .asMap();
}

QVariantMap createProps_nmeaFlags()
{
    cc::property::field::ForField<ublox::message::CfgNmeaFields::flags> props;
    props.name("flags")
         .add("compat")
         .add("consider");
    assert(props.bits().size() == ublox::message::CfgNmeaFields::flags::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_tpIdx()
{
    cc::property::field::ForField<ublox::field::cfg::tpIdx> props;
    props.name("tpIdx")
         .add("TIMEPULSE")
         .add("TIMEPULSE2");
    assert(props.values().size() == (int)ublox::field::cfg::TpIdx::NumOfValues);
    return props.asMap();
}


}  // namespace

const QVariantMap& props_portID()
{
    static const auto Props = createProps_portID();
    return Props;
}

const QVariantMap& props_readOnlyPortID()
{
    static const auto Props = createProps_readOnlyPortID();
    return Props;
}

const QVariantMap& props_txReady()
{
    static const auto Props = createProps_txReady();
    return Props;
}

const QVariantMap& props_inProtoMask()
{
    static const auto Props = createProps_inProtoMask();
    return Props;
}

const QVariantMap& props_outProtoMask()
{
    static const auto Props = createProps_outProtoMask();
    return Props;
}

const QVariantMap& props_prtFlags()
{
    static const auto Props = createProps_prtFlags();
    return Props;
}

const QVariantMap& props_protocolID()
{
    static const auto Props = createProps_protocolID();
    return Props;
}

const QVariantMap& props_datumNum()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::cfg::datumNum>()
            .name("datumNum")
            .asMap();
    return Props;
}

const QVariantMap& props_datumName()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::cfg::datumName<> >()
            .name("datumName")
            .asMap();
    return Props;
}

const QVariantMap& props_datMajA()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::cfg::datMajA>()
            .name("majA")
            .asMap();
    return Props;
}

const QVariantMap& props_datFlat()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::cfg::datFlat>()
            .name("flat")
            .asMap();
    return Props;
}

const QVariantMap& props_datDX()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::cfg::datDX>()
            .name("dX")
            .asMap();
    return Props;
}

const QVariantMap& props_datDY()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::cfg::datDY>()
            .name("dY")
            .asMap();
    return Props;
}

const QVariantMap& props_datDZ()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::cfg::datDZ>()
            .name("dZ")
            .asMap();
    return Props;
}

const QVariantMap& props_datRotX()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::cfg::datRotX>()
            .name("rotX")
            .asMap();
    return Props;
}

const QVariantMap& props_datRotY()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::cfg::datRotY>()
            .name("rotY")
            .asMap();
    return Props;
}

const QVariantMap& props_datRotZ()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::cfg::datRotZ>()
            .name("rotZ")
            .asMap();
    return Props;
}

const QVariantMap& props_datScale()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::field::cfg::datScale>()
            .name("scale")
            .asMap();
    return Props;
}

const QVariantMap& props_nmeaFilter()
{
    static const QVariantMap Props = createProps_nmeaFilter();
    return Props;
}

const QVariantMap& props_nmeaVersion()
{
    static const QVariantMap Props = createProps_nmeaVersion();
    return Props;
}

const QVariantMap& props_nmeaNumSV()
{
    static const QVariantMap Props =
        cc::property::field::ForField<ublox::message::CfgNmeaFields::numSV>()
            .name("numSV")
            .asMap();
    return Props;
}

const QVariantMap& props_nmeaFlags()
{
    static const QVariantMap Props = createProps_nmeaFlags();
    return Props;
}

const QVariantMap& props_tpIdx()
{
    static const QVariantMap Props = createProps_tpIdx();
    return Props;
}

}  // namespace cfg

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox


