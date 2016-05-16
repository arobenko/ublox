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

#include "CfgEkf.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgEkf<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgEkf<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgEkf>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgEkfFields;

QVariantMap createProps_disableEkf()
{
    cc::property::field::ForField<CfgEkfFields::disableEkf> props;
    props.name("disableEkf")
         .add("Enabled")
         .add("Disabled");
    assert(props.values().size() == (int)CfgEkfFields::DisableEkf::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_actionFlags()
{
    cc::property::field::ForField<CfgEkfFields::actionFlags> props;
    props.name("actionFlags")
         .add(CfgEkfFields::actionFlags_clTab, "clTab")
         .add("clCalib")
         .add(CfgEkfFields::actionFlags_nomTacho, "nomTacho")
         .add("nomGyro")
         .add("setTemp")
         .add("dir");
    assert(props.bits().size() == CfgEkfFields::actionFlags_numOfValues);
    return props.asMap();
}

QVariantMap createProps_configFlags()
{
    cc::property::field::ForField<CfgEkfFields::configFlags> props;
    props.name("configFlags")
         .add("pulsesPerM")
         .add("useSerWt");
    assert(props.bits().size() == CfgEkfFields::configFlags_numOfValues);
    return props.asMap();
}

QVariantMap createProps_inverseFlags()
{
    cc::property::field::ForField<CfgEkfFields::inverseFlags> props;
    props.name("inverseFlags")
         .add("invDir")
         .add("invGyro");
    assert(props.bits().size() == CfgEkfFields::inverseFlags_numOfValues);
    return props.asMap();
}

QVariantMap createProps_rmsTemp()
{
    return
        cc::property::field::ForField<CfgEkfFields::rmsTemp>()
            .name("rmsTemp")
            .scaledDecimals(1)
            .asMap();
}


QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_disableEkf());
    props.append(createProps_actionFlags());
    props.append(createProps_configFlags());
    props.append(createProps_inverseFlags());
    props.append(field::common::props_reserved(2));
    props.append(
        cc::property::field::ForField<CfgEkfFields::nomPPDist>().name("nomPPDist").asMap());
    props.append(
        cc::property::field::ForField<CfgEkfFields::nomZero>().name("nomZero").asMap());
    props.append(
        cc::property::field::ForField<CfgEkfFields::nomSens>().name("nomSens").asMap());
    props.append(createProps_rmsTemp());
    props.append(
        cc::property::field::ForField<CfgEkfFields::tempUpdate>().name("tempUpdate").asMap());
    assert(props.size() == CfgEkf::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgEkf::CfgEkf() = default;
CfgEkf::~CfgEkf() = default;

CfgEkf& CfgEkf::operator=(const CfgEkf&) = default;
CfgEkf& CfgEkf::operator=(CfgEkf&&) = default;


const char* CfgEkf::nameImpl() const
{
    static const char* Str = "CFG-EKF";
    return Str;
}

const QVariantList& CfgEkf::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

