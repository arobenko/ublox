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

#include "RxmImes.h"
#include "cc_plugin/field/rxm.h"
#include "cc_plugin/field/common.h"

template class ublox::message::RxmImes<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::RxmImes<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::RxmImes>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::RxmImesFields;

QVariantMap createProps_doppler()
{
    return
        cc::property::field::ForField<RxmImesFields::doppler>()
            .name("doppler")
            .scaledDecimals(9)
            .asMap();
}

QVariantMap createProps_pos1Floor()
{
    return
        cc::property::field::ForField<RxmImesFields::pos1Floor>()
            .name("pos1Floor")
            .serialisedHidden()
            .asMap();
}

QVariantMap createProps_pos1Lat()
{
    return
        cc::property::field::ForField<RxmImesFields::pos1Lat>()
            .name("pos1Lat")
            .serialisedHidden()
            .scaledDecimals(9)
            .asMap();
}

QVariantMap createProps_position1_1()
{
    typedef RxmImesFields::position1_1 Field;
    auto props =
        cc::property::field::ForField<Field>()
            .name("position1_1")
            .add(createProps_pos1Floor())
            .add(createProps_pos1Lat())
            .add(cc::property::field::IntValue().hidden().asMap());
    assert(props.members().size() == (int)Field::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_pos1Lon()
{
    return
        cc::property::field::ForField<RxmImesFields::pos1Lon>()
            .name("pos1Lon")
            .serialisedHidden()
            .scaledDecimals(9)
            .asMap();
}

QVariantMap createProps_pos1Flags()
{
    typedef RxmImesFields::pos1Flags Field;
    auto props =
        cc::property::field::ForField<Field>()
            .serialisedHidden()
            .add("pos1Valid");
    assert(props.bits().size() == (int)Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_position1_2()
{
    typedef RxmImesFields::position1_2 Field;
    auto props =
        cc::property::field::ForField<Field>()
            .name("position1_2")
            .add(createProps_pos1Lon())
            .add(createProps_pos1Flags());
    assert(props.members().size() == (int)Field::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_pos2Floor()
{
    return
        cc::property::field::ForField<RxmImesFields::pos2Floor>()
            .name("pos2Floor")
            .serialisedHidden()
            .asMap();
}

QVariantMap createProps_pos2Alt()
{
    return
        cc::property::field::ForField<RxmImesFields::pos2Alt>()
            .name("pos2Alt")
            .serialisedHidden()
            .asMap();
}

QVariantMap createProps_pos2Acc()
{
    typedef RxmImesFields::pos2Acc Field;
    auto props =
        cc::property::field::ForField<Field>()
            .name("pos2Acc")
            .serialisedHidden()
            .add("undef")
            .add("<7m")
            .add("<15m")
            .add(">15m");

    assert(props.values().size() == (int)Field::ValueType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_pos2Flags()
{
    typedef RxmImesFields::pos2Flags Field;
    auto props =
        cc::property::field::ForField<Field>()
            .serialisedHidden()
            .add("pos2Valid");
    assert(props.bits().size() == (int)Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_position2_1()
{
    typedef RxmImesFields::position2_1 Field;
    auto props =
        cc::property::field::ForField<Field>()
            .name("position2_1")
            .add(createProps_pos2Floor())
            .add(createProps_pos2Alt())
            .add(createProps_pos2Acc())
            .add(createProps_pos2Flags());
    assert(props.members().size() == (int)Field::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_lat()
{
    return
        cc::property::field::ForField<RxmImesFields::lat>()
            .name("lat")
            .scaledDecimals(9)
            .asMap();
}

QVariantMap createProps_lon()
{
    return
        cc::property::field::ForField<RxmImesFields::lon>()
            .name("lon")
            .scaledDecimals(9)
            .asMap();
}

QVariantMap createProps_shortId()
{
    return
        cc::property::field::ForField<RxmImesFields::shortId>()
            .name("shortId")
            .serialisedHidden()
            .asMap();
}

QVariantMap createProps_shortIdFlags()
{
    typedef RxmImesFields::shortIdFlags Field;
    auto props =
        cc::property::field::ForField<Field>()
            .serialisedHidden()
            .add("shortValid")
            .add("shortBoundary");
    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}


QVariantMap createProps_shortIdFrame()
{
    typedef RxmImesFields::shortIdFrame Field;
    auto props =
        cc::property::field::ForField<Field>()
            .name("shortIdFrame")
            .add(createProps_shortId())
            .add(createProps_shortIdFlags());
    assert(props.members().size() == (int)Field::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_mediumId_2()
{
    typedef RxmImesFields::mediumId_2 Field;
    auto props =
        cc::property::field::ForField<Field>()
            .name("mediumId_2")
            .add("mediumIdMSB")
            .add("mediumValid")
            .add("mediumboundary");
    assert(props.bits().size() == (int)Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_data()
{
    auto blockProps =
        cc::property::field::ForField<RxmImesFields::block>()
            .add(cc_plugin::field::common::props_reserved(2))
            .add(cc::property::field::ForField<RxmImesFields::txId>().name("txId").asMap())
            .add(cc_plugin::field::common::props_reserved(3))
            .add(cc::property::field::ForField<RxmImesFields::cno>().name("cno").asMap())
            .add(cc_plugin::field::common::props_reserved(4))
            .add(createProps_doppler())
            .add(createProps_position1_1())
            .add(createProps_position1_2())
            .add(createProps_position2_1())
            .add(createProps_lat())
            .add(createProps_lon())
            .add(createProps_shortIdFrame())
            .add(cc::property::field::ForField<RxmImesFields::mediumIdLSB>().name("mediumIdLSB").asMap())
            .add(createProps_mediumId_2());
    assert(blockProps.members().size() == RxmImesFields::block::FieldIdx_numOfValues);

    return
        cc::property::field::ForField<RxmImesFields::data<> >()
            .name("data")
            .serialisedHidden()
            .add(blockProps.asMap())
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<RxmImesFields::numTx>().name("numTx").readOnly().asMap());
    props.append(
        cc::property::field::ForField<RxmImesFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_data());

    assert(props.size() == RxmImes::FieldIdx_numOfValues);
    return props;
}

}  // namespace

RxmImes::RxmImes() = default;
RxmImes::~RxmImes() = default;

RxmImes& RxmImes::operator=(const RxmImes&) = default;
RxmImes& RxmImes::operator=(RxmImes&&) = default;

const char* RxmImes::nameImpl() const
{
    static const char* Str = "RXM-IMES";
    return Str;
}

const QVariantList& RxmImes::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

