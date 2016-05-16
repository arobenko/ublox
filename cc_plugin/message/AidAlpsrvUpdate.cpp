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

#include "AidAlpsrvUpdate.h"

template class ublox::message::AidAlpsrvUpdate<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::AidAlpsrvUpdate<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::AidAlpsrvUpdate>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::AidAlpsrvUpdateFields;

QVariantMap createProps_size()
{
    return
        cc::property::field::ForField<AidAlpsrvUpdateFields::size>()
            .name("size")
            .readOnly()
            .asMap();
}

QVariantMap createProps_data()
{
    return
        cc::property::field::ForField<AidAlpsrvUpdateFields::data>()
            .name("data")
            .add(cc::property::field::IntValue().asMap())
            .serialisedHidden()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<AidAlpsrvUpdateFields::idSize>().name("idSize").asMap());
    props.append(
        cc::property::field::ForField<AidAlpsrvUpdateFields::type>().name("type").asMap());
    props.append(
        cc::property::field::ForField<AidAlpsrvUpdateFields::ofs>().name("ofs").asMap());
    props.append(createProps_size());
    props.append(
        cc::property::field::ForField<AidAlpsrvUpdateFields::fileId>().name("fileId").asMap());
    props.append(createProps_data());
    assert(props.size() == AidAlpsrvUpdate::FieldIdx_numOfValues);
    return props;
}

}  // namespace

AidAlpsrvUpdate::AidAlpsrvUpdate() = default;
AidAlpsrvUpdate::~AidAlpsrvUpdate() = default;

AidAlpsrvUpdate& AidAlpsrvUpdate::operator=(const AidAlpsrvUpdate&) = default;
AidAlpsrvUpdate& AidAlpsrvUpdate::operator=(AidAlpsrvUpdate&&) = default;


const char* AidAlpsrvUpdate::nameImpl() const
{
    static const char* Str = "AID-ALPSRV (Update)";
    return Str;
}

const QVariantList& AidAlpsrvUpdate::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

