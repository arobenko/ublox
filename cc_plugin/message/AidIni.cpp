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

QVariantMap createProps_optNumeric(const char* name, int decimals = 0)
{
    auto valProps = cc::Property::createPropertiesMap(name);
    if (0 < decimals) {
        cc::Property::setDisplayScaled(valProps);
        cc::Property::setFloatDecimals(valProps, 7);
    }
    auto props = cc::Property::createPropertiesMap(name, std::move(valProps));
    cc::Property::setUncheckable(props);
    return props;
}

QVariantMap createProps_tmCfg()
{
    QVariantList bitNames;

    auto fillUntilFunc =
        [&bitNames](int idx)
        {
            while (bitNames.size() < idx) {
                bitNames.append(QVariant());
            }
        };

    fillUntilFunc(ublox::message::AidIniFields::tmCfg_fEdge);
    bitNames.append("fEdge");
    fillUntilFunc(ublox::message::AidIniFields::tmCfg_tm1);
    bitNames.append("tm1");
    fillUntilFunc(ublox::message::AidIniFields::tmCfg_f1);
    bitNames.append("f1");
    assert(bitNames.size() == ublox::message::AidIniFields::tmCfg_numOfValues);
    return cc::Property::createPropertiesMap("tmCfg", std::move(bitNames));
}

QVariantMap createProps_date()
{
    auto monthProps = cc::Property::createPropertiesMap("month");
    cc::Property::setSerialisedHidden(monthProps);

    auto yearProps = cc::Property::createPropertiesMap("year");
    cc::Property::setSerialisedHidden(yearProps);

    QVariantList membersData;
    membersData.append(std::move(monthProps));
    membersData.append(std::move(yearProps));
    assert(membersData.size() == ublox::message::AidIniFields::date_numOfValues);
    static const QString Name("date");
    auto valProps = cc::Property::createPropertiesMap(Name, std::move(membersData));
    auto props = cc::Property::createPropertiesMap(Name, std::move(valProps));
    cc::Property::setUncheckable(props);
    return props;
}

QVariantMap createProps_time()
{
    auto secProps = cc::Property::createPropertiesMap("second");
    cc::Property::setSerialisedHidden(secProps);

    auto minProps = cc::Property::createPropertiesMap("minute");
    cc::Property::setSerialisedHidden(minProps);

    auto hourProps = cc::Property::createPropertiesMap("hour");
    cc::Property::setSerialisedHidden(hourProps);

    auto dayProps = cc::Property::createPropertiesMap("day");
    cc::Property::setSerialisedHidden(dayProps);

    QVariantList membersData;
    membersData.append(std::move(secProps));
    membersData.append(std::move(minProps));
    membersData.append(std::move(hourProps));
    membersData.append(std::move(dayProps));
    assert(membersData.size() == ublox::message::AidIniFields::time_numOfValues);
    static const QString Name("time");
    auto valProps = cc::Property::createPropertiesMap(Name, std::move(membersData));
    auto props = cc::Property::createPropertiesMap(Name, std::move(valProps));
    cc::Property::setUncheckable(props);
    return props;
}

QVariantMap createProps_flags()
{
    QVariantList bitNames;
    bitNames.append("pos");
    bitNames.append("time");
    bitNames.append("clockD");
    bitNames.append("tp");
    bitNames.append("clockF");
    bitNames.append("lla");
    bitNames.append("altInv");
    bitNames.append("prevTm");
    bitNames.append(QVariant());
    bitNames.append(QVariant());
    bitNames.append("utc");
    assert(bitNames.size() == ublox::message::AidIniFields::flags_numOfValues);
    return cc::Property::createPropertiesMap("flags", std::move(bitNames));
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
    props.append(cc::Property::createPropertiesMap("posAcc"));
    props.append(createProps_tmCfg());
    props.append(createProps_optNumeric("wno"));
    props.append(createProps_date());
    props.append(createProps_optNumeric("tow"));
    props.append(createProps_time());
    props.append(cc::Property::createPropertiesMap("towNs"));
    props.append(cc::Property::createPropertiesMap("tAccMs"));
    props.append(cc::Property::createPropertiesMap("tAccNs"));
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

