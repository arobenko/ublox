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

#include "CfgFxn.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgFxn<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgFxn<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgFxn>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgFxnFields;

QVariantMap createProps_flags()
{
    cc::property::field::ForField<CfgFxnFields::flags> props;
    props.name("flags")
         .add(CfgFxnFields::flags_sleep, "sleep")
         .add(CfgFxnFields::flags_absAlign, "absAlign")
         .add("onOff");
    assert(props.bits().size() == CfgFxnFields::flags_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_flags());
    props.append(
        cc::property::field::ForField<CfgFxnFields::tReacq>().name("tReacq").asMap());
    props.append(
        cc::property::field::ForField<CfgFxnFields::tAcq>().name("tAcq").asMap());
    props.append(
        cc::property::field::ForField<CfgFxnFields::tReacqOff>().name("tReacqOff").asMap());
    props.append(
        cc::property::field::ForField<CfgFxnFields::tAcqOff>().name("tAcqOff").asMap());
    props.append(
        cc::property::field::ForField<CfgFxnFields::tOn>().name("tOn").asMap());
    props.append(
        cc::property::field::ForField<CfgFxnFields::tOff>().name("tOff").asMap());
    props.append(cc_plugin::field::common::props_reserved(0));
    props.append(
        cc::property::field::ForField<CfgFxnFields::baseTow>().name("baseTow").asMap());

    assert(props.size() == CfgFxn::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgFxn::CfgFxn() = default;
CfgFxn::~CfgFxn() = default;

CfgFxn& CfgFxn::operator=(const CfgFxn&) = default;
CfgFxn& CfgFxn::operator=(CfgFxn&&) = default;


const char* CfgFxn::nameImpl() const
{
    static const char* Str = "CFG-FXN";
    return Str;
}

const QVariantList& CfgFxn::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

