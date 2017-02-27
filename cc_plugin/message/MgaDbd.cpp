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

#include "MgaDbd.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaDbd<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaDbd<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaDbd>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaDbdFields;

QVariantList createFieldsProperties()
{
    QVariantList props;

    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(cc_plugin::field::common::props_reserved(3));
    props.append(
        cc::property::field::ForField<MgaDbdFields::data<> >().name("data").asMap());

    assert(props.size() == MgaDbd::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaDbd::MgaDbd() = default;
MgaDbd::~MgaDbd() = default;

MgaDbd& MgaDbd::operator=(const MgaDbd&) = default;
MgaDbd& MgaDbd::operator=(MgaDbd&&) = default;

const char* MgaDbd::nameImpl() const
{
    static const char* Str = "MGA-DBD";
    return Str;
}

const QVariantList& MgaDbd::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

