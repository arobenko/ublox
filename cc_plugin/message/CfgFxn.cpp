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

QVariantMap createProps_flags()
{
    QVariantList bitNames;
    bitNames.append(QVariant());
    bitNames.append("sleep");
    bitNames.append(QVariant());
    bitNames.append("absAlign");
    bitNames.append("onOff");
    assert(bitNames.size() == ublox::message::CfgFxnFields::flags_numOfValues);
    return cc::Property::createPropertiesMap("flags", std::move(bitNames));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_flags());
    props.append(cc::Property::createPropertiesMap("tReacq"));
    props.append(cc::Property::createPropertiesMap("tAcq"));
    props.append(cc::Property::createPropertiesMap("tReacqOff"));
    props.append(cc::Property::createPropertiesMap("tAcqOff"));
    props.append(cc::Property::createPropertiesMap("tOn"));
    props.append(cc::Property::createPropertiesMap("tOff"));
    props.append(cc_plugin::field::common::props_reserved(0));
    props.append(cc::Property::createPropertiesMap("baseTow"));

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

