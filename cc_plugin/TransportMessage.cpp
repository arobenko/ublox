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

#include "TransportMessage.h"

#include <cassert>

#include <QtCore/QVariantMap>

#include "cc_plugin/field/MsgId.h"

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace
{

typedef cc_plugin::Message::Field FieldBase;

QVariantMap createSync1MemberData()
{
    typedef ublox::details::SyncField1<FieldBase> SyncField1;
    return cc::property::field::ForField<SyncField1>().name("SYNC 1").asMap();
}

QVariantMap createSync2MemberData()
{
    typedef ublox::details::SyncField2<FieldBase> SyncField2;
    return cc::property::field::ForField<SyncField2>().name("SYNC 2").asMap();
}

QVariantMap createLengthProperties()
{
    typedef ublox::details::LengthField<FieldBase> LengthField;
    return cc::property::field::ForField<LengthField>().name("LENGTH").asMap();
}

QVariantMap createPayloadProperties()
{
    typedef ublox::details::DataField<FieldBase> DataField;
    return cc::property::field::ForField<DataField>().name("PAYLOAD").asMap();
}

QVariantMap createChecksumProperties()
{
    typedef ublox::details::ChecksumField<FieldBase> ChecksumField;
    return cc::property::field::ForField<ChecksumField>().name("CK").asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createSync1MemberData());
    props.append(createSync2MemberData());
    props.append(field::msgIdProperties());
    props.append(createLengthProperties());
    props.append(createPayloadProperties());
    props.append(createChecksumProperties());
    assert(props.size() == TransportMessage::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

const QVariantList& TransportMessage::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

comms::ErrorStatus TransportMessage::readImpl(ReadIterator& iter, std::size_t size)
{
    static const auto ChecksumLen =
        sizeof(ublox::details::ChecksumField<cc_plugin::Message::Field>::ValueType);

    size -= ChecksumLen;
    auto es = Base::readFieldsUntil<FieldIdx_Checksum>(iter, size);
    if (es == comms::ErrorStatus::Success) {
        size += ChecksumLen;
        es = readFieldsFrom<FieldIdx_Checksum>(iter, size);
    }
    return es;
}


}  // namespace cc_plugin

}  // namespace ublox

