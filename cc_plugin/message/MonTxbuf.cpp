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

QVariantMap createProps_list(const char* name)
{
    QVariantList elemProps;
    for (auto i = 0; i < 6; ++i) {
        elemProps.append(cc::Property::createPropertiesMap(QString("%1").arg(i)));
    }
    auto props = cc::Property::createPropertiesMap(name, std::move(elemProps));
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantMap createProps_errors()
{
    auto limitProps = cc::Property::createPropertiesMap("limit");
    cc::Property::setSerialisedHidden(limitProps);

    QVariantList bitNames;
    bitNames.append("mem");
    bitNames.append("alloc");
    assert(bitNames.size() == ublox::message::MonTxbufFields::errorsBits_numOfValues);
    auto bitsProps = cc::Property::createPropertiesMap(QString(), std::move(bitNames));
    cc::Property::setSerialisedHidden(bitsProps);

    QVariantList membersData;
    membersData.append(std::move(limitProps));
    membersData.append(std::move(bitsProps));
    assert(membersData.size() == ublox::message::MonTxbufFields::errors_numOfValues);
    return cc::Property::createPropertiesMap("errors", std::move(membersData));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_list("pending"));
    props.append(createProps_list("usage"));
    props.append(createProps_list("peakUsage"));
    props.append(cc::Property::createPropertiesMap("tUsage"));
    props.append(cc::Property::createPropertiesMap("tPeakUsage"));
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

