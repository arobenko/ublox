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

#include "MgaFlashStop.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaFlashStop<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaFlashStop<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaFlashStop>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaFlashStopFields;

QVariantList createFieldsProperties()
{
    QVariantList props;

    props.append(
        cc::property::field::ForField<MgaFlashStopFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaFlashStopFields::version>().name("version").asMap());
    assert(props.size() == MgaFlashStop::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaFlashStop::MgaFlashStop() = default;
MgaFlashStop::~MgaFlashStop() = default;

MgaFlashStop& MgaFlashStop::operator=(const MgaFlashStop&) = default;
MgaFlashStop& MgaFlashStop::operator=(MgaFlashStop&&) = default;

const char* MgaFlashStop::nameImpl() const
{
    static const char* Str = "MGA-FLASH-STOP";
    return Str;
}

const QVariantList& MgaFlashStop::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

