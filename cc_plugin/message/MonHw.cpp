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

QVariantMap createProps_aStatus()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "INIT");
    cc::Property::appendEnumValue(enumValues, "DONTKNOW");
    cc::Property::appendEnumValue(enumValues, "OK");
    cc::Property::appendEnumValue(enumValues, "SHORT");
    cc::Property::appendEnumValue(enumValues, "OPEN");
    assert(enumValues.size() == (int)ublox::message::MonHwFields::AStatus::NumOfValues);
    return cc::Property::createPropertiesMap("aStatus", std::move(enumValues));
}

QVariantMap createProps_aPower()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "OFF");
    cc::Property::appendEnumValue(enumValues, "ON");
    cc::Property::appendEnumValue(enumValues, "DONTKNOW");
    assert(enumValues.size() == (int)ublox::message::MonHwFields::APower::NumOfValues);
    return cc::Property::createPropertiesMap("aPower", std::move(enumValues));
}

QVariantMap createProps_flags()
{
    QVariantList bitNames;
    bitNames.append("rtcCalib");
    assert(bitNames.size() == ublox::message::MonHwFields::rtcCalib_numOfValues);
    auto rtcCalibProps = cc::Property::createPropertiesMap("flags", std::move(bitNames));
    cc::Property::setSerialisedHidden(rtcCalibProps);

    QVariantList safeBootValues;
    cc::Property::appendEnumValue(safeBootValues, "Inactive");
    cc::Property::appendEnumValue(safeBootValues, "Active");
    assert(safeBootValues.size() == (int)ublox::message::MonHwFields::SafeBoot::NumOfValues);
    auto safeBootProps = cc::Property::createPropertiesMap("safeBoot", std::move(safeBootValues));
    cc::Property::setSerialisedHidden(safeBootProps);

    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "unknown");
    cc::Property::appendEnumValue(enumValues, "ok");
    cc::Property::appendEnumValue(enumValues, "warning");
    cc::Property::appendEnumValue(enumValues, "critical");
    assert(enumValues.size() == (int)ublox::message::MonHwFields::JammingState::NumOfValues);
    auto jammingStateProps = cc::Property::createPropertiesMap("jammingState", std::move(enumValues));
    cc::Property::setSerialisedHidden(jammingStateProps);

    auto reservedProps = cc::Property::createPropertiesMap(QString());
    cc::Property::setFieldHidden(reservedProps);

    QVariantList membersData;
    membersData.append(std::move(rtcCalibProps));
    membersData.append(std::move(safeBootProps));
    membersData.append(std::move(jammingStateProps));
    membersData.append(std::move(reservedProps));
    return cc::Property::createPropertiesMap("flags", std::move(membersData));
}

QVariantMap createProps_VP()
{
    QVariantList elemProps;
    for (auto idx = 0U; idx < ublox::message::MonHwFields::VP::ParsedOptions::SequenceFixedSize; ++idx) {
        elemProps.append(cc::Property::createPropertiesMap(QString("%1").arg(idx)));
    }

    auto props = cc::Property::createPropertiesMap("VP", std::move(elemProps));
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::Property::createPropertiesMap("pinSel"));
    props.append(cc::Property::createPropertiesMap("pinBank"));
    props.append(cc::Property::createPropertiesMap("pinDir"));
    props.append(cc::Property::createPropertiesMap("pinVal"));
    props.append(cc::Property::createPropertiesMap("noisePerMS"));
    props.append(cc::Property::createPropertiesMap("agcCnt"));
    props.append(createProps_aStatus());
    props.append(createProps_aPower());
    props.append(createProps_flags());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc::Property::createPropertiesMap("usedMask"));
    props.append(createProps_VP());
    props.append(cc::Property::createPropertiesMap("jamInd"));
    props.append(cc_plugin::field::common::props_reserved(3));
    props.append(cc::Property::createPropertiesMap("pinIrq"));
    props.append(cc::Property::createPropertiesMap("pullH"));
    props.append(cc::Property::createPropertiesMap("pullL"));
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

