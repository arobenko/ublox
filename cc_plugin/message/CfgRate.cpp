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

#include "CfgRate.h"
#include "cc_plugin/field/cfg.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgRate<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgRate<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgRate>;

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
    props.append(cc_plugin::field::cfg::measProperties());
    props.append(cc_plugin::field::cfg::navProperties());
    props.append(cc_plugin::field::cfg::timeProperties());

    assert(props.size() == CfgRate::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

CfgRate::CfgRate() = default;
CfgRate::~CfgRate() = default;

CfgRate& CfgRate::operator=(const CfgRate&) = default;
CfgRate& CfgRate::operator=(CfgRate&&) = default;


const char* CfgRate::nameImpl() const
{
    static const char* Str = "CFG-RATE";
    return Str;
}

const QVariantList& CfgRate::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

