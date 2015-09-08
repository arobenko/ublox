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

QVariantMap createProps_disableEkf()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "Enabled");
    cc::Property::appendEnumValue(enumValues, "Disabled");
    assert(enumValues.size() == (int)ublox::message::CfgEkf_DisableEkf::NumOfValues);
    return cc::Property::createPropertiesMap("disableEkf", std::move(enumValues));
}

QVariantMap createProps_actionFlags()
{
    QVariantList bitNames;
    bitNames.append(QVariant());
    bitNames.append("clTab");
    bitNames.append("clCalib");
    bitNames.append(QVariant());
    bitNames.append("nomTacho");
    bitNames.append("nomGyro");
    bitNames.append("setTemp");
    bitNames.append("dir");
    assert(bitNames.size() == ublox::message::CfgEkfField_actionFlags_numOfValues);
    return cc::Property::createPropertiesMap("actionFlags", std::move(bitNames));
}

QVariantMap createProps_configFlags()
{
    QVariantList bitNames;
    bitNames.append("pulsesPerM");
    bitNames.append("useSerWt");
    assert(bitNames.size() == ublox::message::CfgEkfField_configFlags_numOfValues);
    return cc::Property::createPropertiesMap("configFlags", std::move(bitNames));
}

QVariantMap createProps_inverseFlags()
{
    QVariantList bitNames;
    bitNames.append("invDir");
    bitNames.append("invGyro");
    assert(bitNames.size() == ublox::message::CfgEkfField_inverseFlags_numOfValues);
    return cc::Property::createPropertiesMap("inverseFlags", std::move(bitNames));
}

QVariantMap createProps_rmsTemp()
{
    auto props = cc::Property::createPropertiesMap("rmsTemp");
    cc::Property::setDisplayScaled(props);
    cc::Property::setFloatDecimals(props, 1);
    return props;
}


QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_disableEkf());
    props.append(createProps_actionFlags());
    props.append(createProps_configFlags());
    props.append(createProps_inverseFlags());
    props.append(field::common::props_reserved(2));
    props.append(cc::Property::createPropertiesMap("nomPPDist"));
    props.append(cc::Property::createPropertiesMap("nomZero"));
    props.append(cc::Property::createPropertiesMap("nomSens"));
    props.append(createProps_rmsTemp());
    props.append(cc::Property::createPropertiesMap("tempUpdate"));
    assert(props.size() == CfgEkf::FieldIdx_numOfValues);
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

