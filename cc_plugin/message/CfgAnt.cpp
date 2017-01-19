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

#include <cassert>

#include "CfgAnt.h"

template class ublox::message::CfgAnt<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgAnt<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgAnt>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::CfgAntFields;

QVariantMap createProps_flags()
{
    cc::property::field::ForField<CfgAntFields::flags> props;
    props.name("flags")
         .add("svcs")
         .add("scd")
         .add("ocd")
         .add("pdwnOnSCD")
         .add("recovery");
    assert(props.bits().size() == CfgAntFields::flags::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_pins()
{
    auto createPinPropsFunc =
        [](const char* name) -> QVariantMap
        {
            return
                cc::property::field::ForField<CfgAntFields::pinX>()
                    .name(name)
                    .serialisedHidden()
                    .asMap();
        };

    cc::property::field::BitmaskValue bitsProps;
    bitsProps.add("reconfig")
             .serialisedHidden();
    assert(bitsProps.bits().size() == CfgAntFields::reconfig::BitIdx_numOfValues);

    cc::property::field::ForField<CfgAntFields::pins> props;
    props.name("pins")
         .add(createPinPropsFunc("pinSwitch"))
         .add(createPinPropsFunc("pinSCD"))
         .add(createPinPropsFunc("pinOCD"))
         .add(bitsProps.asMap());
    assert(props.members().size() == CfgAntFields::pins::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_flags());
    props.append(createProps_pins());
    assert(props.size() == CfgAnt::FieldIdx_numOfValues);
    return props;
}

}  // namespace

CfgAnt::CfgAnt() = default;
CfgAnt::~CfgAnt() = default;

CfgAnt& CfgAnt::operator=(const CfgAnt&) = default;
CfgAnt& CfgAnt::operator=(CfgAnt&&) = default;


const char* CfgAnt::nameImpl() const
{
    static const char* Str = "CFG-ANT";
    return Str;
}

const QVariantList& CfgAnt::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

