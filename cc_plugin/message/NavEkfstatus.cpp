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

#include "NavEkfstatus.h"
#include "cc_plugin/field/common.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavEkfstatus<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavEkfstatus<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavEkfstatus>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::NavEkfstatusFields;

QVariantMap createProps_scaledValue(const QString& nameVal, int decimals)
{
    return
        cc::property::field::IntValue()
            .name(nameVal)
            .scaledDecimals(decimals)
            .asMap();
}

QVariantMap createProps_calibStatus_calib(const QString& nameVal)
{
    cc::property::field::EnumValue props;
    props.name(nameVal)
         .add("no calibration")
         .add("calibrating")
         .add("coarse calibration")
         .add("fine calibration")
         .serialisedHidden();
    assert(props.values().size() == (int)NavEkfstatusFields::CalibStatus::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_calibStatus_reserved()
{
    return cc::property::field::IntValue().name("reserved").hidden().asMap();
}

QVariantMap createProps_calibStatus()
{
    cc::property::field::ForField<NavEkfstatusFields::calibStatus> props;
    props.name("calibStatus")
         .add(createProps_calibStatus_calib("calibTacho"))
         .add(createProps_calibStatus_calib("calibGyro"))
         .add(createProps_calibStatus_calib("calibGyroB"))
         .add(createProps_calibStatus_reserved());
    assert(props.members().size() == NavEkfstatusFields::calibStatus_numOfValues);
    return props.asMap();
}

QVariantMap createProps_measUsed()
{
    cc::property::field::ForField<NavEkfstatusFields::measUsed> props;
    props.name("measUsed")
         .add("pulse")
         .add("direction")
         .add("gyro")
         .add("temp")
         .add("pos")
         .add("vel")
         .add("errGyro")
         .add("errPulse");
    assert(props.bits().size() == NavEkfstatusFields::measUsed_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::property::field::ForField<NavEkfstatusFields::pulses>().name("pulses").asMap());
    props.append(cc::property::field::ForField<NavEkfstatusFields::period>().name("period").asMap());
    props.append(createProps_scaledValue("gyroMean", 2));
    props.append(createProps_scaledValue("temperature", 2));
    props.append(cc::property::field::ForField<NavEkfstatusFields::direction>().name("direction").asMap());
    props.append(createProps_calibStatus());
    props.append(createProps_scaledValue("pulseScale", 5));
    props.append(createProps_scaledValue("gyroBias", 5));
    props.append(createProps_scaledValue("gyroScale", 5));
    props.append(createProps_scaledValue("accPulseScale", 4));
    props.append(createProps_scaledValue("accGyroBias", 4));
    props.append(createProps_scaledValue("accGyroScale", 4));
    props.append(createProps_measUsed());
    props.append(cc_plugin::field::common::props_reserved(2));

    assert(props.size() == NavEkfstatus::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavEkfstatus::NavEkfstatus() = default;
NavEkfstatus::~NavEkfstatus() = default;

NavEkfstatus& NavEkfstatus::operator=(const NavEkfstatus&) = default;
NavEkfstatus& NavEkfstatus::operator=(NavEkfstatus&&) = default;

const char* NavEkfstatus::nameImpl() const
{
    static const char* Str = "NAV-EKFSTATUS";
    return Str;
}

const QVariantList& NavEkfstatus::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

