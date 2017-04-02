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

#include "MgaIniEop.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaIniEop<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaIniEop<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaIniEop>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaIniEopFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaIniEopFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaIniEopFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MgaIniEopFields::d2kRef>().name("d2kRef").asMap());
    props.append(
        cc::property::field::ForField<MgaIniEopFields::d2kMax>().name("d2kMax").asMap());
    props.append(
        cc::property::field::ForField<MgaIniEopFields::xpP0>().name("xpP0").asMap());
    props.append(
        cc::property::field::ForField<MgaIniEopFields::xpP1>().name("xpP1").asMap());
    props.append(
        cc::property::field::ForField<MgaIniEopFields::ypP0>().name("ypP0").asMap());
    props.append(
        cc::property::field::ForField<MgaIniEopFields::ypP1>().name("ypP1").asMap());
    props.append(
        cc::property::field::ForField<MgaIniEopFields::dUT1>().name("dUT1").asMap());
    props.append(
        cc::property::field::ForField<MgaIniEopFields::ddUT1>().name("ddUT1").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(cc_plugin::field::common::props_reserved(3));
    props.append(cc_plugin::field::common::props_reserved(4));
    props.append(cc_plugin::field::common::props_reserved(5));
    props.append(cc_plugin::field::common::props_reserved(6));
    props.append(cc_plugin::field::common::props_reserved(7));
    props.append(cc_plugin::field::common::props_reserved(8));
    props.append(cc_plugin::field::common::props_reserved(9));
    props.append(cc_plugin::field::common::props_reserved(10));
    props.append(cc_plugin::field::common::props_reserved(11));
    assert(props.size() == MgaIniEop::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaIniEop::MgaIniEop() = default;
MgaIniEop::~MgaIniEop() = default;

MgaIniEop& MgaIniEop::operator=(const MgaIniEop&) = default;
MgaIniEop& MgaIniEop::operator=(MgaIniEop&&) = default;

const char* MgaIniEop::nameImpl() const
{
    static const char* Str = "MGA-INI-EOP";
    return Str;
}

const QVariantList& MgaIniEop::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

