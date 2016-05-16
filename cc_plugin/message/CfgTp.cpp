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

#include <cassert>

#include "CfgTp.h"
#include "cc_plugin/field/cfg.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgTp<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgTp<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgTp>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgTpFields;

QVariantMap createProps_status()
{
    return
        cc::property::field::ForField<CfgTpFields::status>()
            .name("status")
            .add("negative", (int)CfgTpFields::Status::Negative)
            .add("off", (int)CfgTpFields::Status::Off)
            .add("positive", (int)CfgTpFields::Status::Positive)
            .asMap();
}

QVariantMap createProps_timeRef()
{
    cc::property::field::ForField<CfgTpFields::timeRef> props;
    props.name("timeRef")
         .add("UTC time")
         .add("GPS time")
         .add("Local time");
    assert(props.values().size() == (int)CfgTpFields::TimeRef::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_flags()
{
    cc::property::field::ForField<CfgTpFields::flags> props;
    props.name("flags")
         .add("syncMode");
    assert(props.bits().size() == CfgTpFields::flags_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<CfgTpFields::interval>().name("interval").asMap());
    props.append(
        cc::property::field::ForField<CfgTpFields::length>().name("length").asMap());
    props.append(createProps_status());
    props.append(createProps_timeRef());
    props.append(createProps_flags());
    props.append(cc_plugin::field::common::props_reserved(0));
    props.append(
        cc::property::field::ForField<CfgTpFields::antennaCableDelay>().name("antennaCableDelay").asMap());
    props.append(
        cc::property::field::ForField<CfgTpFields::rfGroupDelay>().name("rfGroupDelay").asMap());
    props.append(
        cc::property::field::ForField<CfgTpFields::userDelay>().name("userDelay").asMap());

    assert(props.size() == CfgTp::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgTp::CfgTp() = default;
CfgTp::~CfgTp() = default;

CfgTp& CfgTp::operator=(const CfgTp&) = default;
CfgTp& CfgTp::operator=(CfgTp&&) = default;


const char* CfgTp::nameImpl() const
{
    static const char* Str = "CFG-TP";
    return Str;
}

const QVariantList& CfgTp::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

