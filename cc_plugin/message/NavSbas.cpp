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

#include "NavSbas.h"
#include "cc_plugin/field/nav.h"
#include "cc_plugin/field/common.h"

template class ublox::message::NavSbas<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavSbas<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavSbas>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::NavSbasFields;

QVariantMap createProps_mode()
{
    return
        cc::property::field::ForField<NavSbasFields::mode>()
            .name("mode")
            .add("Disabled", (int)NavSbasFields::Mode::Disabled)
            .add("Enabed Integrity", (int)NavSbasFields::Mode::EnabledIntegrity)
            .add("Enabed Testmode", (int)NavSbasFields::Mode::EnabledTestmode)
            .asMap();
}

QVariantMap createProps_sys(const QString& propsName)
{
    return
        cc::property::field::ForField<NavSbasFields::sys>()
            .name(propsName)
            .add("Unknown", (int)NavSbasFields::Sys::Unknown)
            .add("WAAS", (int)NavSbasFields::Sys::WAAS)
            .add("EGNOS", (int)NavSbasFields::Sys::EGNOS)
            .add("MSAS", (int)NavSbasFields::Sys::MSAS)
            .add("GPS", (int)NavSbasFields::Sys::GPS)
            .asMap();
}

QVariantMap createProps_service(const QString& propsName)
{
    cc::property::field::ForField<NavSbasFields::service> props;
    props.name(propsName)
         .add("Ranging")
         .add("Corrections")
         .add("Integrity")
         .add("Testmode");
    assert(props.bits().size() == NavSbasFields::service::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_data()
{
    cc::property::field::ForField<NavSbasFields::block> blockProps;
    blockProps.add(cc_plugin::field::nav::props_svid())
              .add(cc::property::field::ForField<NavSbasFields::flags>().name("flags").asMap())
              .add(cc::property::field::ForField<NavSbasFields::udre>().name("udre").asMap())
              .add(createProps_sys("svSys"))
              .add(createProps_service("svService"))
              .add(cc_plugin::field::common::props_reserved(1))
              .add(cc::property::field::ForField<NavSbasFields::prc>().name("prc").asMap())
              .add(cc_plugin::field::common::props_reserved(2))
              .add(cc::property::field::ForField<NavSbasFields::ic>().name("ic").asMap());


    return
        cc::property::field::ForField<NavSbasFields::data<> >()
            .name("data")
            .add(blockProps.asMap())
            .serialisedHidden()
            .asMap();
}


QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(cc::property::field::ForField<NavSbasFields::geo>().name("geo").asMap());
    props.append(createProps_mode());
    props.append(createProps_sys("sys"));
    props.append(createProps_service("service"));
    props.append(cc_plugin::field::nav::props_cnt());
    props.append(cc_plugin::field::common::props_reserved(0));
    props.append(createProps_data());

    assert(props.size() == NavSbas::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavSbas::NavSbas() = default;
NavSbas::~NavSbas() = default;

NavSbas& NavSbas::operator=(const NavSbas&) = default;
NavSbas& NavSbas::operator=(NavSbas&&) = default;


const char* NavSbas::nameImpl() const
{
    static const char* Str = "NAV-SBAS";
    return Str;
}

const QVariantList& NavSbas::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

