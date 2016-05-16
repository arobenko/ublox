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

#include "CfgNvs.h"

template class ublox::message::CfgNvs<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgNvs<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgNvs>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgNvsFields;

QVariantMap createProps_mask(const char* name)
{
    cc::property::field::ForField<CfgNvsFields::mask> props;
    props.name(name)
         .add(ublox::message::CfgNvsFields::mask_alm, "alm")
         .add(ublox::message::CfgNvsFields::mask_aop, "aop");
    assert(props.bits().size() == CfgNvsFields::mask_numOfValues);
    return props.asMap();
}

QVariantMap createProps_deviceMask()
{
    cc::property::field::ForField<CfgNvsFields::deviceMask> props;
    props.name("deviceMask")
         .add("devBBR")
         .add("devFlash")
         .add("devEEPROM")
         .add(CfgNvsFields::deviceMask_devSpiFlash, "devSpiFlash");
    assert(props.bits().size() == CfgNvsFields::deviceMask_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_mask("clearMask"));
    props.append(createProps_mask("saveMask"));
    props.append(createProps_mask("loadMask"));
    props.append(createProps_deviceMask());
    assert(props.size() == CfgNvs::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgNvs::CfgNvs() = default;
CfgNvs::~CfgNvs() = default;

CfgNvs& CfgNvs::operator=(const CfgNvs&) = default;
CfgNvs& CfgNvs::operator=(CfgNvs&&) = default;


const char* CfgNvs::nameImpl() const
{
    static const char* Str = "CFG-NVS";
    return Str;
}

const QVariantList& CfgNvs::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

