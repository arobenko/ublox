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

#include "MonIo.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MonIo<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MonIo<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MonIo>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MonIoFields;

QVariantMap createProps_data()
{
    cc::property::field::ForField<MonIoFields::block> blockProps;
    blockProps
        .add(cc::property::field::ForField<MonIoFields::rxBytes>().name("rxBytes").asMap())
        .add(cc::property::field::ForField<MonIoFields::txBytes>().name("txBytes").asMap())
        .add(cc::property::field::ForField<MonIoFields::parityErrs>().name("parityErrs").asMap())
        .add(cc::property::field::ForField<MonIoFields::framingErrs>().name("framingErrs").asMap())
        .add(cc::property::field::ForField<MonIoFields::overrunErrs>().name("overrunErrs").asMap())
        .add(cc::property::field::ForField<MonIoFields::breakCond>().name("breakCond").asMap())
        .add(cc::property::field::ForField<MonIoFields::rxBusy>().name("rxBusy").asMap())
        .add(cc::property::field::ForField<MonIoFields::txBusy>().name("txBusy").asMap())
        .add(cc_plugin::field::common::props_reserved(1));
    assert(blockProps.members().size() == MonIoFields::block::FieldIdx_numOfValues);

    return
        cc::property::field::ForField<MonIoFields::data>()
            .name("data")
            .add(blockProps.asMap())
            .serialisedHidden()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_data());

    assert(props.size() == MonIo::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MonIo::MonIo() = default;
MonIo::~MonIo() = default;

MonIo& MonIo::operator=(const MonIo&) = default;
MonIo& MonIo::operator=(MonIo&&) = default;

const char* MonIo::nameImpl() const
{
    static const char* Str = "MON-IO";
    return Str;
}

const QVariantList& MonIo::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

