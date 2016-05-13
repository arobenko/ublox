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

#include "MonHw.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MonHw<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MonHw<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MonHw>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MonHwFields;

QVariantMap createProps_aStatus()
{
    cc::property::field::ForField<MonHwFields::aStatus> props;
    props.name("aStatus")
         .add("INIT")
         .add("DONTKNOW")
         .add("OK")
         .add("SHORT")
         .add("OPEN");
    assert(props.values().size() == (int)MonHwFields::AStatus::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_aPower()
{
    cc::property::field::ForField<MonHwFields::aPower> props;
    props.name("aPower")
         .add("OFF")
         .add("ON")
         .add("DONTKNOW");
    assert(props.values().size() == (int)MonHwFields::APower::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_flags()
{
    cc::property::field::ForField<MonHwFields::rtcCalib> rtcCalibProps;
    rtcCalibProps.name("flags")
                 .add("rtcCalib")
                 .serialisedHidden();
    assert(rtcCalibProps.bits().size() == MonHwFields::rtcCalib_numOfValues);

    cc::property::field::ForField<MonHwFields::safeBoot> safeBootProps;
    safeBootProps.name("safeBoot")
                 .add("Inactive")
                 .add("Active")
                 .serialisedHidden();
    assert(safeBootProps.values().size() == (int)MonHwFields::SafeBoot::NumOfValues);

    cc::property::field::ForField<MonHwFields::jammingState> jammingStateProps;
    jammingStateProps.name("jammingState")
                     .add("unknown")
                     .add("ok")
                     .add("warning")
                     .add("critical")
                     .serialisedHidden();
    assert(jammingStateProps.values().size() == (int)MonHwFields::JammingState::NumOfValues);

    cc::property::field::IntValue reservedProps;
    reservedProps.hidden();

    cc::property::field::ForField<MonHwFields::flags> props;
    props.add(rtcCalibProps.asMap())
         .add(safeBootProps.asMap())
         .add(jammingStateProps.asMap())
         .add(reservedProps.asMap());
    assert(props.members().size() == MonHwFields::flags_numOfValues);
    return props.asMap();
}

QVariantMap createProps_VP()
{
    cc::property::field::ForField<MonHwFields::VP> props;
    props.name("VP").serialisedHidden();

    for (auto idx = 0U; idx < MonHwFields::VP::ParsedOptions::SequenceFixedSize; ++idx) {
        props.add(cc::property::field::IntValue().name(QString("%1").arg(idx)).asMap());
    }

    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MonHwFields::pinSel>().name("pinSel").asMap());
    props.append(
        cc::property::field::ForField<MonHwFields::pinBank>().name("pinBank").asMap());
    props.append(
        cc::property::field::ForField<MonHwFields::pinDir>().name("pinDir").asMap());
    props.append(
        cc::property::field::ForField<MonHwFields::pinVal>().name("pinVal").asMap());
    props.append(
        cc::property::field::ForField<MonHwFields::noisePerMS>().name("noisePerMS").asMap());
    props.append(
        cc::property::field::ForField<MonHwFields::agcCnt>().name("agcCnt").asMap());
    props.append(createProps_aStatus());
    props.append(createProps_aPower());
    props.append(createProps_flags());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MonHwFields::usedMask>().name("usedMask").asMap());
    props.append(createProps_VP());
    props.append(
        cc::property::field::ForField<MonHwFields::jamInd>().name("jamInd").asMap());
    props.append(cc_plugin::field::common::props_reserved(3));
    props.append(
        cc::property::field::ForField<MonHwFields::pinIrq>().name("pinIrq").asMap());
    props.append(
        cc::property::field::ForField<MonHwFields::pullH>().name("pullH").asMap());
    props.append(
        cc::property::field::ForField<MonHwFields::pullL>().name("pullL").asMap());
    assert(props.size() == MonHw::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MonHw::MonHw() = default;
MonHw::~MonHw() = default;

MonHw& MonHw::operator=(const MonHw&) = default;
MonHw& MonHw::operator=(MonHw&&) = default;

const char* MonHw::nameImpl() const
{
    static const char* Str = "MON-HW";
    return Str;
}

const QVariantList& MonHw::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

