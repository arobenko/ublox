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

#include "MonPatch.h"

#include <cassert>

#include "cc_plugin/field/common.h"

template class ublox::message::MonPatch<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MonPatch<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MonPatch>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MonPatchFields;

QVariantMap createProps_activated()
{
    auto props =
        cc::property::field::ForField<MonPatchFields::activated>()
            .add("activated")
            .serialisedHidden();
    assert(props.bits().size() == MonPatchFields::activated::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_location()
{
    auto props =
        cc::property::field::ForField<MonPatchFields::location>()
            .name("location")
            .serialisedHidden()
            .add("eFuse")
            .add("ROM")
            .add("BBR")
            .add("file system");
    assert(props.values().size() == (int)MonPatchFields::Location::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_patchInfo()
{
    auto props =
        cc::property::field::ForField<MonPatchFields::patchInfo>()
            .name("patchInfo")
            .add(createProps_activated())
            .add(createProps_location())
            .add(cc::property::field::IntValue().hidden().asMap());

    assert(props.members().size() == MonPatchFields::patchInfo::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_data()
{
    auto blockProps =
        cc::property::field::ForField<MonPatchFields::block>()
            .add(createProps_patchInfo())
            .add(cc::property::field::ForField<MonPatchFields::comparatorNumber>().name("comparatorNumber").asMap())
            .add(cc::property::field::ForField<MonPatchFields::patchAddress>().name("patchAddress").asMap())
            .add(cc::property::field::ForField<MonPatchFields::patchData>().name("patchData").asMap());
    assert(blockProps.members().size() == MonPatchFields::block::FieldIdx_numOfValues);

    return
        cc::property::field::ForField<MonPatchFields::data<> >()
            .name("data")
            .add(blockProps.asMap())
            .serialisedHidden()
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MonPatchFields::version>().name("version").asMap());
    props.append(
        cc::property::field::ForField<MonPatchFields::nEntries>().name("nEntries").readOnly().asMap());
    props.append(createProps_data());

    assert(props.size() == MonPatch::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MonPatch::MonPatch() = default;
MonPatch::~MonPatch() = default;

MonPatch& MonPatch::operator=(const MonPatch&) = default;
MonPatch& MonPatch::operator=(MonPatch&&) = default;

const char* MonPatch::nameImpl() const
{
    static const char* Str = "MON-PATCH";
    return Str;
}

const QVariantList& MonPatch::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

