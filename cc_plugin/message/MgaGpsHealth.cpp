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

#include "MgaGpsHealth.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaGpsHealth<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaGpsHealth<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaGpsHealth>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaGpsHealthFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaGpsHealthFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaGpsHealthFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MgaGpsHealthFields::healthCode<> >().name("healthCode").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));

    assert(props.size() == MgaGpsHealth::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaGpsHealth::MgaGpsHealth() = default;
MgaGpsHealth::~MgaGpsHealth() = default;

MgaGpsHealth& MgaGpsHealth::operator=(const MgaGpsHealth&) = default;
MgaGpsHealth& MgaGpsHealth::operator=(MgaGpsHealth&&) = default;

const char* MgaGpsHealth::nameImpl() const
{
    static const char* Str = "MGA-GPS-HEALTH";
    return Str;
}

const QVariantList& MgaGpsHealth::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

