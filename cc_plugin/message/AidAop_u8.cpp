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

#include "cc_plugin/field/common.h"
#include "AidAop_u8.h"

template class ublox::message::AidAop_u8<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::AidAop_u8<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::AidAop_u8>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::AidAopFields_u8;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(field::common::props_gnssId());
    props.append(field::common::props_svid());
    props.append(field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<AidAopFields_u8::data<> >().name("data").asMap());

    assert(props.size() == AidAop_u8::FieldIdx_numOfValues);
    return props;
}

}  // namespace

AidAop_u8::AidAop_u8() = default;
AidAop_u8::~AidAop_u8() = default;

AidAop_u8& AidAop_u8::operator=(const AidAop_u8&) = default;
AidAop_u8& AidAop_u8::operator=(AidAop_u8&&) = default;


const char* AidAop_u8::nameImpl() const
{
    static const char* Str = "AID-AOP (ublox-8)";
    return Str;
}

const QVariantList& AidAop_u8::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

