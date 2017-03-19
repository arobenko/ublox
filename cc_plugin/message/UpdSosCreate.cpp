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

#include "UpdSosCreate.h"
#include "cc_plugin/field/common.h"

template class ublox::message::UpdSosCreate<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::UpdSosCreate<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::UpdSosCreate>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::UpdSosCreateFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<UpdSosCreateFields::cmd>().name("cmd").readOnly().asMap());
    props.append(cc_plugin::field::common::props_reserved(1));

    assert(props.size() == UpdSosCreate::FieldIdx_numOfValues);
    return props;
}

}  // namespace

UpdSosCreate::UpdSosCreate() = default;
UpdSosCreate::~UpdSosCreate() = default;

UpdSosCreate& UpdSosCreate::operator=(const UpdSosCreate&) = default;
UpdSosCreate& UpdSosCreate::operator=(UpdSosCreate&&) = default;

const char* UpdSosCreate::nameImpl() const
{
    static const char* Str = "UPD-SOS (Create)";
    return Str;
}

const QVariantList& UpdSosCreate::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

