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


#include "RxmAlmPollSv.h"

#include "cc_plugin/field/rxm.h"

template class ublox::message::RxmAlmPollSv<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::RxmAlmPollSv<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::RxmAlmPollSv>;

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
    props.append(cc_plugin::field::rxm::props_svid());

    assert(props.size() == RxmAlmPollSv::FieldIdx_numOfValues);
    return props;
}

}  // namespace

RxmAlmPollSv::RxmAlmPollSv() = default;
RxmAlmPollSv::~RxmAlmPollSv() = default;

RxmAlmPollSv& RxmAlmPollSv::operator=(const RxmAlmPollSv&) = default;
RxmAlmPollSv& RxmAlmPollSv::operator=(RxmAlmPollSv&&) = default;

const char* RxmAlmPollSv::nameImpl() const
{
    static const char* Str = "RXM-ALM (Poll SV)";
    return Str;
}

const QVariantList& RxmAlmPollSv::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

