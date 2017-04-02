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

#include "MgaGloTimeoffset.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaGloTimeoffset<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaGloTimeoffset<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaGloTimeoffset>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaGloTimeoffsetFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaGloTimeoffsetFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaGloTimeoffsetFields::version>().name("version").asMap());
    props.append(
        cc::property::field::ForField<MgaGloTimeoffsetFields::N>().name("N").asMap());
    props.append(
        cc::property::field::ForField<MgaGloTimeoffsetFields::tauC>().name("tauC").asMap());
    props.append(
        cc::property::field::ForField<MgaGloTimeoffsetFields::tauGps>().name("tauGps").asMap());
    props.append(
        cc::property::field::ForField<MgaGloTimeoffsetFields::B1>().name("B1").asMap());
    props.append(
        cc::property::field::ForField<MgaGloTimeoffsetFields::B2>().name("B2").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));

    assert(props.size() == MgaGloTimeoffset::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaGloTimeoffset::MgaGloTimeoffset() = default;
MgaGloTimeoffset::~MgaGloTimeoffset() = default;

MgaGloTimeoffset& MgaGloTimeoffset::operator=(const MgaGloTimeoffset&) = default;
MgaGloTimeoffset& MgaGloTimeoffset::operator=(MgaGloTimeoffset&&) = default;

const char* MgaGloTimeoffset::nameImpl() const
{
    static const char* Str = "MGA-GLO-TIMEOFFSET";
    return Str;
}

const QVariantList& MgaGloTimeoffset::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

