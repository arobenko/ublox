//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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

#include "MonTxbuf.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MonTxbuf<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MonTxbuf<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MonTxbuf>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MonTxbufFields;

QVariantMap createProps_list(const char* name)
{
    cc::property::field::ArrayList props;
    props.name(name).serialisedHidden();
    for (auto i = 0; i < 6; ++i) {
        props.add(
            cc::property::field::IntValue().name(QString("%1").arg(i)).asMap());
    }
    return props.asMap();
}

QVariantMap createProps_errors()
{
    cc::property::field::ForField<MonTxbufFields::limit> limitProps;
    limitProps.name("limit").serialisedHidden();

    cc::property::field::ForField<MonTxbufFields::errorsBits> bitsProps;
    bitsProps.add("mem")
             .add("alloc")
             .serialisedHidden();
    assert(bitsProps.bits().size() == MonTxbufFields::errorsBits::BitIdx_numOfValues);

    cc::property::field::ForField<MonTxbufFields::errors> props;
    props.name("errors")
         .add(limitProps.asMap())
         .add(bitsProps.asMap());
    assert(props.members().size() == MonTxbufFields::errors::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_list("pending"));
    props.append(createProps_list("usage"));
    props.append(createProps_list("peakUsage"));
    props.append(
        cc::property::field::ForField<MonTxbufFields::tUsage>().name("tUsage").asMap());
    props.append(
        cc::property::field::ForField<MonTxbufFields::tPeakUsage>().name("tPeakUsage").asMap());
    props.append(createProps_errors());
    props.append(cc_plugin::field::common::props_reserved(1));
    assert(props.size() == MonTxbuf::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MonTxbuf::MonTxbuf() = default;
MonTxbuf::~MonTxbuf() = default;

MonTxbuf& MonTxbuf::operator=(const MonTxbuf&) = default;
MonTxbuf& MonTxbuf::operator=(MonTxbuf&&) = default;

const char* MonTxbuf::nameImpl() const
{
    static const char* Str = "MON-TXBUF";
    return Str;
}

const QVariantList& MonTxbuf::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

