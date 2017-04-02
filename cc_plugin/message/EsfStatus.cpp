//
// Copyright 2017 (C). Alex Robenko. All rights reserved.
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

#include "EsfStatus.h"

#include <cassert>

#include "cc_plugin/field/common.h"

template class ublox::message::EsfStatus<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::EsfStatus<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::EsfStatus>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::EsfStatusFields;

QVariantMap createProps_fusionMode()
{
    auto props =
        cc::property::field::ForField<EsfStatusFields::fusionMode>()
            .name("fusionMode")
            .add("Initializing")
            .add("On")
            .add("On Hold")
            .add("Off");
    assert(props.values().size() == (int)EsfStatusFields::FusionMode::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_numSens()
{
    return
        cc::property::field::ForField<EsfStatusFields::numSens>()
            .name("numSens")
            .readOnly()
            .asMap();
}

QVariantMap createProps_sensStatus1()
{
    auto flagsProps =
        cc::property::field::ForField<EsfStatusFields::flagsSensStatus1>()
            .serialisedHidden()
            .add("used")
            .add("ready");

    assert(flagsProps.bits().size() == EsfStatusFields::flagsSensStatus1::BitIdx_numOfValues);

    auto props =
        cc::property::field::ForField<EsfStatusFields::sensStatus1>()
            .name("sensStatus1")
            .add(cc::property::field::ForField<EsfStatusFields::type>().name("type").serialisedHidden().asMap())
            .add(flagsProps.asMap());

    assert(props.members().size() == EsfStatusFields::sensStatus1::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_calibStatus()
{
    auto props =
        cc::property::field::ForField<EsfStatusFields::calibStatus>()
            .name("calibStatus")
            .add("Not calibrated")
            .add("Calibrating")
            .add("Calibrated")
            .add("Calibrated (2)")
            .serialisedHidden();
    assert(props.values().size() == (int)EsfStatusFields::CalibStatus::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_timeStatus()
{
    auto props =
        cc::property::field::ForField<EsfStatusFields::timeStatus>()
            .name("timeStatus")
            .add("No data")
            .add("First byte")
            .add("Event input")
            .add("Time tag")
            .serialisedHidden();
    assert(props.values().size() == (int)EsfStatusFields::TimeStatus::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_sensStatus2()
{
    auto props =
        cc::property::field::ForField<EsfStatusFields::sensStatus2>()
            .name("sensStatus2")
            .add(createProps_calibStatus())
            .add(createProps_timeStatus())
            .add(cc::property::field::IntValue().hidden().asMap());

    assert(props.members().size() == EsfStatusFields::sensStatus2::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_faults()
{
    auto props =
        cc::property::field::ForField<EsfStatusFields::faults>()
            .name("faults")
            .add("badMeas")
            .add("badTTag")
            .add("missingMeas")
            .add("noisyMeas");
    assert(props.bits().size() == EsfStatusFields::faults::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_data()
{
    auto blockProps =
        cc::property::field::ForField<EsfStatusFields::block>()
            .add(createProps_sensStatus1())
            .add(createProps_sensStatus2())
            .add(cc::property::field::ForField<EsfStatusFields::freq>().name("freq").asMap())
            .add(createProps_faults());
    assert(blockProps.members().size() == EsfStatusFields::block::FieldIdx_numOfValues);

    return
        cc::property::field::ForField<EsfStatusFields::data<> >()
            .name("data")
            .add(blockProps.asMap())
            .serialisedHidden()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::common::props_iTOW());
    props.append(
        cc::property::field::ForField<EsfStatusFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::createProps_reservedBundleTwoParts(1));
    props.append(createProps_fusionMode());
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(createProps_numSens());
    props.append(createProps_data());

    assert(props.size() == EsfStatus::FieldIdx_numOfValues);
    return props;
}

}  // namespace

EsfStatus::EsfStatus() = default;
EsfStatus::~EsfStatus() = default;

EsfStatus& EsfStatus::operator=(const EsfStatus&) = default;
EsfStatus& EsfStatus::operator=(EsfStatus&&) = default;

const char* EsfStatus::nameImpl() const
{
    static const char* Str = "ESF-STATUS";
    return Str;
}

const QVariantList& EsfStatus::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

