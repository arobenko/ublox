//
// Copyright 2015 (C). Alex Robenko. All rights reserved.
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

#include "InfDebug.h"
#include "cc_plugin/field/inf.h"

template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::InfDebug<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::InfDebug>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::inf::stringProperties());

    assert(props.size() == InfDebug::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

InfDebug::InfDebug() = default;
InfDebug::~InfDebug() = default;

InfDebug& InfDebug::operator=(const InfDebug&) = default;
InfDebug& InfDebug::operator=(InfDebug&&) = default;

const char* InfDebug::nameImpl() const
{
    static const char* Str = "INF-DEBUG";
    return Str;
}

const QVariantList& InfDebug::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

