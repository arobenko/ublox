//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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

#include "CfgPm2.h"

#include "cc_plugin/field/common.h"

template class ublox::message::CfgPm2<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgPm2<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgPm2>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgPm2Fields;

QVariantMap createProps_flags()
{
    auto createReservedProps =
        []() -> QVariantMap
        {
            return cc::property::field::IntValue().hidden().asMap();
        };

    auto createSingleBitMask =
        [](const QString& name) -> QVariantMap
        {
            return cc::property::field::BitmaskValue().add(name).serialisedHidden().asMap();
        };

    cc::property::field::ForField<CfgPm2Fields::extintSelect> extintSelectProps;
    extintSelectProps.name("extintSelect")
                     .add("EXTINT0")
                     .add("EXTINT1")
                     .serialisedHidden();
    assert(extintSelectProps.values().size() == (int)CfgPm2Fields::ExtintSelect::NumOfValues);

    auto createEnableDisableProps =
        [](const char* name) -> QVariantMap
        {
            cc::property::field::EnumValue props;
            props.name(name)
                 .add("disabled")
                 .add("enabled")
                 .serialisedHidden();
            assert(props.values().size() == (int)CfgPm2Fields::DisabledEnabled::NumOfValues);
            return props.asMap();
        };

    cc::property::field::ForField<CfgPm2Fields::mode> modeProps;
    modeProps.name("mode")
             .add("ON/OFF")
             .add("Cyclic tracking")
             .serialisedHidden();
    assert(modeProps.values().size() == (int)CfgPm2Fields::Mode::NumOfValues);

    cc::property::field::ForField<CfgPm2Fields::flags> props;
    props.name("flags")
         .add(createReservedProps())
         .add(extintSelectProps.asMap())
         .add(createEnableDisableProps("extintWake"))
         .add(createEnableDisableProps("extintBackup"))
         .add(createEnableDisableProps("extintInactive"))
         .add(createEnableDisableProps("limitPeakCurr"))
         .add(createSingleBitMask("waitTimeFix"))
         .add(createSingleBitMask("updateRTC"))
         .add(createSingleBitMask("updateEPH"))
         .add(createReservedProps())
         .add(createSingleBitMask("doNotEnterOff"))
         .add(modeProps.asMap())
         .add(createReservedProps());
    assert(props.members().size() == CfgPm2Fields::flags::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_extintInactivity()
{
    return
        cc::property::field::Optional()
            .name("extintInactivity")
            .field(cc::property::field::IntValue().name("extintInactivity").asMap())
            .uncheckable()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<CfgPm2Fields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(cc_plugin::field::common::props_reserved(3));
    props.append(createProps_flags());
    props.append(
        cc::property::field::ForField<CfgPm2Fields::updatePeriod>().name("updatePeriod").asMap());
    props.append(
        cc::property::field::ForField<CfgPm2Fields::searchPeriod>().name("searchPeriod").asMap());
    props.append(
        cc::property::field::ForField<CfgPm2Fields::gridOffset>().name("gridOffset").asMap());
    props.append(
        cc::property::field::ForField<CfgPm2Fields::onTime>().name("onTime").asMap());
    props.append(
        cc::property::field::ForField<CfgPm2Fields::minAcqTime>().name("minAcqTime").asMap());
    props.append(cc_plugin::field::common::props_reserved(4));
    props.append(cc_plugin::field::common::props_reserved(5));
    props.append(cc_plugin::field::common::props_reserved(6));
    props.append(cc_plugin::field::common::props_reserved(7));
    props.append(cc_plugin::field::common::props_reserved(8));
    props.append(cc_plugin::field::common::props_reserved(9));
    props.append(cc_plugin::field::common::props_reserved(10));
    props.append(cc_plugin::field::common::props_reserved(11));
    props.append(createProps_extintInactivity());
    assert(props.size() == CfgPm2::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgPm2::CfgPm2() = default;
CfgPm2::~CfgPm2() = default;

CfgPm2& CfgPm2::operator=(const CfgPm2&) = default;
CfgPm2& CfgPm2::operator=(CfgPm2&&) = default;


const char* CfgPm2::nameImpl() const
{
    static const char* Str = "CFG-PM2";
    return Str;
}

const QVariantList& CfgPm2::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

