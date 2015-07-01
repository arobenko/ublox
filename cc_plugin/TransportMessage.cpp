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

enum FieldIdx
{
    FieldIdx_Sync1,
    FieldIdx_Sync2,
    FieldIdx_Checksum,
    FieldIdx_Id,
    FieldIdx_Len,
    FieldIdx_Payload,
    FieldIdx_NumOfValues
};

QVariantMap createSync1MemberData()
{
    QVariantMap map;
    map.insert(cc::Property::name(), "SYNC 1");
    return map;
}

QVariantMap createSync2MemberData()
{
    QVariantMap map;
    map.insert(cc::Property::name(), "SYNC 2");
    return map;
}

QVariantMap createLengthProperties()
{
    QVariantMap map;
    map.insert(cc::Property::name(), "LENGTH");
    return map;
}

QVariantMap createPayloadProperties()
{
    QVariantMap map;
    map.insert(cc::Property::name(), "PAYLOAD");
    return map;
}

QVariantMap createChecksumProperties()
{
    QVariantMap map;
    map.insert(cc::Property::name(), "CK");
    return map;
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createSync1MemberData());
    props.append(createSync2MemberData());
    props.append(createChecksumProperties());
    props.append(field::msgIdProperties());
    props.append(createLengthProperties());
    props.append(createPayloadProperties());

    assert(props.size() == FieldIdx_NumOfValues);
    return props;
}

}  // namespace

const QVariantList& TransportMessage::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}


}  // namespace cc_plugin

}  // namespace ublox

