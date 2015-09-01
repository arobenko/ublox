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


#include "RxmEphPollSv.h"

#include "cc_plugin/field/rxm.h"

template class ublox::message::RxmEphPollSv<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::RxmEphPollSv<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::RxmEphPollSv>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::Property::createPropertiesMap("svid"));

    assert(props.size() == RxmEphPollSv::FieldIdx_numOfValues);
    return props;
}

}  // namespace

RxmEphPollSv::RxmEphPollSv() = default;
RxmEphPollSv::~RxmEphPollSv() = default;

RxmEphPollSv& RxmEphPollSv::operator=(const RxmEphPollSv&) = default;
RxmEphPollSv& RxmEphPollSv::operator=(RxmEphPollSv&&) = default;

const char* RxmEphPollSv::nameImpl() const
{
    static const char* Str = "RXM-EPH (Poll SV)";
    return Str;
}

const QVariantList& RxmEphPollSv::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

