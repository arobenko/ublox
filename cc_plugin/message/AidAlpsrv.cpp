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

#include "AidAlpsrv.h"

template class ublox::message::AidAlpsrv<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::AidAlpsrv<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::AidAlpsrv>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::AidAlpsrvFields;

QVariantMap createProps_dataSize()
{
    return
        cc::property::field::ForField<AidAlpsrvFields::dataSize>()
            .name("dataSize")
            .readOnly()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<AidAlpsrvFields::idSize>().name("idSize").asMap());
    props.append(
        cc::property::field::ForField<AidAlpsrvFields::type>().name("type").asMap());
    props.append(
        cc::property::field::ForField<AidAlpsrvFields::ofs>().name("ofs").asMap());
    props.append(
        cc::property::field::ForField<AidAlpsrvFields::size>().name("size").asMap());
    props.append(
        cc::property::field::ForField<AidAlpsrvFields::fileId>().name("fileId").asMap());
    props.append(createProps_dataSize());
    props.append(
        cc::property::field::ForField<AidAlpsrvFields::id1>().name("id1").asMap());
    props.append(
        cc::property::field::ForField<AidAlpsrvFields::id2>().name("id2").asMap());
    props.append(
        cc::property::field::ForField<AidAlpsrvFields::id3>().name("id3").asMap());
    props.append(
        cc::property::field::ForField<AidAlpsrvFields::data<> >().name("data").asMap());
    assert(props.size() == AidAlpsrv::FieldIdx_numOfValues);
    return props;
}

}  // namespace

AidAlpsrv::AidAlpsrv() = default;
AidAlpsrv::~AidAlpsrv() = default;

AidAlpsrv& AidAlpsrv::operator=(const AidAlpsrv&) = default;
AidAlpsrv& AidAlpsrv::operator=(AidAlpsrv&&) = default;


const char* AidAlpsrv::nameImpl() const
{
    static const char* Str = "AID-ALPSRV";
    return Str;
}

const QVariantList& AidAlpsrv::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

