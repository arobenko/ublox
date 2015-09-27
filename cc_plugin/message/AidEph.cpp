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

#include <cassert>

#include "AidEph.h"

template class ublox::message::AidEph<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::AidEph<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::AidEph>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantMap createProps_sfxd(int sfIdx)
{
    static const auto NumOfElems =
        ublox::message::AidEphField_sf1d::Field::ParsedOptions::SequenceFixedSize;
    QVariantList elemsProps;
    for (auto idx = 0U; idx < NumOfElems; ++idx) {
        elemsProps.append(cc::Property::createPropertiesMap(QString("%1").arg(idx, 1, 10, QChar('0'))));
    }

    auto name = QString("sf%1d").arg(sfIdx, 1, 10, QChar('0'));
    auto listProps =
        cc::Property::createPropertiesMap(
            name,
            std::move(elemsProps));
    cc::Property::setSerialisedHidden(listProps);

    auto props = cc::Property::createPropertiesMap(name, std::move(listProps));
    cc::Property::setUncheckable(props);
    return props;
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc::Property::createPropertiesMap("svid"));
    props.append(cc::Property::createPropertiesMap("how"));
    props.append(createProps_sfxd(1));
    props.append(createProps_sfxd(2));
    props.append(createProps_sfxd(3));

    assert(props.size() == AidEph::FieldIdx_numOfValues);
    return props;
}

}  // namespace

AidEph::AidEph() = default;
AidEph::~AidEph() = default;

AidEph& AidEph::operator=(const AidEph&) = default;
AidEph& AidEph::operator=(AidEph&&) = default;

const char* AidEph::nameImpl() const
{
    static const char* Str = "AID-EPH";
    return Str;
}

const QVariantList& AidEph::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

