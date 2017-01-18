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

#include "CfgRinv.h"

template class ublox::message::CfgRinv<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgRinv<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgRinv>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgRinvFields;

QVariantMap createProps_flags()
{
    cc::property::field::ForField<CfgRinvFields::flags> props;
    props.name("flags")
         .add("dump")
         .add("binary");
    assert(props.bits().size() == CfgRinvFields::flags::BitIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_flags());
    props.append(
        cc::property::field::ForField<CfgRinvFields::data>().name("data").asMap());

    assert(props.size() == CfgRinv::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgRinv::CfgRinv() = default;
CfgRinv::~CfgRinv() = default;

CfgRinv& CfgRinv::operator=(const CfgRinv&) = default;
CfgRinv& CfgRinv::operator=(CfgRinv&&) = default;


const char* CfgRinv::nameImpl() const
{
    static const char* Str = "CFG-RINV";
    return Str;
}

const QVariantList& CfgRinv::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

