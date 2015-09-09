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

#include "CfgSbas.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgSbas<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgSbas<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgSbas>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_mode()
{
    QVariantList bitNames;
    bitNames.append("enabled");
    bitNames.append("test");
    assert(bitNames.size() == ublox::message::CfgSbasField_mode_numOfValues);
    return cc::Property::createPropertiesMap("mode", std::move(bitNames));
}

QVariantMap createProps_usage()
{
    QVariantList bitNames;
    bitNames.append("range");
    bitNames.append("diffCorr");
    bitNames.append("integrity");
    assert(bitNames.size() == ublox::message::CfgSbasField_usage_numOfValues);
    return cc::Property::createPropertiesMap("usage", std::move(bitNames));
}

QVariantMap createProps_scanmode(int idx, int base, int count)
{
    QVariantList bitNames;
    for (auto idx = 0; idx < count; ++idx) {
        bitNames.append(QString("PRN%1").arg(base + idx));
    }
    return cc::Property::createPropertiesMap(QString("scanmode%1").arg(idx), std::move(bitNames));
}


QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_mode());
    props.append(createProps_usage());
    props.append(cc::Property::createPropertiesMap("maxSBAS"));
    props.append(createProps_scanmode(2, 152, ublox::message::CfgSbasField_scanmode2_numOfValues));
    props.append(createProps_scanmode(1, 120, ublox::message::CfgSbasField_scanmode1_numOfValues));
    assert(props.size() == CfgSbas::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgSbas::CfgSbas() = default;
CfgSbas::~CfgSbas() = default;

CfgSbas& CfgSbas::operator=(const CfgSbas&) = default;
CfgSbas& CfgSbas::operator=(CfgSbas&&) = default;


const char* CfgSbas::nameImpl() const
{
    static const char* Str = "CFG-SBAS";
    return Str;
}

const QVariantList& CfgSbas::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

