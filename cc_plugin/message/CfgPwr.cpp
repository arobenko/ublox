//
// Copyright 2017 (C). Alex Robenko. All rights reserved.
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

#include "CfgPwr.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgPwr<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgPwr<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgPwr>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgPwrFields;

QVariantMap createProps_state()
{
    return
        cc::property::field::ForField<CfgPwrFields::state>()
            .name("state")
            .add("Software Backup", (long long)CfgPwrFields::State::SoftwareBackup)
            .add("GNSS Running", (long long)CfgPwrFields::State::GnssRunning)
            .add("GNSS Stopped", (long long)CfgPwrFields::State::GnssStopped)
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<CfgPwrFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_state());

    assert(props.size() == CfgPwr::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgPwr::CfgPwr() = default;
CfgPwr::~CfgPwr() = default;

CfgPwr& CfgPwr::operator=(const CfgPwr&) = default;
CfgPwr& CfgPwr::operator=(CfgPwr&&) = default;


const char* CfgPwr::nameImpl() const
{
    static const char* Str = "CFG-PWR";
    return Str;
}

const QVariantList& CfgPwr::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

