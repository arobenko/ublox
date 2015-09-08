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

#include "MsgId.h"

#include "comms_champion/comms_champion.h"
#include "ublox/MsgId.h"

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace field
{

namespace
{

QVariantMap createMsgIdProperties()
{
    QVariantList enumValues;
    cc::Property::appendEnumValue(enumValues, "NAV-POSECEF", MsgId_NAV_POSECEF);
    cc::Property::appendEnumValue(enumValues, "NAV-POSLLH", MsgId_NAV_POSLLH);
    cc::Property::appendEnumValue(enumValues, "NAV-STATUS", MsgId_NAV_STATUS);
    cc::Property::appendEnumValue(enumValues, "NAV-DOP", MsgId_NAV_DOP);
    cc::Property::appendEnumValue(enumValues, "NAV-SOL", MsgId_NAV_SOL);
    cc::Property::appendEnumValue(enumValues, "NAV-SOL", MsgId_NAV_PVT);
    cc::Property::appendEnumValue(enumValues, "NAV-VELECEF", MsgId_NAV_VELECEF);
    cc::Property::appendEnumValue(enumValues, "NAV-VELNED", MsgId_NAV_VELNED);
    cc::Property::appendEnumValue(enumValues, "NAV-TIMEGPS", MsgId_NAV_TIMEGPS);
    cc::Property::appendEnumValue(enumValues, "NAV-TIMEUTC", MsgId_NAV_TIMEUTC);
    cc::Property::appendEnumValue(enumValues, "NAV-CLOCK", MsgId_NAV_CLOCK);
    cc::Property::appendEnumValue(enumValues, "NAV-SVINFO", MsgId_NAV_SVINFO);
    cc::Property::appendEnumValue(enumValues, "NAV-DGPS", MsgId_NAV_DGPS);
    cc::Property::appendEnumValue(enumValues, "NAV-SBAS", MsgId_NAV_SBAS);
    cc::Property::appendEnumValue(enumValues, "NAV-EKFSTATUS", MsgId_NAV_EKFSTATUS);

    cc::Property::appendEnumValue(enumValues, "RXM-RAW", MsgId_RXM_RAW);
    cc::Property::appendEnumValue(enumValues, "RXM-SFRB", MsgId_RXM_SFRB);
    cc::Property::appendEnumValue(enumValues, "RXM-SVSI", MsgId_RXM_SVSI);
    cc::Property::appendEnumValue(enumValues, "RXM-ALM", MsgId_RXM_ALM);
    cc::Property::appendEnumValue(enumValues, "RXM-EPH", MsgId_RXM_EPH);
    cc::Property::appendEnumValue(enumValues, "RXM-POSREQ", MsgId_RXM_PMREQ);

    cc::Property::appendEnumValue(enumValues, "INF-ERROR", MsgId_INF_ERROR);
    cc::Property::appendEnumValue(enumValues, "INF-WARNING", MsgId_INF_WARNING);
    cc::Property::appendEnumValue(enumValues, "INF-NOTICE", MsgId_INF_NOTICE);
    cc::Property::appendEnumValue(enumValues, "INF-TEST", MsgId_INF_TEST);
    cc::Property::appendEnumValue(enumValues, "INF-DEBUG", MsgId_INF_DEBUG);

    cc::Property::appendEnumValue(enumValues, "ACK-NAK", MsgId_ACK_NAK);
    cc::Property::appendEnumValue(enumValues, "ACK-ACK", MsgId_ACK_ACK);

    cc::Property::appendEnumValue(enumValues, "CFG-PRT", MsgId_CFG_PRT);
    cc::Property::appendEnumValue(enumValues, "CFG-MSG", MsgId_CFG_MSG);
    cc::Property::appendEnumValue(enumValues, "CFG-INF", MsgId_CFG_INF);
    cc::Property::appendEnumValue(enumValues, "CFG-RST", MsgId_CFG_RST);
    cc::Property::appendEnumValue(enumValues, "CFG-DAT", MsgId_CFG_DAT);
    cc::Property::appendEnumValue(enumValues, "CFG-TP", MsgId_CFG_TP);
    cc::Property::appendEnumValue(enumValues, "CFG-RATE", MsgId_CFG_RATE);
    cc::Property::appendEnumValue(enumValues, "CFG-CFG", MsgId_CFG_CFG);
    cc::Property::appendEnumValue(enumValues, "CFG-FXN", MsgId_CFG_FXN);
    cc::Property::appendEnumValue(enumValues, "CFG-RXM", MsgId_CFG_RXM);
    cc::Property::appendEnumValue(enumValues, "CFG-EKF", MsgId_CFG_EKF);
    cc::Property::appendEnumValue(enumValues, "CFG-ANT", MsgId_CFG_ANT);
    cc::Property::appendEnumValue(enumValues, "CFG-SBAS", MsgId_CFG_SBAS);
    cc::Property::appendEnumValue(enumValues, "CFG-NMEA", MsgId_CFG_NMEA);
    cc::Property::appendEnumValue(enumValues, "CFG-TM2", MsgId_CFG_TM2);
    cc::Property::appendEnumValue(enumValues, "CFG-NAV2", MsgId_CFG_NAV2);
    cc::Property::appendEnumValue(enumValues, "CFG-USB", MsgId_CFG_USB);
    cc::Property::appendEnumValue(enumValues, "CFG-TMODE", MsgId_CFG_TMODE);
    cc::Property::appendEnumValue(enumValues, "CFG-NVS", MsgId_CFG_NVS);
    cc::Property::appendEnumValue(enumValues, "CFG-NAVX5", MsgId_CFG_NAVX5);
    cc::Property::appendEnumValue(enumValues, "CFG-NAV5", MsgId_CFG_NAV5);
    cc::Property::appendEnumValue(enumValues, "CFG-TP5", MsgId_CFG_TP5);
    cc::Property::appendEnumValue(enumValues, "CFG-RINV", MsgId_CFG_RINV);
    cc::Property::appendEnumValue(enumValues, "CFG-ITFM", MsgId_CFG_ITFM);
    cc::Property::appendEnumValue(enumValues, "CFG-PM2", MsgId_CFG_PM2);
    cc::Property::appendEnumValue(enumValues, "CFG-GNSS", MsgId_CFG_GNSS);
    cc::Property::appendEnumValue(enumValues, "CFG-LOGFILTER", MsgId_CFG_LOGFILTER);
    cc::Property::appendEnumValue(enumValues, "CFG-LIC", MsgId_CFG_LIC);

    return cc::Property::createPropertiesMap("CLASS + ID", std::move(enumValues));
}

}  // namespace

const QVariantMap& msgIdProperties()
{
    static const QVariantMap props(createMsgIdProperties());
    return props;
}


}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox


