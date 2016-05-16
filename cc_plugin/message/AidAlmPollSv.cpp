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


#include "AidAlmPollSv.h"

#include <cassert>

template class ublox::message::AidAlmPollSv<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::AidAlmPollSv<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::AidAlmPollSv>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::AidAlmPollSvFields;

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<AidAlmPollSvFields::svid>().name("svid").asMap());

    assert(props.size() == AidAlmPollSv::FieldIdx_numOfValues);
    return props;
}

}  // namespace

AidAlmPollSv::AidAlmPollSv() = default;
AidAlmPollSv::~AidAlmPollSv() = default;

AidAlmPollSv& AidAlmPollSv::operator=(const AidAlmPollSv&) = default;
AidAlmPollSv& AidAlmPollSv::operator=(AidAlmPollSv&&) = default;

const char* AidAlmPollSv::nameImpl() const
{
    static const char* Str = "AID-ALM (Poll SV)";
    return Str;
}

const QVariantList& AidAlmPollSv::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

