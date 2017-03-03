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

#include "MgaIniClkd.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaIniClkd<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaIniClkd<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaIniClkd>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaIniClkdFields;


QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaIniClkdFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaIniClkdFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MgaIniClkdFields::clkD>().name("clkD").asMap());
    props.append(
        cc::property::field::ForField<MgaIniClkdFields::clkDAcc>().name("clkDAcc").asMap());
    assert(props.size() == MgaIniClkd::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaIniClkd::MgaIniClkd() = default;
MgaIniClkd::~MgaIniClkd() = default;

MgaIniClkd& MgaIniClkd::operator=(const MgaIniClkd&) = default;
MgaIniClkd& MgaIniClkd::operator=(MgaIniClkd&&) = default;

const char* MgaIniClkd::nameImpl() const
{
    static const char* Str = "MGA-INI-CLKD";
    return Str;
}

const QVariantList& MgaIniClkd::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

