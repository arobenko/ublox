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

#include "MonRxbuf.h"

template class ublox::message::MonRxbuf<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MonRxbuf<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MonRxbuf>;

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
    cc::property::field::ArrayList props;
    props.name(name).serialisedHidden();
    for (auto i = 0; i < 6; ++i) {
        props.add(
            cc::property::field::IntValue().name(QString("%1").arg(i)).asMap());
    }
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_list("pending"));
    props.append(createProps_list("usage"));
    props.append(createProps_list("peakUsage"));

    assert(props.size() == MonRxbuf::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MonRxbuf::MonRxbuf() = default;
MonRxbuf::~MonRxbuf() = default;

MonRxbuf& MonRxbuf::operator=(const MonRxbuf&) = default;
MonRxbuf& MonRxbuf::operator=(MonRxbuf&&) = default;

const char* MonRxbuf::nameImpl() const
{
    static const char* Str = "MON-RXBUF";
    return Str;
}

const QVariantList& MonRxbuf::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

