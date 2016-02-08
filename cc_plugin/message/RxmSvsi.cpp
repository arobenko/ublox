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

QVariantMap createProps_svFlag()
{
    auto uraProps = cc::Property::createPropertiesMap("ura");
    cc::Property::setSerialisedHidden(uraProps);

    QVariantList bitNames;
    bitNames.append("healthy");
    bitNames.append("ephVal");
    bitNames.append("almVal");
    bitNames.append("notAvail");
    assert(bitNames.size() == ublox::message::RxmSvsiFields::svFlagBits_numOfValues);
    auto flagsProps = cc::Property::createPropertiesMap(QString(), std::move(bitNames));
    cc::Property::setSerialisedHidden(flagsProps);

    QVariantList membersData;
    membersData.append(std::move(uraProps));
    membersData.append(std::move(flagsProps));
    assert(membersData.size() == ublox::message::RxmSvsiFields::svFlag_numOfValues);
    return cc::Property::createPropertiesMap("svFlag", std::move(membersData));
}

QVariantMap createProps_age()
{
    auto createAgePropsFunc =
        [](const QString& name) -> QVariantMap
        {
            auto props = cc::Property::createPropertiesMap(name);
            cc::Property::setSerialisedHidden(props);
            return props;
        };

    QVariantList membersData;
    membersData.append(createAgePropsFunc("almAge"));
    membersData.append(createAgePropsFunc("ephAge"));
    assert(membersData.size() == ublox::message::RxmSvsiFields::age_numOfValues);

    return cc::Property::createPropertiesMap("age", std::move(membersData));
}

QVariantMap createProps_data()
{
    QVariantList membersData;
    membersData.append(cc_plugin::field::rxm::props_svid());
    membersData.append(createProps_svFlag());
    membersData.append(cc::Property::createPropertiesMap("azim"));
    membersData.append(cc::Property::createPropertiesMap("elev"));
    membersData.append(createProps_age());
    assert(membersData.size() == ublox::message::RxmSvsiFields::block_numOfValues);

    QVariantMap elementProps = cc::Property::createPropertiesMap("block", std::move(membersData));
    auto props = cc::Property::createPropertiesMap("data", std::move(elementProps));
    cc::Property::setSerialisedHidden(props);
    return props;
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::rxm::props_iTOW());
    props.append(cc_plugin::field::rxm::props_week());
    props.append(cc::Property::createPropertiesMap("numVis"));
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

