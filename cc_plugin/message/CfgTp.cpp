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

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::cfg::intervalProperties());
    props.append(cc_plugin::field::cfg::lengthProperties());
    props.append(cc_plugin::field::cfg::statusProperties());
    props.append(cc_plugin::field::cfg::timeRefProperties());
    props.append(cc_plugin::field::common::resProperties());
    props.append(cc_plugin::field::cfg::antennaCableDelayProperties());
    props.append(cc_plugin::field::cfg::rfGroupDelayProperties());
    props.append(cc_plugin::field::cfg::userDelayProperties());

    assert(props.size() == CfgTp::FieldIdx_NumOfValues);
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

