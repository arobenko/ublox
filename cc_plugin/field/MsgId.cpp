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
    cc::Property::appendEnumValue(enumValues, "NAV-POSUTM", MsgId_NAV_POSUTM);
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
    cc::Property::appendEnumValue(enumValues, "RXM-POSREQ", MsgId_RXM_POSREQ);

    cc::Property::appendEnumValue(enumValues, "INF-ERROR", MsgId_INF_ERROR);
    cc::Property::appendEnumValue(enumValues, "INF-WARNING", MsgId_INF_WARNING);
    cc::Property::appendEnumValue(enumValues, "INF-NOTICE", MsgId_INF_NOTICE);
    cc::Property::appendEnumValue(enumValues, "INF-TEST", MsgId_INF_TEST);
    cc::Property::appendEnumValue(enumValues, "INF-DEBUG", MsgId_INF_DEBUG);
    cc::Property::appendEnumValue(enumValues, "INF-USER", MsgId_INF_USER);

    cc::Property::appendEnumValue(enumValues, "ACK-NAK", MsgId_ACK_NAK);
    cc::Property::appendEnumValue(enumValues, "ACK-ACK", MsgId_ACK_ACK);

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


