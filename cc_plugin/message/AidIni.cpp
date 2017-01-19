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

#include "AidIni.h"

template class ublox::message::AidIni<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::AidIni<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::AidIni>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

using ublox::message::AidIniFields;

QVariantMap createProps_optNumeric(const char* name, int decimals = 0)
{
    cc::property::field::IntValue valProps;
    valProps.name(name);
    if (0 < decimals) {
        valProps.scaledDecimals(decimals);
    }

    return
        cc::property::field::Optional()
            .name(name)
            .field(valProps.asMap())
            .uncheckable()
            .asMap();
}

QVariantMap createProps_tmCfg()
{
    cc::property::field::ForField<AidIniFields::tmCfg> props;
    props.name("tmCfg")
         .add(AidIniFields::tmCfg::BitIdx_fEdge, "fEdge")
         .add(AidIniFields::tmCfg::BitIdx_tm1, "tm1")
         .add(AidIniFields::tmCfg::BitIdx_f1, "f1");
    assert(props.bits().size() == AidIniFields::tmCfg::BitIdx_numOfValues);
    return props.asMap();
}

QVariantMap createProps_date()
{
    cc::property::field::IntValue monthProps;
    monthProps.name("month").serialisedHidden();

    cc::property::field::IntValue yearProps;
    yearProps.name("year").serialisedHidden();

    static const QString Name("date");
    cc::property::field::Bitfield bitfieldProps;
    bitfieldProps.add(monthProps.asMap())
                 .add(yearProps.asMap())
                 .name(Name);
    assert(bitfieldProps.members().size() == AidIniFields::dateBitfield::FieldIdx_numOfValues);

    return
        cc::property::field::ForField<AidIniFields::date>()
            .name(Name)
            .field(bitfieldProps.asMap())
            .uncheckable()
            .asMap();
}

QVariantMap createProps_time()
{
    cc::property::field::IntValue secProps;
    secProps.name("second").serialisedHidden();

    cc::property::field::IntValue minProps;
    minProps.name("minute").serialisedHidden();

    cc::property::field::IntValue hourProps;
    hourProps.name("hour").serialisedHidden();

    cc::property::field::IntValue dayProps;
    dayProps.name("day").serialisedHidden();

    static const QString Name("time");
    cc::property::field::Bitfield bitfieldProps;
    bitfieldProps.name(Name)
                 .add(secProps.asMap())
                 .add(minProps.asMap())
                 .add(hourProps.asMap())
                 .add(dayProps.asMap());
    assert(bitfieldProps.members().size() == AidIniFields::timeBitfield::FieldIdx_numOfValues);

    return
        cc::property::field::ForField<AidIniFields::time>()
            .name(Name)
            .field(bitfieldProps.asMap())
            .uncheckable()
            .asMap();
}

QVariantMap createProps_flags()
{
    cc::property::field::ForField<AidIniFields::flags> props;
    props.name("flags")
         .add("pos")
         .add("time")
         .add("clockD")
         .add("tp")
         .add("clockF")
         .add("lla")
         .add("altInv")
         .add("prevTm")
         .add(AidIniFields::flags::BitIdx_utc, "utc");
    assert(props.bits().size() == AidIniFields::flags::BitIdx_numOfValues);
    return props.asMap();

}

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(createProps_optNumeric("ecefX"));
    props.append(createProps_optNumeric("lat", 7));
    props.append(createProps_optNumeric("ecefY"));
    props.append(createProps_optNumeric("lon", 7));
    props.append(createProps_optNumeric("ecefZ"));
    props.append(createProps_optNumeric("alt"));
    props.append(
        cc::property::field::ForField<AidIniFields::posAcc>().name("posAcc").asMap());
    props.append(createProps_tmCfg());
    props.append(createProps_optNumeric("wno"));
    props.append(createProps_date());
    props.append(createProps_optNumeric("tow"));
    props.append(createProps_time());
    props.append(
        cc::property::field::ForField<AidIniFields::towNs>().name("towNs").asMap());
    props.append(
        cc::property::field::ForField<AidIniFields::tAccMs>().name("tAccMs").asMap());
    props.append(
        cc::property::field::ForField<AidIniFields::tAccNs>().name("tAccNs").asMap());
    props.append(createProps_optNumeric("clkD"));
    props.append(createProps_optNumeric("freq", 2));
    props.append(createProps_optNumeric("clkDAcc"));
    props.append(createProps_optNumeric("freqAcc"));
    props.append(createProps_flags());
    assert(props.size() == AidIni::FieldIdx_numOfValues);
    return props;
}

}  // namespace

AidIni::AidIni() = default;
AidIni::~AidIni() = default;

AidIni& AidIni::operator=(const AidIni&) = default;
AidIni& AidIni::operator=(AidIni&&) = default;


const char* AidIni::nameImpl() const
{
    static const char* Str = "AID-INI";
    return Str;
}

const QVariantList& AidIni::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

