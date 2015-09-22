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

#include "MonRxr.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MonRxr<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MonRxr<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MonRxr>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_flags()
{
    QVariantList bitNames;
    bitNames.append("awake");
    assert(bitNames.size() == ublox::message::MonRxrField_data_numOfValues);
    return cc::Property::createPropertiesMap("flags", std::move(bitNames));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_flags());
    assert(props.size() == MonRxr::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MonRxr::MonRxr() = default;
MonRxr::~MonRxr() = default;

MonRxr& MonRxr::operator=(const MonRxr&) = default;
MonRxr& MonRxr::operator=(MonRxr&&) = default;

const char* MonRxr::nameImpl() const
{
    static const char* Str = "MON-RXR";
    return Str;
}

const QVariantList& MonRxr::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

