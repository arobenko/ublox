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

#include "RxmSvsi.h"
#include "cc_plugin/field/rxm.h"
#include "cc_plugin/field/common.h"

template class ublox::message::RxmSvsi<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::RxmSvsi<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::RxmSvsi>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::RxmSvsiFields;

QVariantMap createProps_svFlag()
{
    cc::property::field::ForField<RxmSvsiFields::ura> uraProps;
    uraProps.name("ura").serialisedHidden();

    cc::property::field::ForField<RxmSvsiFields::svFlagBits> svFlagBitsProps;
    svFlagBitsProps.add("healthy")
                   .add("ephVal")
                   .add("almVal")
                   .add("notAvail")
                   .serialisedHidden();

    assert(svFlagBitsProps.bits().size() == RxmSvsiFields::svFlagBits::BitIdx_numOfValues);

    cc::property::field::ForField<RxmSvsiFields::svFlag> props;
    props.name("svFlag")
         .add(uraProps.asMap())
         .add(svFlagBitsProps.asMap());

    assert(props.members().size() == RxmSvsiFields::svFlag::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_age()
{
    auto createAgePropsFunc =
        [](const QString& name) -> QVariantMap
        {
            return
                cc::property::field::ForField<RxmSvsiFields::almAge>()
                    .name(name)
                    .serialisedHidden()
                    .asMap();
        };

    cc::property::field::ForField<RxmSvsiFields::age> props;
    props.name("age")
         .add(createAgePropsFunc("almAge"))
         .add(createAgePropsFunc("ephAge"));
    assert(props.members().size() == RxmSvsiFields::age::FieldIdx_numOfValues);

    return props.asMap();
}

QVariantMap createProps_data()
{
    cc::property::field::ForField<RxmSvsiFields::block> blockProps;
    blockProps.add(cc_plugin::field::rxm::props_svid())
              .add(createProps_svFlag())
              .add(cc::property::field::ForField<RxmSvsiFields::azim>().name("azim").asMap())
              .add(cc::property::field::ForField<RxmSvsiFields::elev>().name("elev").asMap())
              .add(createProps_age());
    assert(blockProps.members().size() == RxmSvsiFields::block::FieldIdx_numOfValues);

    return
        cc::property::field::ForField<RxmSvsiFields::data<> >()
            .name("data")
            .serialisedHidden()
            .add(blockProps.asMap())
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::rxm::props_iTOW());
    props.append(cc_plugin::field::rxm::props_week());
    props.append(cc::property::field::ForField<RxmSvsiFields::numVis>().name("numVis").asMap());
    props.append(cc_plugin::field::rxm::props_numSV());
    props.append(createProps_data());

    assert(props.size() == RxmSvsi::FieldIdx_numOfValues);
    return props;
}

}  // namespace

RxmSvsi::RxmSvsi() = default;
RxmSvsi::~RxmSvsi() = default;

RxmSvsi& RxmSvsi::operator=(const RxmSvsi&) = default;
RxmSvsi& RxmSvsi::operator=(RxmSvsi&&) = default;

const char* RxmSvsi::nameImpl() const
{
    static const char* Str = "RXM-SVSI";
    return Str;
}

const QVariantList& RxmSvsi::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

