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


#include "RxmPmreq.h"

#include <cassert>

template class ublox::message::RxmPmreq<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::RxmPmreq<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::RxmPmreq>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_flags()
{
    QVariantList bitNames;
    bitNames.append(QVariant());
    bitNames.append("backup");
    assert(bitNames.size() == ublox::message::RxmPmreqFields::flags_numOfValues);
    return cc::Property::createPropertiesMap("flags", std::move(bitNames));
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::Property::createPropertiesMap("duration"));
    props.append(createProps_flags());
    assert(props.size() == RxmPmreq::FieldIdx_numOfValues);
    return props;
}

}  // namespace

RxmPmreq::RxmPmreq() = default;
RxmPmreq::~RxmPmreq() = default;

RxmPmreq& RxmPmreq::operator=(const RxmPmreq&) = default;
RxmPmreq& RxmPmreq::operator=(RxmPmreq&&) = default;

const char* RxmPmreq::nameImpl() const
{
    static const char* Str = "RXM-PMREQ";
    return Str;
}

const QVariantList& RxmPmreq::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

