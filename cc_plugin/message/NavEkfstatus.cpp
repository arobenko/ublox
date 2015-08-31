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

QVariantMap createProps_scaledValue(const QString& name, int decimals)
{
    auto props = cc::Property::createPropertiesMap(name);
    cc::Property::setDisplayScaled(props);
    cc::Property::setFloatDecimals(props, decimals);
    return props;
}

QVariantMap createProps_calibStatus_calib(const QString& name)
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "no calibration");
    cc::Property::appendEnumValue(enumValues, "calibrating");
    cc::Property::appendEnumValue(enumValues, "coarse calibration");
    cc::Property::appendEnumValue(enumValues, "fine calibration");
    assert(enumValues.size() == (int)ublox::message::NavEkfstatus_CalibStatus::NumOfValues);
    auto props = cc::Property::createPropertiesMap(name, std::move(enumValues));
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantMap createProps_calibStatus_reserved()
{
    auto props = cc::Property::createPropertiesMap("reserved");
    cc::Property::setFieldHidden(props);
    return props;
}

QVariantMap createProps_calibStatus()
{
    QVariantList membersData;
    membersData.append(createProps_calibStatus_calib("calibTacho"));
    membersData.append(createProps_calibStatus_calib("calibGyro"));
    membersData.append(createProps_calibStatus_calib("calibGyroB"));
    membersData.append(createProps_calibStatus_reserved());
    assert(membersData.size() == ublox::message::NavEkfstatusField_calibStatus_numOfValues);
    return cc::Property::createPropertiesMap("calibStatus", std::move(membersData));
}

QVariantMap createProps_measUsed()
{
    QVariantList bitNames;
    bitNames.append("pulse");
    bitNames.append("direction");
    bitNames.append("gyro");
    bitNames.append("temp");
    bitNames.append("pos");
    bitNames.append("vel");
    bitNames.append("errGyro");
    bitNames.append("errPulse");
    assert(bitNames.size() == ublox::message::NavEkfstatusField_measUsed_numOfValues);
    return cc::Property::createPropertiesMap("measUsed", std::move(bitNames));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::Property::createPropertiesMap("pulses"));
    props.append(cc::Property::createPropertiesMap("period"));
    props.append(createProps_scaledValue("gyroMean", 2));
    props.append(createProps_scaledValue("temperature", 2));
    props.append(cc::Property::createPropertiesMap("direction"));
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

