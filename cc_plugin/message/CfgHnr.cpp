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

#include "CfgHnr.h"

#include <cassert>

#include "cc_plugin/field/common.h"

template class ublox::message::CfgHnr<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgHnr<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgHnr>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgHnrFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::property::field::ForField<CfgHnrFields::highNavRate>().name("highNavRate").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));

    assert(props.size() == CfgHnr::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgHnr::CfgHnr() = default;
CfgHnr::~CfgHnr() = default;

CfgHnr& CfgHnr::operator=(const CfgHnr&) = default;
CfgHnr& CfgHnr::operator=(CfgHnr&&) = default;

const char* CfgHnr::nameImpl() const
{
    static const char* Str = "CFG-HNR";
    return Str;
}

const QVariantList& CfgHnr::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

