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

#include "NavAtt.h"
#include "cc_plugin/field/nav.h"
#include "cc_plugin/field/common.h"

template class ublox::message::NavAtt<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavAtt<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavAtt>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::NavAttFields;

QVariantMap createProps_attField(const char* name)
{
    return
        cc::property::field::IntValue()
            .name(name)
            .scaledDecimals(5)
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(
        cc::property::field::ForField<NavAttFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_attField("roll"));
    props.append(createProps_attField("pitch"));
    props.append(createProps_attField("heading"));
    props.append(createProps_attField("accRoll"));
    props.append(createProps_attField("accPitch"));
    props.append(createProps_attField("accHeading"));

    assert(props.size() == NavAtt::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavAtt::NavAtt() = default;
NavAtt::~NavAtt() = default;

NavAtt& NavAtt::operator=(const NavAtt&) = default;
NavAtt& NavAtt::operator=(NavAtt&&) = default;

const char* NavAtt::nameImpl() const
{
    static const char* Str = "NAV-ATT";
    return Str;
}

const QVariantList& NavAtt::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

