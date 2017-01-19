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

#include "NavSol.h"
#include "cc_plugin/field/common.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavSol<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavSol<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavSol>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::NavSolFields;

QVariantMap createProps_flags()
{
    cc::property::field::ForField<NavSolFields::flags> props;
    props.name("flags")
         .add("GPSfixOK")
         .add("DiffSoln")
         .add("WKNSET")
         .add("TOWSET");

    assert(props.bits().size() == NavSolFields::flags::BitIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::props_iTOW());
    props.append(cc_plugin::field::nav::props_fTOW());
    props.append(cc_plugin::field::nav::props_week());
    props.append(cc_plugin::field::nav::props_gpsFix());
    props.append(createProps_flags());
    props.append(cc_plugin::field::nav::props_ecefX());
    props.append(cc_plugin::field::nav::props_ecefY());
    props.append(cc_plugin::field::nav::props_ecefZ());
    props.append(cc_plugin::field::nav::props_pAcc());
    props.append(cc_plugin::field::nav::props_ecefVX());
    props.append(cc_plugin::field::nav::props_ecefVY());
    props.append(cc_plugin::field::nav::props_ecefVZ());
    props.append(cc_plugin::field::nav::props_sAcc());
    props.append(cc_plugin::field::nav::props_pDOP());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(cc_plugin::field::nav::props_numSV());
    props.append(cc_plugin::field::common::props_reserved(2));

    assert(props.size() == NavSol::FieldIdx_numOfValues);
    return props;
}

}  // namespace

NavSol::NavSol() = default;
NavSol::~NavSol() = default;

NavSol& NavSol::operator=(const NavSol&) = default;
NavSol& NavSol::operator=(NavSol&&) = default;

const char* NavSol::nameImpl() const
{
    static const char* Str = "NAV-SOL";
    return Str;
}

const QVariantList& NavSol::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

