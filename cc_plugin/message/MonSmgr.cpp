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

#include "MonSmgr.h"
#include "cc_plugin/field/common.h"

template class ublox::message::MonSmgr<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::MonSmgr<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::MonSmgr>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::MonSmgrFields;

QVariantMap createProps_oscState(const QString& name)
{
    using Field = MonSmgrFields::intOscState;
    auto props =
        cc::property::field::ForField<Field>()
            .name(QString("%1OscState").arg(name))
            .serialisedHidden()
            .add("autonomous operation")
            .add("calibration ongoing")
            .add("steered by host")
            .add("idle state");

    assert(props.values().size() == (int)Field::ValueType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_oscFlags(const QString& name)
{
    using Field = MonSmgrFields::intOscFlags;
    auto props =
        cc::property::field::ForField<Field>()
            .serialisedHidden()
            .add(QString("%1OscCalib").arg(name))
            .add(QString("%1OscDisc").arg(name));

    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_osc(const QString& name)
{
    using Field = MonSmgrFields::intOsc;
    auto props =
        cc::property::field::ForField<Field>()
            .name(QString("%1Osc").arg(name))
            .add(createProps_oscState(name))
            .add(createProps_oscFlags(name));

    assert(props.members().size() == Field::FieldIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_discSrc()
{
    using Field = MonSmgrFields::discSrc;
    auto props =
        cc::property::field::ForField<Field>()
            .name("discSrc")
            .add("internal")
            .add("GNSS")
            .add("EXTINT0")
            .add("EXTINT1")
            .add("host internal")
            .add("host external");
    assert(props.values().size() == (int)Field::ValueType::NumOfValues);
    return props.asMap();
}

QVariantMap createProps_gnss()
{
    using Field = MonSmgrFields::gnss;
    auto props =
        cc::property::field::ForField<Field>()
            .name("gnss")
            .add("gnssAvail");
    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_extInt(int idx)
{
    using Field = MonSmgrFields::extInt0;
    auto props =
        cc::property::field::ForField<Field>()
            .name(QString("extInt%1").arg(idx))
            .add(QString("extInt%1Avail").arg(idx))
            .add(QString("extInt%1Type").arg(idx))
            .add(QString("extInt%1FeedBack").arg(idx));
    assert(props.bits().size() == Field::BitIdx_numOfValues);
    return props.asMap();
}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(
        cc::property::field::ForField<MonSmgrFields::version>().name("version").asMap());
    props.append(cc_plugin::field::common::props_reserved(1));
    props.append(
        cc::property::field::ForField<MonSmgrFields::iTOW>().name("iTOW").asMap());
    props.append(createProps_osc("int"));
    props.append(createProps_osc("ext"));
    props.append(createProps_discSrc());
    props.append(createProps_gnss());
    props.append(createProps_extInt(0));
    props.append(createProps_extInt(1));

    assert(props.size() == MonSmgr::FieldIdx_numOfValues);
    return props;
}

}  // namespace

MonSmgr::MonSmgr() = default;
MonSmgr::~MonSmgr() = default;

MonSmgr& MonSmgr::operator=(const MonSmgr&) = default;
MonSmgr& MonSmgr::operator=(MonSmgr&&) = default;

const char* MonSmgr::nameImpl() const
{
    static const char* Str = "MON-SMGR";
    return Str;
}

const QVariantList& MonSmgr::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

