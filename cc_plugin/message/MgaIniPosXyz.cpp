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

#include "MgaIniPosXyz.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MgaIniPosXyz<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MgaIniPosXyz<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MgaIniPosXyz>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MgaIniPosXyzFields;

QVariantMap createProps_ecef(QChar dir)
{
    return
        cc::property::field::ForField<MgaIniPosXyzFields::ecefX>()
            .name(QString("ecef%1").arg(dir))
            .asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MgaIniPosXyzFields::type>().name("type").readOnly().asMap());
    props.append(
        cc::property::field::ForField<MgaIniPosXyzFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(createProps_ecef('X'));
    props.append(createProps_ecef('Y'));
    props.append(createProps_ecef('Z'));
    props.append(
        cc::property::field::ForField<MgaIniPosXyzFields::posAcc>().name("posAcc").asMap());

    assert(props.size() == MgaIniPosXyz::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MgaIniPosXyz::MgaIniPosXyz() = default;
MgaIniPosXyz::~MgaIniPosXyz() = default;

MgaIniPosXyz& MgaIniPosXyz::operator=(const MgaIniPosXyz&) = default;
MgaIniPosXyz& MgaIniPosXyz::operator=(MgaIniPosXyz&&) = default;

const char* MgaIniPosXyz::nameImpl() const
{
    static const char* Str = "MGA-INI-POS_XYZ";
    return Str;
}

const QVariantList& MgaIniPosXyz::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

