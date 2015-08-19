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
#include "cc_plugin/field/cfg.h"
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

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::cfg::fxnFlagsProperties());
    props.append(cc_plugin::field::cfg::tReacqProperties());
    props.append(cc_plugin::field::cfg::tAcqProperties());
    props.append(cc_plugin::field::cfg::tReacqOffProperties());
    props.append(cc_plugin::field::cfg::tAcqOffProperties());
    props.append(cc_plugin::field::cfg::tOnProperties());
    props.append(cc_plugin::field::cfg::tOffProperties());
    props.append(cc_plugin::field::common::resProperties());
    props.append(cc_plugin::field::cfg::baseTowProperties());

    assert(props.size() == CfgFxn::FieldIdx_NumOfValues);
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

