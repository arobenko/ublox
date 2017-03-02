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

#include "MgaGpsIono.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaGpsIono<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaGpsIono<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaGpsIono>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaGpsIonoFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaGpsIonoFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaGpsIonoFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MgaGpsIonoFields::ionoAlpha0>().name("ionoAlpha0").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsIonoFields::ionoAlpha1>().name("ionoAlpha1").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsIonoFields::ionoAlpha2>().name("ionoAlpha2").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsIonoFields::ionoAlpha3>().name("ionoAlpha3").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsIonoFields::ionoBeta0>().name("ionoBeta0").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsIonoFields::ionoBeta1>().name("ionoBeta1").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsIonoFields::ionoBeta2>().name("ionoBeta2").asMap());
    props.append(
        cc::property::field::ForField<MgaGpsIonoFields::ionoBeta3>().name("ionoBeta3").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));

    assert(props.size() == MgaGpsIono::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaGpsIono::MgaGpsIono() = default;
MgaGpsIono::~MgaGpsIono() = default;

MgaGpsIono& MgaGpsIono::operator=(const MgaGpsIono&) = default;
MgaGpsIono& MgaGpsIono::operator=(MgaGpsIono&&) = default;

const char* MgaGpsIono::nameImpl() const
{
    static const char* Str = "MGA-GPS-IONO";
    return Str;
}

const QVariantList& MgaGpsIono::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

