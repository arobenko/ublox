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

#include <type_traits>
#include <functional>
#include <cassert>

#include "CfgItfm.h"
#include "cc_plugin/field/cfg.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgItfm<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgItfm<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgItfm>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgItfmFields;

QVariantMap createProps_config()
{
    cc::property::field::ForField<CfgItfmFields::bbThreshold> bbThresholdProps;
    bbThresholdProps.name("bbThreshold").serialisedHidden();

    cc::property::field::ForField<CfgItfmFields::cwThreshold> cwThresholdProps;
    cwThresholdProps.name("cwThreshold").serialisedHidden();


    cc::property::field::ForField<CfgItfmFields::reserved1> reserved1Props;
    reserved1Props.name("reserved1").serialisedHidden();

    cc::property::field::ForField<CfgItfmFields::enable> enableProps;
    enableProps.add("enable").serialisedHidden();
    assert(enableProps.bits().size() == CfgItfmFields::enable::BitIdx_numOfValues);

    cc::property::field::ForField<CfgItfmFields::config> props;
    props.name("config")
         .add(bbThresholdProps.asMap())
         .add(cwThresholdProps.asMap())
         .add(reserved1Props.asMap())
         .add(enableProps.asMap());
    assert(props.members().size() == CfgItfmFields::config::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_config2()
{
    cc::property::field::ForField<CfgItfmFields::reserved2> reserved2Props;
    reserved2Props.name("reserved2").serialisedHidden();

    cc::property::field::ForField<CfgItfmFields::antSetting> antSettingProps;
    antSettingProps.name("antSetting")
                   .add("unknown")
                   .add("passive")
                   .add("active")
                   .serialisedHidden();
    assert(antSettingProps.values().size() == (int)CfgItfmFields::AntSetting::NumOfValues);

    cc::property::field::ForField<CfgItfmFields::reserved3> reserved3Props;
    reserved3Props.name("reserved3").serialisedHidden();

    cc::property::field::ForField<CfgItfmFields::config2> props;
    props.name("config2")
         .add(reserved2Props.asMap())
         .add(antSettingProps.asMap())
         .add(reserved3Props.asMap());
    assert(props.members().size() == CfgItfmFields::config2::FieldIdx_numOfValues);
    return props.asMap();
}


QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_config());
    props.append(createProps_config2());

    assert(props.size() == CfgItfm::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgItfm::CfgItfm() = default;
CfgItfm::~CfgItfm() = default;

CfgItfm& CfgItfm::operator=(const CfgItfm&) = default;
CfgItfm& CfgItfm::operator=(CfgItfm&&) = default;


const char* CfgItfm::nameImpl() const
{
    static const char* Str = "CFG-ITFM";
    return Str;
}

const QVariantList& CfgItfm::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

