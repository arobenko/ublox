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

#include "MgaIniPosLlh.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaIniPosLlh<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaIniPosLlh<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaIniPosLlh>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaIniPosLlhFields;

QVariantMap createProps_lat()
{
    return
        cc::property::field::ForField<MgaIniPosLlhFields::lat>()
            .name("lat")
            .scaledDecimals(7)
            .asMap();
}

QVariantMap createProps_lon()
{
    return
        cc::property::field::ForField<MgaIniPosLlhFields::lat>()
            .name("lat")
            .scaledDecimals(7)
            .asMap();
}


QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaIniPosLlhFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaIniPosLlhFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_lat());
    props.append(createProps_lon());
    props.append(
        cc::property::field::ForField<MgaIniPosLlhFields::alt>().name("alt").asMap());
    props.append(
        cc::property::field::ForField<MgaIniPosLlhFields::posAcc>().name("posAcc").asMap());

    assert(props.size() == MgaIniPosLlh::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaIniPosLlh::MgaIniPosLlh() = default;
MgaIniPosLlh::~MgaIniPosLlh() = default;

MgaIniPosLlh& MgaIniPosLlh::operator=(const MgaIniPosLlh&) = default;
MgaIniPosLlh& MgaIniPosLlh::operator=(MgaIniPosLlh&&) = default;

const char* MgaIniPosLlh::nameImpl() const
{
    static const char* Str = "MGA-INI-POS_LLH";
    return Str;
}

const QVariantList& MgaIniPosLlh::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

