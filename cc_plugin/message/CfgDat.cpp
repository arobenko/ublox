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

#include "CfgDat.h"
#include "cc_plugin/field/cfg.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgDat<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgDat<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgDat>;

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
    props.append(cc_plugin::field::cfg::datumNumProperties());
    props.append(cc_plugin::field::cfg::datumProperties());
    props.append(cc_plugin::field::cfg::majXProperties());
    props.append(cc_plugin::field::cfg::flatProperties());
    props.append(cc_plugin::field::cfg::dXProperties());
    props.append(cc_plugin::field::cfg::dYProperties());
    props.append(cc_plugin::field::cfg::dZProperties());
    props.append(cc_plugin::field::cfg::rotXProperties());
    props.append(cc_plugin::field::cfg::rotYProperties());
    props.append(cc_plugin::field::cfg::rotZProperties());
    props.append(cc_plugin::field::cfg::scaleProperties());

    assert(props.size() == CfgDat::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

CfgDat::CfgDat() = default;
CfgDat::~CfgDat() = default;

CfgDat& CfgDat::operator=(const CfgDat&) = default;
CfgDat& CfgDat::operator=(CfgDat&&) = default;


const char* CfgDat::nameImpl() const
{
    static const char* Str = "CFG-DAT";
    return Str;
}

const QVariantList& CfgDat::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

