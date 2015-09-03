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

#include <type_traits>
#include <functional>
#include <cassert>

#include "CfgPrtDdc.h"
#include "cc_plugin/field/cfg.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgPrtDdc<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgPrtDdc<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgPrtDdc>;

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

    auto slaveAddrProps = cc::Property::createPropertiesMap("slaveAddr");
    cc::Property::setSerialisedHidden(slaveAddrProps);

    auto createReservedFunc =
        []() -> QVariantMap
        {
            QVariantMap props;
            cc::Property::setFieldHidden(props);
            return props;
        };

    QVariantList membersData;
    membersData.append(createReservedFunc());
    membersData.append(std::move(slaveAddrProps));
    membersData.append(createReservedFunc());
    assert(membersData.size() == ublox::message::CfgPrtDdcField_mode_numOfValues);
    return cc::Property::createPropertiesMap("mode", std::move(membersData));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::cfg::props_readOnlyPortID());
    props.append(cc_plugin::field::common::props_reserved(0));
    props.append(cc_plugin::field::cfg::props_txReady());
    props.append(createProps_mode());
    props.append(cc_plugin::field::common::props_reserved(3));
    props.append(cc_plugin::field::cfg::props_inProtoMask());
    props.append(cc_plugin::field::cfg::props_outProtoMask());
    props.append(cc_plugin::field::cfg::props_prtFlags());
    props.append(cc_plugin::field::common::props_reserved(5));

    assert(props.size() == CfgPrtDdc::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgPrtDdc::CfgPrtDdc() = default;
CfgPrtDdc::~CfgPrtDdc() = default;

CfgPrtDdc& CfgPrtDdc::operator=(const CfgPrtDdc&) = default;
CfgPrtDdc& CfgPrtDdc::operator=(CfgPrtDdc&&) = default;


const char* CfgPrtDdc::nameImpl() const
{
    static const char* Str = "CFG-PRT (DDC)";
    return Str;
}

const QVariantList& CfgPrtDdc::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

