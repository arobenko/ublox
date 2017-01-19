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

#include "CfgPm.h"

#include "cc_plugin/field/common.h"

template class ublox::message::CfgPm<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgPm<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgPm>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgPmFields;

QVariantMap createProps_flags()
{
    auto createReservedProps =
        []() -> QVariantMap
        {
            return cc::property::field::IntValue().hidden().asMap();
        };

    cc::property::field::ForField<CfgPmFields::internal> internalProps;
    internalProps.name("internal").serialisedHidden();

    cc::property::field::ForField<CfgPmFields::extintSelect> extintSelectProps;
    extintSelectProps.name("extintSelect")
                     .add("EXTINT0")
                     .add("EXTINT1")
                     .serialisedHidden();
    assert(extintSelectProps.values().size() == (int)CfgPmFields::ExtintSelect::NumOfValues);

    auto createEnableDisableProps =
        [](const char* name) -> QVariantMap
        {
            cc::property::field::EnumValue props;
            props.name(name)
                 .add("disabled")
                 .add("enabled")
                 .serialisedHidden();
            assert(props.values().size() == (int)CfgPmFields::DisabledEnabled::NumOfValues);
            return props.asMap();
        };

    cc::property::field::ForField<CfgPmFields::remainingFlags> flagsProps;
    flagsProps.add("waitTimeFix")
              .add("updateRtc")
              .add("updateEPH")
              .serialisedHidden();
    assert(flagsProps.bits().size() == CfgPmFields::remainingFlags::BitIdx_numOfValues);

    cc::property::field::ForField<CfgPmFields::flags> props;
    props.name("flags")
         .add(createReservedProps())
         .add(internalProps.asMap())
         .add(extintSelectProps.asMap())
         .add(createEnableDisableProps("extintWake"))
         .add(createEnableDisableProps("extintBackup"))
         .add(createReservedProps())
         .add(createEnableDisableProps("limitPeakCurr"))
         .add(flagsProps.asMap());
    assert(props.members().size() == CfgPmFields::flags::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<CfgPmFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(cc_plugin::field::common::props_reserved(3));
    props.append(createProps_flags());
    props.append(
        cc::property::field::ForField<CfgPmFields::updatePeriod>().name("updatePeriod").asMap());
    props.append(
        cc::property::field::ForField<CfgPmFields::searchPeriod>().name("searchPeriod").asMap());
    props.append(
        cc::property::field::ForField<CfgPmFields::gridOffset>().name("gridOffset").asMap());
    props.append(
        cc::property::field::ForField<CfgPmFields::onTime>().name("onTime").asMap());
    props.append(
        cc::property::field::ForField<CfgPmFields::minAcqTime>().name("minAcqTime").asMap());
    assert(props.size() == CfgPm::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgPm::CfgPm() = default;
CfgPm::~CfgPm() = default;

CfgPm& CfgPm::operator=(const CfgPm&) = default;
CfgPm& CfgPm::operator=(CfgPm&&) = default;


const char* CfgPm::nameImpl() const
{
    static const char* Str = "CFG-PM";
    return Str;
}

const QVariantList& CfgPm::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

