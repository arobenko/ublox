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

#include "AidAlm.h"

template class ublox::message::AidAlm<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::AidAlm<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::AidAlm>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::AidAlmFields;

QVariantMap createProps_dwrd()
{
    static const QString Name("dwrd");
    cc::property::field::ArrayList listProps;
    listProps.name(Name).serialisedHidden();

    static const auto NumOfElems =
        AidAlmFields::dwrd::Field::ParsedOptions::SequenceFixedSize;

    for (auto idx = 0U; idx < NumOfElems; ++idx) {
        listProps.add(
            cc::property::field::IntValue().name(QString("%1").arg(idx, 1, 10, QChar('0'))).asMap());
    }

    return
        cc::property::field::ForField<AidAlmFields::dwrd>()
            .name(Name)
            .field(listProps.asMap())
            .uncheckable()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<AidAlmFields::svid>().name("svid").asMap());
    props.append(
        cc::property::field::ForField<AidAlmFields::week>().name("week").asMap());
    props.append(createProps_dwrd());

    assert(props.size() == AidAlm::FieldIdx_numOfValues);
    return props;
}

}  // namespace

AidAlm::AidAlm() = default;
AidAlm::~AidAlm() = default;

AidAlm& AidAlm::operator=(const AidAlm&) = default;
AidAlm& AidAlm::operator=(AidAlm&&) = default;


const char* AidAlm::nameImpl() const
{
    static const char* Str = "AID-ALM";
    return Str;
}

const QVariantList& AidAlm::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

