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

#include "CfgCfg.h"

template class ublox::message::CfgCfg<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgCfg<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgCfg>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgCfgFields;

QVariantMap createProps_mask(const char* name)
{
    cc::property::field::ForField<CfgCfgFields::mask> props;
    props.name(name)
         .add("ioPort")
         .add("msgConf")
         .add("infMsg")
         .add("navConf")
         .add("rxmConf")
         .add(CfgCfgFields::mask::BitIdx_senConf, "senConf")
         .add("rinvConf")
         .add("antConf")
         .add("logConf")
         .add("ftsConf")
         ;
    assert(props.bits().size() == CfgCfgFields::mask::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_deviceMask()
{
    const QString Name("deviceMask");

    cc::property::field::ForField<CfgCfgFields::deviceMask::Field> props;
    props.name(Name)
         .add("devBBR")
         .add("devFlash")
         .add("devEEPROM")
         .add(CfgCfgFields::deviceMaskBitmask::BitIdx_devSpiFlash, "devSpiFlash");
    assert(props.bits().size() == CfgCfgFields::deviceMaskBitmask::BitIdx_numOfValues);

    return
        cc::property::field::ForField<CfgCfgFields::deviceMask>()
            .name(Name)
            .field(props.asMap())
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_mask("clearMask"));
    props.append(createProps_mask("saveMask"));
    props.append(createProps_mask("loadMask"));
    props.append(createProps_deviceMask());
    assert(props.size() == CfgCfg::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgCfg::CfgCfg() = default;
CfgCfg::~CfgCfg() = default;

CfgCfg& CfgCfg::operator=(const CfgCfg&) = default;
CfgCfg& CfgCfg::operator=(CfgCfg&&) = default;


const char* CfgCfg::nameImpl() const
{
    static const char* Str = "CFG-CFG";
    return Str;
}

const QVariantList& CfgCfg::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

