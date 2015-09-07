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

#include "CfgCfg.h"

template class ublox::message::CfgCfg<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgCfg<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgCfg>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_mask(const char* name)
{
    QVariantList bitNames;
    bitNames.append("ioPort");
    bitNames.append("msgConf");
    bitNames.append("infMsg");
    bitNames.append("navConf");
    bitNames.append("rxmConf");
    bitNames.append(QVariant());
    bitNames.append(QVariant());
    bitNames.append(QVariant());
    bitNames.append(QVariant());
    bitNames.append("rinvConf");
    bitNames.append("antConf");
    assert(bitNames.size() == ublox::message::CfgCfgField_mask_numOfValues);
    return cc::Property::createPropertiesMap(name, std::move(bitNames));
}

QVariantMap createProps_deviceMask()
{
    QVariantList bitNames;
    bitNames.append("devBBR");
    bitNames.append("devFlash");
    bitNames.append("devEEPROM");
    bitNames.append(QVariant());
    bitNames.append("devSpiFlash");
    assert(bitNames.size() == ublox::message::CfgCfgField_deviceMask_numOfValues);

    static const QString Name("deviceMask");
    auto maskProps = cc::Property::createPropertiesMap(Name, std::move(bitNames));
    return cc::Property::createPropertiesMap(Name, std::move(maskProps));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_mask("clearMask"));
    props.append(createProps_mask("saveMask"));
    props.append(createProps_mask("loadMask"));
    props.append(createProps_deviceMask());
    assert(props.size() == CfgCfg::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgCfg::CfgCfg() = default;
CfgCfg::~CfgCfg() = default;

CfgCfg& CfgCfg::operator=(const CfgCfg&) = default;
CfgCfg& CfgCfg::operator=(CfgCfg&&) = default;


const char* CfgCfg::nameImpl() const
{
    static const char* Str = "CFG-CFG";
    return Str;
}

const QVariantList& CfgCfg::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

