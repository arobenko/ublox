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


#include "RxmEphPoll.h"

#include "cc_plugin/field/rxm.h"

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
    auto svidProps = cc_plugin::field::rxm::svidProperties();
    auto name = cc::Property::getName(svidProps).toString();
    auto optSvidProps =
        cc::Property::createPropertiesMap(
            name,
            std::move(svidProps));


    QVariantList props;
    props.append(std::move(optSvidProps));

    assert(props.size() == RxmEphPoll::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

RxmEphPoll::RxmEphPoll()
{
    setPoll();
}

const char* RxmEphPoll::nameImpl() const
{
    static const char* Str = "RXM-EPH (Poll)";
    return Str;
}

const QVariantList& RxmEphPoll::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

