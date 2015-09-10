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

#include "CfgNvs.h"

template class ublox::message::CfgNvs<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgNvs<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgNvs>;

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

    auto fillBitNamesFunc =
        [&bitNames](int until)
        {
            while (bitNames.size() < until) {
                bitNames.append(QVariant());
            }
        };

    static const int AlmBitIdx = 17;
    fillBitNamesFunc(AlmBitIdx);
    bitNames.append("alm");
    static const int AopBitIdx = 29;
    fillBitNamesFunc(AopBitIdx);
    bitNames.append("aop");
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
    assert(bitNames.size() == ublox::message::CfgNvsField_deviceMask_numOfValues);

    return cc::Property::createPropertiesMap("deviceMask", std::move(bitNames));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_mask("clearMask"));
    props.append(createProps_mask("saveMask"));
    props.append(createProps_mask("loadMask"));
    props.append(createProps_deviceMask());
    assert(props.size() == CfgNvs::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgNvs::CfgNvs() = default;
CfgNvs::~CfgNvs() = default;

CfgNvs& CfgNvs::operator=(const CfgNvs&) = default;
CfgNvs& CfgNvs::operator=(CfgNvs&&) = default;


const char* CfgNvs::nameImpl() const
{
    static const char* Str = "CFG-NVS";
    return Str;
}

const QVariantList& CfgNvs::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

