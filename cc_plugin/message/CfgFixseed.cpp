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

#include "CfgFixseed.h"

#include <cassert>

#include "cc_plugin/field/common.h"
#include "cc_plugin/field/MsgId.h"

template class ublox::message::CfgFixseed<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgFixseed<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgFixseed>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgFixseedFields;

QVariantMap createProps_length()
{
    return
        cc::property::field::ForField<CfgFixseedFields::length>()
            .name("length")
            .readOnly()
            .asMap();
}

QVariantMap createProps_list()
{
    return
        cc::property::field::ForField<CfgFixseedFields::list<> >()
            .name("list")
            .add(cc_plugin::field::msgIdProperties())
            .serialisedHidden()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;

    props.append(cc::property::field::ForField<CfgFixseedFields::version>().name("version").asMap());
    props.append(createProps_length());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc::property::field::ForField<CfgFixseedFields::seedHi>().name("seedHi").asMap());
    props.append(cc::property::field::ForField<CfgFixseedFields::seedHi>().name("seedLo ").asMap());
    props.append(createProps_list());

    assert(props.size() == CfgFixseed::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgFixseed::CfgFixseed() = default;
CfgFixseed::~CfgFixseed() = default;

CfgFixseed& CfgFixseed::operator=(const CfgFixseed&) = default;
CfgFixseed& CfgFixseed::operator=(CfgFixseed&&) = default;

const char* CfgFixseed::nameImpl() const
{
    static const char* Str = "CFG-FIXSEED";
    return Str;
}

const QVariantList& CfgFixseed::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

