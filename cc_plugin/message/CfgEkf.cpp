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

#include "CfgEkf.h"
#include "cc_plugin/field/cfg.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgEkf<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgEkf<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgEkf>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createDisableEkfProperties()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "Enabled");
    cc::Property::appendEnumValue(enumValues, "Disabled");

    return cc::Property::createPropertiesMap("disable_ekf", std::move(enumValues));
}

QVariantMap createActionFlagsProperties()
{
    QVariantList bitNames;
    bitNames.append(QVariant());
    bitNames.append("Clear temperature compensation table");
    bitNames.append("Clear stored calibration");
    bitNames.append(QVariant());
    bitNames.append("Set nominal tacho pulses");
    bitNames.append("Set nominal gyro values");
    bitNames.append("Set temp table config");
    bitNames.append("Set direction pin and gyro sense meaning");

    return cc::Property::createPropertiesMap("action_flags", std::move(bitNames));
}

QVariantMap createInverseFlagsProperties()
{
    QVariantList bitNames;
    bitNames.append("Direction pin: Backwards");
    bitNames.append("Gyro rotation sense: Anty-clockwise positive");

    return cc::Property::createPropertiesMap("inverse_flags", std::move(bitNames));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createDisableEkfProperties());
    props.append(createActionFlagsProperties());
    props.append(field::common::resProperties());
    props.append(createInverseFlagsProperties());
    props.append(field::common::resProperties());
    props.append(cc::Property::createPropertiesMap("nom_ppkm"));
    props.append(cc::Property::createPropertiesMap("nom_zero"));
    props.append(cc::Property::createPropertiesMap("nom_sens"));
    props.append(cc::Property::createPropertiesMap("RMSTemp"));
    props.append(cc::Property::createPropertiesMap("TempUpdate"));

    assert(props.size() == CfgEkf::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

CfgEkf::CfgEkf() = default;
CfgEkf::~CfgEkf() = default;

CfgEkf& CfgEkf::operator=(const CfgEkf&) = default;
CfgEkf& CfgEkf::operator=(CfgEkf&&) = default;


const char* CfgEkf::nameImpl() const
{
    static const char* Str = "CFG-EKF";
    return Str;
}

const QVariantList& CfgEkf::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

