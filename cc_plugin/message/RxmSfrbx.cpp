//
// Copyright 2017 (C). Alex Robenko. All rights reserved.
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

#include "RxmSfrbx.h"
#include "cc_plugin/field/rxm.h"
#include "cc_plugin/field/common.h"

template class ublox::message::RxmSfrbx<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::RxmSfrbx<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::RxmSfrbx>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::RxmSfrbxFields;

QVariantMap createProps_dwrd()
{
    auto props =
        cc::property::field::ForField<RxmSfrbxFields::dwrd<> >()
            .name("dwrd")
            .serialisedHidden();

    for (auto idx = 0U; idx < 16U; ++idx) {
        props.add(
            cc::property::field::IntValue()
                .name(QString("%1").arg(idx, 1, 10, QChar('0')))
                .asMap());
    }

    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::common::props_gnssId());
    props.append(
        cc::property::field::ForField<RxmSfrbxFields::svId>().name("svId").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<RxmSfrbxFields::freqId>().name("freqId").asMap());
    props.append(
        cc::property::field::ForField<RxmSfrbxFields::numWords>().name("numWords").readOnly().asMap());
    props.append(
        cc::property::field::ForField<RxmSfrbxFields::chn>().name("chn").asMap());
    props.append(
        cc::property::field::ForField<RxmSfrbxFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(2));
    props.append(createProps_dwrd());

    assert(props.size() == RxmSfrbx::FieldIdx_numOfValues);
    return props;
}

}  // namespace

RxmSfrbx::RxmSfrbx() = default;
RxmSfrbx::~RxmSfrbx() = default;

RxmSfrbx& RxmSfrbx::operator=(const RxmSfrbx&) = default;
RxmSfrbx& RxmSfrbx::operator=(RxmSfrbx&&) = default;

const char* RxmSfrbx::nameImpl() const
{
    static const char* Str = "RXM-SFRBX";
    return Str;
}

const QVariantList& RxmSfrbx::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

