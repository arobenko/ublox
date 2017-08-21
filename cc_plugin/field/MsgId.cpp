//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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
#include "ublox/field/MsgId.h"

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
    return
        cc::property::field::ForField<ublox::field::MsgId>()
            .name("CLASS + ID")
            .add("NAV-POSECEF", MsgId_NAV_POSECEF)
            .add("NAV-POSLLH", MsgId_NAV_POSLLH)
            .add("NAV-STATUS", MsgId_NAV_STATUS)
            .add("NAV-DOP", MsgId_NAV_DOP)
            .add("NAV-ATT", MsgId_NAV_ATT)
            .add("NAV-SOL", MsgId_NAV_SOL)
            .add("NAV-PVT", MsgId_NAV_PVT)
            .add("NAV_ODO", MsgId_NAV_ODO)
            .add("NAV-RESETODO", MsgId_NAV_RESETODO)
            .add("NAV-VELECEF", MsgId_NAV_VELECEF)
            .add("NAV-VELNED", MsgId_NAV_VELNED)
            .add("NAV-HPPOSECEF", MsgId_NAV_HPPOSECEF)
            .add("NAV-HPPOSLLH", MsgId_NAV_HPPOSLLH)
            .add("NAV-TIMEGPS", MsgId_NAV_TIMEGPS)
            .add("NAV-TIMEUTC", MsgId_NAV_TIMEUTC)
            .add("NAV-CLOCK", MsgId_NAV_CLOCK)
            .add("NAV-TIMEGLO", MsgId_NAV_TIMEGLO)
            .add("NAV-TIMEBDS", MsgId_NAV_TIMEBDS)
            .add("NAV-TIMEGAL", MsgId_NAV_TIMEGAL)
            .add("NAV-TIMELS", MsgId_NAV_TIMELS)
            .add("NAV-SVINFO", MsgId_NAV_SVINFO)
            .add("NAV-DGPS", MsgId_NAV_DGPS)
            .add("NAV-SBAS", MsgId_NAV_SBAS)
            .add("NAV-ORB", MsgId_NAV_ORB)
            .add("NAV-SAT", MsgId_NAV_SAT)
            .add("NAV-GEOFENCE", MsgId_NAV_GEOFENCE)
            .add("NAV-SVIN", MsgId_NAV_SVIN)
            .add("NAV-RELPOSNED", MsgId_NAV_RELPOSNED)
            .add("NAV-EKFSTATUS", MsgId_NAV_EKFSTATUS)
            .add("NAV-AOPSTATUS", MsgId_NAV_AOPSTATUS)
            .add("NAV-EOE", MsgId_NAV_EOE)

            .add("RXM-RAW", MsgId_RXM_RAW)
            .add("RXM-SFRB", MsgId_RXM_SFRB)
            .add("RXM-SFRBX", MsgId_RXM_SFRBX)
            .add("RXM-MEASX", MsgId_RXM_MEASX)
            .add("RXM-RAWX", MsgId_RXM_RAWX)
            .add("RXM-SVSI", MsgId_RXM_SVSI)
            .add("RXM-ALM", MsgId_RXM_ALM)
            .add("RXM-EPH", MsgId_RXM_EPH)
            .add("RXM-PMREQ", MsgId_RXM_PMREQ)
            .add("RXM-RLM", MsgId_RXM_RLM)
            .add("RXM-IMES", MsgId_RXM_IMES)

            .add("INF-ERROR", MsgId_INF_ERROR)
            .add("INF-WARNING", MsgId_INF_WARNING)
            .add("INF-NOTICE", MsgId_INF_NOTICE)
            .add("INF-TEST", MsgId_INF_TEST)
            .add("INF-DEBUG", MsgId_INF_DEBUG)

            .add("ACK-NAK", MsgId_ACK_NAK)
            .add("ACK-ACK", MsgId_ACK_ACK)

            .add("CFG-PRT", MsgId_CFG_PRT)
            .add("CFG-MSG", MsgId_CFG_MSG)
            .add("CFG-INF", MsgId_CFG_INF)
            .add("CFG-RST", MsgId_CFG_RST)
            .add("CFG-DAT", MsgId_CFG_DAT)
            .add("CFG-TP", MsgId_CFG_TP)
            .add("CFG-RATE", MsgId_CFG_RATE)
            .add("CFG-CFG", MsgId_CFG_CFG)
            .add("CFG-FXN", MsgId_CFG_FXN)
            .add("CFG-RXM", MsgId_CFG_RXM)
            .add("CFG-EKF", MsgId_CFG_EKF)
            .add("CFG-ANT", MsgId_CFG_ANT)
            .add("CFG-SBAS", MsgId_CFG_SBAS)
            .add("CFG-NMEA", MsgId_CFG_NMEA)
            .add("CFG-USB", MsgId_CFG_USB)
            .add("CFG-TMODE", MsgId_CFG_TMODE)
            .add("CFG-ODO", MsgId_CFG_ODO)
            .add("CFG-NVS", MsgId_CFG_NVS)
            .add("CFG-NAVX5", MsgId_CFG_NAVX5)
            .add("CFG-NAV5", MsgId_CFG_NAV5)
            .add("CFG-ESFGWT", MsgId_CFG_ESFGWT)
            .add("CFG-TP5", MsgId_CFG_TP5)
            .add("CFG-PM", MsgId_CFG_PM)
            .add("CFG-RINV", MsgId_CFG_RINV)
            .add("CFG-ITFM", MsgId_CFG_ITFM)
            .add("CFG-PM2", MsgId_CFG_PM2)
            .add("CFG-TMODE2", MsgId_CFG_TMODE2)
            .add("CFG-GNSS", MsgId_CFG_GNSS)
            .add("CFG-LOGFILTER", MsgId_CFG_LOGFILTER)
            .add("CFG-TXSLOT", MsgId_CFG_TXSLOT)
            .add("CFG-PWR", MsgId_CFG_PWR)
            .add("CFG-HNR", MsgId_CFG_HNR)
            .add("CFG-ESRC", MsgId_CFG_ESRC)
            .add("CFG-DOSC", MsgId_CFG_DOSC)
            .add("CFG-SMGR", MsgId_CFG_SMGR)
            .add("CFG-GEOFENCE", MsgId_CFG_GEOFENCE)
            .add("CFG-DGNSS", MsgId_CFG_GNSS)
            .add("CFG-TMODE3", MsgId_CFG_TMODE3)
            .add("CFG-FIXSEED", MsgId_CFG_FIXSEED)
            .add("CFG-DYNSEED", MsgId_CFG_DYNSEED)
            .add("CFG-PMS", MsgId_CFG_PMS)

            .add("UPD-SOS", MsgId_UPD_SOS)

            .add("MON-IO", MsgId_MON_IO)
            .add("MON-VER", MsgId_MON_VER)
            .add("MON-MSGPP", MsgId_MON_MSGPP)
            .add("MON-RXBUF", MsgId_MON_RXBUF)
            .add("MON-TXBUF", MsgId_MON_TXBUF)
            .add("MON-HW", MsgId_MON_HW)
            .add("MON-HW2", MsgId_MON_HW2)
            .add("MON-RXR", MsgId_MON_RXR)
            .add("MON-PATCH", MsgId_MON_PATCH)
            .add("MON-GNSS", MsgId_MON_GNSS)
            .add("MON-SMGR", MsgId_MON_SMGR)

            .add("AID-REQ", MsgId_AID_REQ)
            .add("AID-INI", MsgId_AID_INI)
            .add("AID-HUI", MsgId_AID_HUI)
            .add("AID-DATA", MsgId_AID_DATA)
            .add("AID-ALM", MsgId_AID_ALM)
            .add("AID-EPH", MsgId_AID_EPH)
            .add("AID-ALPSRV", MsgId_AID_ALPSRV)
            .add("AID-AOP", MsgId_AID_AOP)
            .add("AID-ALP", MsgId_AID_ALP)

            .add("TIM-TP", MsgId_TIM_TP)
            .add("TIM-TM2", MsgId_TIM_TM2)
            .add("TIM-SVIN", MsgId_TIM_SVIN)
            .add("TIM-VRFY", MsgId_TIM_VRFY)
            .add("TIM-DOSC", MsgId_TIM_DOSC)
            .add("TIM-TOS", MsgId_TIM_TOS)
            .add("TIM-SMEAS", MsgId_TIM_SMEAS)
            .add("TIM-VCOCAL", MsgId_TIM_VCOCAL)
            .add("TIM-FCHG", MsgId_TIM_FCHG)
            .add("TIM-HOC", MsgId_TIM_HOC)

            .add("ESF-MEAS", MsgId_ESF_MEAS)
            .add("ESF-RAW", MsgId_ESF_RAW)
            .add("ESF-STATUS", MsgId_ESF_STATUS)
            .add("ESF-INS", MsgId_ESF_INS)

            .add("MGA-GPS", MsgId_MGA_GPS)
            .add("MGA-GAL", MsgId_MGA_GAL)
            .add("MGA-BDS", MsgId_MGA_BDS)
            .add("MGA-QZSS", MsgId_MGA_QZSS)
            .add("MGA-GLO", MsgId_MGA_GLO)
            .add("MGA-ANO", MsgId_MGA_ANO)
            .add("MGA-FLASH", MsgId_MGA_FLASH)
            .add("MGA-INI", MsgId_MGA_INI)
            .add("MGA-ACK", MsgId_MGA_ACK)
            .add("MGA-DBD", MsgId_MGA_DBD)

            .add("LOG-ERASE", MsgId_LOG_ERASE)
            .add("LOG-STRING", MsgId_LOG_STRING)
            .add("LOG-CREATE", MsgId_LOG_CREATE)
            .add("LOG-INFO", MsgId_LOG_INFO)
            .add("LOG-RETRIEVE", MsgId_LOG_RETRIEVE)
            .add("LOG-RETRIEVEPOS", MsgId_LOG_RETRIEVEPOS)
            .add("LOG-RETRIEVESTRING", MsgId_LOG_RETRIEVESTRING)
            .add("LOG-FINDTIME", MsgId_LOG_FINDTIME)

            .add("SEC-SIGN", MsgId_SEC_SIGN)
            .add("SEC-UNIQID", MsgId_SEC_UNIQID)

            .add("HNR-PVT", MsgId_HNR_PVT)

            .asMap();

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


