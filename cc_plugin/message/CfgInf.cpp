//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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

#include <type_traits>
#include <functional>
#include <cassert>

#include "CfgInf.h"
#include "cc_plugin/field/cfg.h"
#include "cc_plugin/field/common.h"

template class ublox::message::CfgInf<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgInf<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgInf>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgInfFields;

QVariantMap createProps_infMsgMask()
{
    auto createBitmaskProps =
        [](const char* name) -> QVariantMap
        {
            cc::property::field::ForField<CfgInfFields::mask> props;
            props.name(name)
                 .add("ERROR")
                 .add("WARNING")
                 .add("NOTICE")
                 .add("DEBUG")
                 .add("TEST");
            assert(props.bits().size() == CfgInfFields::mask::BitIdx_numOfValues);
            return props.asMap();
        };

    cc::property::field::ForField<CfgInfFields::infMsgMask> props;
    props.name("infMsgMask")
         .add(createBitmaskProps("DDC"))
         .add(createBitmaskProps("UART"))
         .add(createBitmaskProps("UART2"))
         .add(createBitmaskProps("USB"))
         .add(createBitmaskProps("SPI"))
         .add(createBitmaskProps("RESERVED"))
         .serialisedHidden();
    assert(props.elements().size() == CfgInfFields::infMsgMask_numOfValues);
    return props.asMap();
}

QVariantMap createProps_list()
{
    cc::property::field::ForField<CfgInfFields::element> elemProps;
    elemProps.add(field::cfg::props_protocolID())
             .add(field::common::props_reserved(0))
             .add(field::common::props_reserved(1))
             .add(createProps_infMsgMask());
    assert(elemProps.members().size() == CfgInfFields::element::FieldIdx_numOfValues);

    return
        cc::property::field::ForField<CfgInfFields::list>()
            .name("list")
            .add(elemProps.asMap())
            .serialisedHidden()
            .asMap();
}


QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_list());

    assert(props.size() == CfgInf::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgInf::CfgInf() = default;
CfgInf::~CfgInf() = default;

CfgInf& CfgInf::operator=(const CfgInf&) = default;
CfgInf& CfgInf::operator=(CfgInf&&) = default;


const char* CfgInf::nameImpl() const
{
    static const char* Str = "CFG-INF";
    return Str;
}

const QVariantList& CfgInf::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

