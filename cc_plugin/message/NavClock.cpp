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

#include "NavClock.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavClock<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavClock<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavClock>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::NavClockFields;

QVariantMap createProps_clkB()
{
    return
        cc::property::field::ForField<NavClockFields::clkB>()
            .name("clkB")
            .asMap();
}

QVariantMap createProps_clkD()
{
    return
        cc::property::field::ForField<NavClockFields::clkD>()
            .name("clkD")
            .asMap();
}

QVariantMap createProps_fAcc()
{
    return
        cc::property::field::ForField<NavClockFields::fAcc>()
            .name("fAcc")
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(createProps_clkB());
    props.append(createProps_clkD());
    props.append(cc_plugin::field::nav::props_tAcc());
    props.append(createProps_fAcc());

    assert(props.size() == NavClock::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavClock::NavClock() = default;
NavClock::~NavClock() = default;

NavClock& NavClock::operator=(const NavClock&) = default;
NavClock& NavClock::operator=(NavClock&&) = default;

const char* NavClock::nameImpl() const
{
    static const char* Str = "NAV-CLOCK";
    return Str;
}

const QVariantList& NavClock::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

