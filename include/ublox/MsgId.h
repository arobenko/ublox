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

/// @file
/// @brief Contains ID enumerator for all the messages.

#pragma once

#include <cstdint>

namespace ublox
{

/// @brief Enumeration type of message ID.
/// @details Contains both Class ID and Message ID. The class ID is most
///     significant byte, while Message ID is least significant one.@n
///     For example: ID of @b NAV-DOP message is 0x0104, where 0x01 is @b NAV Class ID
///     while 0x04 is @b DOP message ID within the @b NAV class.
enum MsgId : std::uint16_t
{
    MsgId_NAV_POSECEF = 0x0101, ///< ID of NAV-POSECEF message
    MsgId_NAV_POSLLH = 0x0102, ///< ID of NAV-POSLLH message
    MsgId_NAV_STATUS = 0x0103, ///< ID of NAV-STATUS message
    MsgId_NAV_DOP = 0x0104, ///< ID of NAV-DOP message
    MsgId_NAV_SOL = 0x0106, ///< ID of NAV-SOL message
    MsgId_NAV_PVT = 0x0107, ///< ID of NAV-PVT message
    MsgId_NAV_ODO = 0x0109, ///< ID of NAV-ODO message
    MsgId_NAV_RESETODO = 0x0110, ///< ID of NAV-RESETODO message
    MsgId_NAV_VELECEF = 0x0111, ///< ID of NAV-VELECEF message
    MsgId_NAV_VELNED = 0x0112, ///< ID of NAV-VELNED message
    MsgId_NAV_TIMEGPS = 0x0120, ///< ID of NAV-TIMEGPS message
    MsgId_NAV_TIMEUTC = 0x0121, ///< ID of NAV-TIMEUTC message
    MsgId_NAV_CLOCK = 0x0122, ///< ID of NAV-CLOCK message
    MsgId_NAV_TIMEGLO = 0x0123, ///< ID of NAV-TIMEGLO message
    MsgId_NAV_TIMEBDS = 0x0124, ///< ID of NAV-TIMEBDS message
    MsgId_NAV_TIMEGAL = 0x0125, ///< ID of NAV-TIMEGAL message
    MsgId_NAV_TIMELS = 0x0126, ///< ID of NAV-TIMELS message
    MsgId_NAV_SVINFO = 0x0130, ///< ID of NAV-SVINFO message
    MsgId_NAV_DGPS = 0x0131, ///< ID of NAV-DGPS message
    MsgId_NAV_SBAS = 0x0132, ///< ID of NAV-SBAS message
    MsgId_NAV_ORB = 0x0134, ///< ID of NAV-ORB message
    MsgId_NAV_SAT = 0x0135, ///< ID of NAV-SAT message
    MsgId_NAV_GEOFENCE = 0x0139, ///< ID of NAV-GEOFENCE message
    MsgId_NAV_EKFSTATUS = 0x0140, ///< ID of NAV-EKFSTATUS message
    MsgId_NAV_AOPSTATUS = 0x0160, ///< ID of NAV-AOPSTATUS message
    MsgId_NAV_EOE = 0x0161, ///< ID of NAV-EOE message
    MsgId_RXM_RAW = 0x0210, ///< ID of RXM-RAW message
    MsgId_RXM_SFRB = 0x0211, ///< ID of RXM-SFRB message
    MsgId_RXM_SFRBX = 0x0213, ///< ID of RXM-SFRBX message
    MsgId_RXM_MEASX = 0x0214, ///< ID of RXM-MEASX message
    MsgId_RXM_RAWX = 0x0215, ///< ID of RXM-RAWX message
    MsgId_RXM_SVSI = 0x0220, ///< ID of RXM-SVSI message
    MsgId_RXM_ALM = 0x0230, ///< ID of RXM-ALM message
    MsgId_RXM_EPH = 0x0231, ///< ID of RXM-EPH message
    MsgId_RXM_PMREQ = 0x0241, ///< ID of RXM-PMREQ message
    MsgId_RXM_RLM = 0x0259, ///< ID of RXM-RLM message
    MsgId_RXM_IMES = 0x0261, ///< ID of RXM-IMES message
    MsgId_INF_ERROR = 0x0400, ///< ID of RXM-ERROR message
    MsgId_INF_WARNING = 0x0401, ///< ID of INF-WARNING message
    MsgId_INF_NOTICE = 0x0402, ///< ID of INF-NOTICE message
    MsgId_INF_TEST = 0x0403, ///< ID of INF-TEST message
    MsgId_INF_DEBUG = 0x0404, ///< ID of INF-DEBUG message
    MsgId_ACK_NAK = 0x0500, ///< ID of ACK-NACK message
    MsgId_ACK_ACK = 0x0501, ///< ID of ACK-ACK message
    MsgId_CFG_PRT = 0x0600, ///< ID of CFG-PRT message
    MsgId_CFG_MSG = 0x0601, ///< ID of CFG-MSG message
    MsgId_CFG_INF = 0x0602, ///< ID of CFG-INF message
    MsgId_CFG_RST = 0x0604, ///< ID of CFG-RST message
    MsgId_CFG_DAT = 0x0606, ///< ID of CFG-DAT message
    MsgId_CFG_TP = 0x0607, ///< ID of CFG-TP message
    MsgId_CFG_RATE = 0x0608, ///< ID of CFG-RATE message
    MsgId_CFG_CFG = 0x0609, ///< ID of CFG-CFG message
    MsgId_CFG_FXN = 0x060E, ///< ID of CFG-FXN message
    MsgId_CFG_RXM = 0x0611, ///< ID of CFG-RXM message
    MsgId_CFG_EKF = 0x0612, ///< ID of CFG-EKF message
    MsgId_CFG_ANT = 0x0613, ///< ID of CFG-ANT message
    MsgId_CFG_SBAS = 0x0616, ///< ID of CFG-SBAS message
    MsgId_CFG_NMEA = 0x0617, ///< ID of CFG-NMEA message
    MsgId_CFG_USB = 0x061b, ///< ID of CFG-USB message
    MsgId_CFG_TMODE = 0x061d, ///< ID of CFG-TMODE message
    MsgId_CFG_ODO = 0x061e, ///< ID of CFG-ODO message
    MsgId_CFG_NVS = 0x0622, ///< ID of CFG-NVS message
    MsgId_CFG_NAVX5 = 0x0623, ///< ID of CFG-NAVX5 message
    MsgId_CFG_NAV5 = 0x0624, ///< ID of CFG-NAV5 message
    MsgId_CFG_ESFGWT = 0x0629, ///< ID of CFG-ESFGWT message
    MsgId_CFG_TP5 = 0x0631, ///< ID of CFG-TP5 message
    MsgId_CFG_PM = 0x0632, ///< ID of CFG-PM message
    MsgId_CFG_RINV = 0x0634, ///< ID of CFG-RINV message
    MsgId_CFG_ITFM = 0x0639, ///< ID of CFG-ITFM message
    MsgId_CFG_PM2 = 0x063b, ///< ID of CFG-PM2 message
    MsgId_CFG_TMODE2 = 0x063d, ///< ID of CFG-TMODE2 message
    MsgId_CFG_GNSS = 0x063e, ///< ID of CFG-GNSS message
    MsgId_CFG_LOGFILTER = 0x0647, ///< ID of CFG-LOGFILTER message
    MsgId_CFG_TXSLOT = 0x0653, ///< ID of CFG-TXSLOT message
    MsgId_CFG_PWR = 0x0657, ///< ID of CFG-PWR message
    MsgId_CFG_HNR = 0x065C, ///< ID of CFG-HNR message
    MsgId_CFG_ESRC = 0x0660, ///< ID of CFG-ESRC message
    MsgId_CFG_DOSC = 0x0661, ///< ID of CFG-DOSC message
    MsgId_CFG_SMGR = 0x0662, ///< ID of CFG-SMGR message
    MsgId_CFG_GEOFENCE = 0x0669, ///< ID of CFG-GEOFENCE message
    MsgId_CFG_DGNSS = 0x0670, ///< ID of CFG-DGNSS message
    MsgId_CFG_TMODE3 = 0x0671, ///< ID of CFG-TMODE3 message
    MsgId_CFG_FIXSEED = 0x0684, ///< ID of CFG-FIXSEED message
    MsgId_CFG_DYNSEED = 0x0685, ///< ID of CFG-DYNSEED message
    MsgId_CFG_PMS = 0x0686, ///< ID of CFG-PMS message
    MsgId_UPD_SOS = 0x0914, ///< ID of UPD-SOS message
    MsgId_MON_IO = 0x0a02, ///< ID of MON-IO message
    MsgId_MON_VER = 0x0a04, ///< ID of MON-VER message
    MsgId_MON_MSGPP = 0x0a06, ///< ID of MON-MSGPP message
    MsgId_MON_RXBUF = 0x0a07, ///< ID of MON-RXBUF message
    MsgId_MON_TXBUF = 0x0a08, ///< ID of MON-TXBUF message
    MsgId_MON_HW = 0x0a09, ///< ID of MON-HW message
    MsgId_MON_HW2 = 0x0a0b, ///< ID of MON-HW2 message
    MsgId_MON_RXR = 0x0a21, ///< ID of MON-RXR message
    MsgId_MON_PATCH = 0x0a27, ///< ID of MON-PATCH message
    MsgId_MON_GNSS = 0x0a28, ///< ID of MON-GNSS message
    MsgId_MON_SMGR = 0x0a2e, ///< ID of MON-SMGR message
    MsgId_AID_REQ = 0x0b00, ///< ID of AID-REQ message
    MsgId_AID_INI = 0x0b01, ///< ID of AID-INI message
    MsgId_AID_HUI = 0x0b02, ///< ID of AID-HUI message
    MsgId_AID_DATA = 0x0b10, ///< ID of AID-DATA message
    MsgId_AID_ALM = 0x0b30, ///< ID of AID-ALM message
    MsgId_AID_EPH = 0x0b31, ///< ID of AID-EPH message
    MsgId_AID_ALPSRV = 0x0b32, ///< ID of AID-ALPSRV message
    MsgId_AID_AOP = 0x0b33, ///< ID of AID-AOP message
    MsgId_AID_ALP = 0x0b50, ///< ID of AID-ALP message
    MsgId_TIM_TP = 0x0d01, ///< ID of TIM-TP message
    MsgId_TIM_TM2 = 0x0d03, ///< ID of TIM-TM2 message
    MsgId_TIM_SVIN = 0x0d04, ///< ID of TIM-SVIN message
    MsgId_TIM_VRFY = 0x0d06, ///< ID of TIM-VRFY message
    MsgId_TIM_DOSC = 0x0d11, ///< ID of TIM-DOSC message
    MsgId_TIM_TOS = 0x0d12, ///< ID of TIM-TOS message
    MsgId_TIM_SMEAS = 0x0d13, ///< ID of TIM-SMEAS message
    MsgId_TIM_VCOCAL = 0x0d15, ///< ID of TIM-VCOCAL message
    MsgId_TIM_FCHG = 0x0d16, ///< ID of TIM-FCHG message
    MsgId_TIM_HOC = 0x0d17, ///< ID of TIM-HOC message
    MsgId_ESF_MEAS = 0x1002, ///< ID of ESF-MEAS message
    MsgId_ESF_RAW = 0x1003, ///< ID of ESF-RAW message
    MsgId_ESF_STATUS = 0x1010, ///< ID of ESF-STATUS message
    MsgId_ESF_INS = 0x1015, ///< ID of ESF-INS message
    MsgId_MGA_GPS = 0x1300, ///< ID of MGA-GPS message
    MsgId_MGA_GAL = 0x1302, ///< ID of MGA-GAL message
    MsgId_MGA_BDS = 0x1303, ///< ID of MGA-BDS message
    MsgId_MGA_QZSS = 0x1305, ///< ID of MGA-QZSS message
    MsgId_MGA_GLO = 0x1306, ///< ID of MGA-GLO message
    MsgId_MGA_ANO = 0x1320, ///< ID of MGA-ANO message
    MsgId_MGA_FLASH = 0x1321, ///< ID of MGA-FLASH message
    MsgId_MGA_INI = 0x1340, ///< ID of MGA-INI message
    MsgId_MGA_ACK = 0x1360, ///< ID of MGA-ACK message
    MsgId_MGA_DBD = 0x1380, ///< ID of MGA-DBD message
    MsgId_LOG_ERASE = 0x2103, ///< ID of LOG-ERASE message
    MsgId_LOG_STRING = 0x2104, ///< ID of LOG-STRING message
    MsgId_LOG_CREATE = 0x2107, ///< ID of LOG-CREATE message
    MsgId_LOG_INFO = 0x2108, ///< ID of LOG-INFO message
    MsgId_LOG_RETRIEVE = 0x2109, ///< ID of LOG-RETRIEVE message
    MsgId_LOG_RETRIEVEPOS = 0x210b, ///< ID of LOG-RETRIEVEPOS message
    MsgId_LOG_RETRIEVESTRING = 0x210d, ///< ID of LOG-RETRIEVESTRING message
    MsgId_LOG_FINDTIME = 0x210e, ///< ID of LOG-FINDTIME message
    MsgId_LOG_RETRIEVEPOSEXTRA = 0x210f, ///< ID of LOG-RETRIEVEPOSEXTRA message
    MsgId_SEC_SIGN = 0x2701, ///< ID of SEC-SIGN message
    MsgId_SEC_UNIQID = 0x2703, ///< ID of SEC-UNIQID message
    MsgId_HNR_PVT = 0x2800, ///< ID of HNR-PVT message
};

}  // namespace ublox


