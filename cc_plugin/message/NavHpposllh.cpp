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

#include "NavHpposllh.h"
#include "cc_plugin/field/nav.h"
#include "cc_plugin/field/common.h"

template class ublox::message::NavHpposllh<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavHpposllh<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavHpposllh>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using NavHpposllhFields = ublox::message::NavHpposllhFields;

QVariantMap createProps_degHp(const char* name)
{
    return
        cc::property::field::IntValue()
            .name(name)
            .scaledDecimals(9)
            .asMap();
}

QVariantMap createProps_mmHp(const char* name)
{
    return
        cc::property::field::IntValue()
            .name(name)
            .scaledDecimals(1)
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<NavHpposllhFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(cc_plugin::field::nav::props_lon());
    props.append(cc_plugin::field::nav::props_lat());
    props.append(cc_plugin::field::nav::props_height());
    props.append(cc_plugin::field::nav::props_hMSL());
    props.append(createProps_degHp("lonHp"));
    props.append(createProps_degHp("latHp"));
    props.append(createProps_mmHp("heightHp"));
    props.append(createProps_mmHp("hMSLHp"));
    props.append(createProps_mmHp("hAcc"));
    props.append(createProps_mmHp("vAcc"));

    assert(props.size() == NavHpposllh::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavHpposllh::NavHpposllh() = default;
NavHpposllh::~NavHpposllh() = default;

NavHpposllh& NavHpposllh::operator=(const NavHpposllh&) = default;
NavHpposllh& NavHpposllh::operator=(NavHpposllh&&) = default;


const char* NavHpposllh::nameImpl() const
{
    static const char* Str = "NAV-HPPOSLLH";
    return Str;
}

const QVariantList& NavHpposllh::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

