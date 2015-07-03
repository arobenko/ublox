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
    QVariantMap props;
    props.insert(cc::Property::name(), "CLASS + ID");

    props.insert(cc::Property::indexedName(MsgId_NAV_POSECEF), "NAV-POSECEF");
    props.insert(cc::Property::indexedName(MsgId_NAV_POSLLH), "NAV-POSLLH");
    props.insert(cc::Property::indexedName(MsgId_NAV_STATUS), "NAV-STATUS");
    props.insert(cc::Property::indexedName(MsgId_NAV_DOP), "NAV-DOP");
    props.insert(cc::Property::indexedName(MsgId_NAV_SOL), "NAV-SOL");
    props.insert(cc::Property::indexedName(MsgId_NAV_POSUTM), "NAV-POSUTM");
    props.insert(cc::Property::indexedName(MsgId_NAV_VELECEF), "NAV-VELECEF");
    props.insert(cc::Property::indexedName(MsgId_NAV_VELNED), "NAV-VELNED");
    props.insert(cc::Property::indexedName(MsgId_NAV_TIMEGPS), "NAV-TIMEGPS");
    props.insert(cc::Property::indexedName(MsgId_NAV_TIMEUTC), "NAV-TIMEUTC");
    props.insert(cc::Property::indexedName(MsgId_NAV_CLOCK), "NAV-CLOCK");
    props.insert(cc::Property::indexedName(MsgId_NAV_SVINFO), "NAV-SVINFO");
    props.insert(cc::Property::indexedName(MsgId_NAV_DGPS), "NAV-DGPS");
    props.insert(cc::Property::indexedName(MsgId_NAV_SBAS), "NAV-SBAS");
    props.insert(cc::Property::indexedName(MsgId_NAV_EKFSTATUS), "NAV-EKFSTATUS");

    props.insert(cc::Property::indexedName(MsgId_ACK_NAK), "ACK-NAK");
    props.insert(cc::Property::indexedName(MsgId_ACK_ACK), "ACK-ACK");

    return props;
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


