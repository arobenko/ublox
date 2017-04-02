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
    auto bbThresholdProps =
        cc::property::field::ForField<CfgItfmFields::bbThreshold>()
            .name("bbThreshold")
            .serialisedHidden();

    auto cwThresholdProps =
        cc::property::field::ForField<CfgItfmFields::cwThreshold>()
            .name("cwThreshold")
            .serialisedHidden();

    auto algorithmBitsProps =
        cc::property::field::ForField<CfgItfmFields::algorithmBits>()
            .name("algorithmBits")
            .serialisedHidden();

    auto enableProps =
        cc::property::field::ForField<CfgItfmFields::enable>()
            .add("enable")
            .serialisedHidden();
    assert(enableProps.bits().size() == CfgItfmFields::enable::BitIdx_numOfValues);

    cc::property::field::ForField<CfgItfmFields::config> props;
    props.name("config")
         .add(bbThresholdProps.asMap())
         .add(cwThresholdProps.asMap())
         .add(algorithmBitsProps.asMap())
         .add(enableProps.asMap());
    assert(props.members().size() == CfgItfmFields::config::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_config2()
{
    auto generalBitsProps =
        cc::property::field::ForField<CfgItfmFields::generalBits>()
            .name("generalBits")
            .serialisedHidden();

    cc::property::field::ForField<CfgItfmFields::antSetting> antSettingProps;
    antSettingProps.name("antSetting")
                   .add("unknown")
                   .add("passive")
                   .add("active")
                   .serialisedHidden();
    assert(antSettingProps.values().size() == (int)CfgItfmFields::AntSetting::NumOfValues);

    auto enable2Props =
        cc::property::field::ForField<CfgItfmFields::enable2>()
            .add("enable2")
            .serialisedHidden();
    assert(enable2Props.bits().size() == CfgItfmFields::enable2::BitIdx_numOfValues);

    auto reservedProps = cc::property::field::IntValue().hidden();

    auto props =
        cc::property::field::ForField<CfgItfmFields::config2>()
            .name("config2")
            .add(generalBitsProps.asMap())
            .add(antSettingProps.asMap())
            .add(enable2Props.asMap())
            .add(reservedProps.asMap());
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

