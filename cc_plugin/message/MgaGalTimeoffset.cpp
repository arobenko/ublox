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

#include "MgaGalTimeoffset.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaGalTimeoffset<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaGalTimeoffset<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaGalTimeoffset>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaGalTimeoffsetFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaGalTimeoffsetFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaGalTimeoffsetFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MgaGalTimeoffsetFields::a0G>().name("a0G").asMap());
    props.append(
        cc::property::field::ForField<MgaGalTimeoffsetFields::a1G>().name("a1G").asMap());
    props.append(
        cc::property::field::ForField<MgaGalTimeoffsetFields::t0G>().name("t0G").asMap());
    props.append(
        cc::property::field::ForField<MgaGalTimeoffsetFields::wn0G>().name("wn0G").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));

    assert(props.size() == MgaGalTimeoffset::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaGalTimeoffset::MgaGalTimeoffset() = default;
MgaGalTimeoffset::~MgaGalTimeoffset() = default;

MgaGalTimeoffset& MgaGalTimeoffset::operator=(const MgaGalTimeoffset&) = default;
MgaGalTimeoffset& MgaGalTimeoffset::operator=(MgaGalTimeoffset&&) = default;

const char* MgaGalTimeoffset::nameImpl() const
{
    static const char* Str = "MGA-GAL-TIMEOFFSET";
    return Str;
}

const QVariantList& MgaGalTimeoffset::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

