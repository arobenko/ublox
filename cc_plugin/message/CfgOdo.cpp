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

#include "CfgOdo.h"

#include "cc_plugin/field/common.h"

template class ublox::message::CfgOdo<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgOdo<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgOdo>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgOdoFields;

QVariantMap createProps_flags()
{
    cc::property::field::ForField<CfgOdoFields::flags> props;
    props.name("flags")
         .add("useODO")
         .add("useCOG")
         .add("outLPVel")
         .add("outLPCog");
    assert(props.bits().size() == CfgOdoFields::flags::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_profile()
{
    auto props =
        cc::property::field::ForField<CfgOdoFields::profile>()
            .name("profile")
            .serialisedHidden()
            .add("running")
            .add("cycling")
            .add("swimming")
            .add("car")
            .add("custom");

    assert(props.values().size() == (int)CfgOdoFields::Profile::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_odoCfg()
{
    auto props =
        cc::property::field::ForField<CfgOdoFields::odoCfg>()
            .name("odoCfg")
            .add(createProps_profile())
            .add(cc::property::field::IntValue().hidden().asMap());

    assert(props.members().size() == CfgOdoFields::odoCfg::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<CfgOdoFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_flags());
    props.append(createProps_odoCfg());
    props.append(cc_plugin::field::common::createProps_reservedBundleTwoParts(2));
    props.append(
        cc::property::field::ForField<CfgOdoFields::cogMaxSpeed>().name("cogMaxSpeed").asMap());
    props.append(
        cc::property::field::ForField<CfgOdoFields::cogMaxPosAcc>().name("cogMaxPosAcc").asMap());
    props.append(cc_plugin::field::common::props_reserved(3));
    props.append(
        cc::property::field::ForField<CfgOdoFields::velLpGain>().name("velLpGain").asMap());
    props.append(
        cc::property::field::ForField<CfgOdoFields::cogLpGain>().name("cogLpGain").asMap());
    props.append(cc_plugin::field::common::props_reserved(4));
    assert(props.size() == CfgOdo::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgOdo::CfgOdo() = default;
CfgOdo::~CfgOdo() = default;

CfgOdo& CfgOdo::operator=(const CfgOdo&) = default;
CfgOdo& CfgOdo::operator=(CfgOdo&&) = default;


const char* CfgOdo::nameImpl() const
{
    static const char* Str = "CFG-ODO";
    return Str;
}

const QVariantList& CfgOdo::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

