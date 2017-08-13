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

#include "EsfRaw.h"

#include <cassert>

#include "cc_plugin/field/common.h"

template class ublox::message::EsfRaw<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::EsfRaw<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::EsfRaw>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::EsfRawFields;

QVariantMap createProps_list()
{
    using BlockField = EsfRawFields::block;
    auto blockProps =
        cc::property::field::ForField<BlockField>()
            .add(cc::property::field::ForField<EsfRawFields::dataField>().name("dataField").asMap())
            .add(cc::property::field::ForField<EsfRawFields::dataType>().name("dataType").asMap())
            .add(cc::property::field::ForField<EsfRawFields::sTtag>().name("sTtag").asMap())
            .serialisedHidden();
    assert(blockProps.members().size() == BlockField::FieldIdx_numOfValues);

    return
        cc::property::field::ForField<EsfRawFields::list<> >()
            .name("data")
            .add(blockProps.asMap())
            .serialisedHidden()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_list());

    assert(props.size() == EsfRaw::FieldIdx_numOfValues);
    return props;
}

}  // namespace

EsfRaw::EsfRaw() = default;
EsfRaw::~EsfRaw() = default;

EsfRaw& EsfRaw::operator=(const EsfRaw&) = default;
EsfRaw& EsfRaw::operator=(EsfRaw&&) = default;

const char* EsfRaw::nameImpl() const
{
    static const char* Str = "ESF-RAW";
    return Str;
}

const QVariantList& EsfRaw::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

