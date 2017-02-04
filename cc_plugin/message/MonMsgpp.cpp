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

#include "MonMsgpp.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MonMsgpp<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MonMsgpp<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MonMsgpp>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MonMsgppFields;

QVariantMap createProps_msgX(int idx)
{
    cc::property::field::ForField<MonMsgppFields::msg1<> > props;
    props.name(QString("msg%1").arg(idx)).serialisedHidden();
    for (auto i = 0; i < 8; ++i) {
        props.add(
            cc::property::field::IntValue().name(QString("%1").arg(i)).asMap());
    }
    return props.asMap();
}

QVariantMap createProps_skipped()
{
    cc::property::field::ForField<MonMsgppFields::skipped<> > props;
    props.name("skipped").serialisedHidden();
    for (auto i = 0; i < 6; ++i) {
        props.add(
            cc::property::field::IntValue().name(QString("%1").arg(i)).asMap());
    }
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_msgX(1));
    props.append(createProps_msgX(2));
    props.append(createProps_msgX(3));
    props.append(createProps_msgX(4));
    props.append(createProps_msgX(5));
    props.append(createProps_msgX(6));
    props.append(createProps_skipped());

    assert(props.size() == MonMsgpp::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MonMsgpp::MonMsgpp() = default;
MonMsgpp::~MonMsgpp() = default;

MonMsgpp& MonMsgpp::operator=(const MonMsgpp&) = default;
MonMsgpp& MonMsgpp::operator=(MonMsgpp&&) = default;

const char* MonMsgpp::nameImpl() const
{
    static const char* Str = "MON-MSGPP";
    return Str;
}

const QVariantList& MonMsgpp::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

