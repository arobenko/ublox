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


#pragma once

#include <tuple>
#include "cc_plugin/Message.h"

//#include "cc_plugin/message/NavPosecef.h"
//#include "cc_plugin/message/NavPosecefPoll.h"
//#include "cc_plugin/message/NavPosllh.h"
//#include "cc_plugin/message/NavPosllhPoll.h"
//#include "cc_plugin/message/NavStatus.h"
//#include "cc_plugin/message/NavStatusPoll.h"
//#include "cc_plugin/message/NavDop.h"
//#include "cc_plugin/message/NavDopPoll.h"
//#include "cc_plugin/message/NavSol.h"
//#include "cc_plugin/message/NavSolPoll.h"
//#include "cc_plugin/message/NavPvt.h"
//#include "cc_plugin/message/NavPvtPoll.h"
//#include "cc_plugin/message/NavVelecef.h"
//#include "cc_plugin/message/NavVelecefPoll.h"
//#include "cc_plugin/message/NavVelned.h"
//#include "cc_plugin/message/NavVelnedPoll.h"
//#include "cc_plugin/message/NavTimegps.h"
//#include "cc_plugin/message/NavTimegpsPoll.h"
//#include "cc_plugin/message/NavTimeutc.h"
//#include "cc_plugin/message/NavTimeutcPoll.h"
//#include "cc_plugin/message/NavClock.h"
//#include "cc_plugin/message/NavClockPoll.h"
//#include "cc_plugin/message/NavSvinfo.h"
//#include "cc_plugin/message/NavSvinfoPoll.h"
//#include "cc_plugin/message/NavDgps.h"
//#include "cc_plugin/message/NavDgpsPoll.h"
//#include "cc_plugin/message/NavSbas.h"
//#include "cc_plugin/message/NavSbasPoll.h"
//#include "cc_plugin/message/NavEkfstatus.h"
//#include "cc_plugin/message/NavEkfstatusPoll.h"
//#include "cc_plugin/message/NavAopstatus.h"
//#include "cc_plugin/message/NavAopstatusPoll.h"
//
//#include "cc_plugin/message/RxmRaw.h"
//#include "cc_plugin/message/RxmRawPoll.h"
//#include "cc_plugin/message/RxmSfrb.h"
//#include "cc_plugin/message/RxmSvsi.h"
//#include "cc_plugin/message/RxmSvsiPoll.h"
//#include "cc_plugin/message/RxmAlm.h"
//#include "cc_plugin/message/RxmAlmPollSv.h"
//#include "cc_plugin/message/RxmAlmPoll.h"
//#include "cc_plugin/message/RxmEph.h"
//#include "cc_plugin/message/RxmEphPollSv.h"
//#include "cc_plugin/message/RxmEphPoll.h"
//#include "cc_plugin/message/RxmPmreq.h"
//
//#include "cc_plugin/message/InfError.h"
//#include "cc_plugin/message/InfWarning.h"
//#include "cc_plugin/message/InfNotice.h"
//#include "cc_plugin/message/InfTest.h"
//#include "cc_plugin/message/InfDebug.h"
//
//#include "cc_plugin/message/AckNak.h"
//#include "cc_plugin/message/AckAck.h"
//
#include "cc_plugin/message/CfgPrtUart.h"
#include "cc_plugin/message/CfgPrtUsb.h"
#include "cc_plugin/message/CfgPrtSpi.h"
#include "cc_plugin/message/CfgPrtDdc.h"
#include "cc_plugin/message/CfgPrtPollPort.h"
#include "cc_plugin/message/CfgPrtPoll.h"
#include "cc_plugin/message/CfgMsg.h"
#include "cc_plugin/message/CfgMsgCurrent.h"
#include "cc_plugin/message/CfgMsgPoll.h"
#include "cc_plugin/message/CfgInf.h"
#include "cc_plugin/message/CfgInfPoll.h"
#include "cc_plugin/message/CfgRst.h"
#include "cc_plugin/message/CfgDat.h"
#include "cc_plugin/message/CfgDatUser.h"
#include "cc_plugin/message/CfgDatStandard.h"
#include "cc_plugin/message/CfgDatPoll.h"
#include "cc_plugin/message/CfgTp.h"
#include "cc_plugin/message/CfgTpPoll.h"
#include "cc_plugin/message/CfgRate.h"
#include "cc_plugin/message/CfgRatePoll.h"
#include "cc_plugin/message/CfgCfg.h"
#include "cc_plugin/message/CfgFxn.h"
#include "cc_plugin/message/CfgFxnPoll.h"
//#include "cc_plugin/message/CfgRxm.h"
//#include "cc_plugin/message/CfgRxmPoll.h"
//#include "cc_plugin/message/CfgEkf.h"
//#include "cc_plugin/message/CfgEkfPoll.h"

namespace ublox
{

namespace cc_plugin
{

typedef std::tuple<
//    cc_plugin::message::NavPosecef,
//    cc_plugin::message::NavPosecefPoll,
//    cc_plugin::message::NavPosllh,
//    cc_plugin::message::NavPosllhPoll,
//    cc_plugin::message::NavStatus,
//    cc_plugin::message::NavStatusPoll,
//    cc_plugin::message::NavDop,
//    cc_plugin::message::NavDopPoll,
//    cc_plugin::message::NavSol,
//    cc_plugin::message::NavSolPoll,
//    cc_plugin::message::NavPvt,
//    cc_plugin::message::NavPvtPoll,
//    cc_plugin::message::NavVelecef,
//    cc_plugin::message::NavVelecefPoll,
//    cc_plugin::message::NavVelned,
//    cc_plugin::message::NavVelnedPoll,
//    cc_plugin::message::NavTimegps,
//    cc_plugin::message::NavTimegpsPoll,
//    cc_plugin::message::NavTimeutc,
//    cc_plugin::message::NavTimeutcPoll,
//    cc_plugin::message::NavClock,
//    cc_plugin::message::NavClockPoll,
//    cc_plugin::message::NavSvinfo,
//    cc_plugin::message::NavSvinfoPoll,
//    cc_plugin::message::NavDgps,
//    cc_plugin::message::NavDgpsPoll,
//    cc_plugin::message::NavSbas,
//    cc_plugin::message::NavSbasPoll,
//    cc_plugin::message::NavEkfstatus,
//    cc_plugin::message::NavEkfstatusPoll,
//    cc_plugin::message::NavAopstatus,
//    cc_plugin::message::NavAopstatusPoll,
//    cc_plugin::message::RxmRaw,
//    cc_plugin::message::RxmRawPoll,
//    cc_plugin::message::RxmSfrb,
//    cc_plugin::message::RxmSvsi,
//    cc_plugin::message::RxmSvsiPoll,
//    cc_plugin::message::RxmAlm,
//    cc_plugin::message::RxmAlmPollSv,
//    cc_plugin::message::RxmAlmPoll,
//    cc_plugin::message::RxmEph,
//    cc_plugin::message::RxmEphPollSv,
//    cc_plugin::message::RxmEphPoll,
//    cc_plugin::message::RxmPmreq,
//    cc_plugin::message::InfError,
//    cc_plugin::message::InfWarning,
//    cc_plugin::message::InfNotice,
//    cc_plugin::message::InfTest,
//    cc_plugin::message::InfDebug,
//    cc_plugin::message::AckNak,
//    cc_plugin::message::AckAck,
    cc_plugin::message::CfgPrtUart,
    cc_plugin::message::CfgPrtUsb,
    cc_plugin::message::CfgPrtSpi,
    cc_plugin::message::CfgPrtDdc,
    cc_plugin::message::CfgPrtPollPort,
    cc_plugin::message::CfgPrtPoll,
    cc_plugin::message::CfgMsg,
    cc_plugin::message::CfgMsgCurrent,
    cc_plugin::message::CfgMsgPoll,
    cc_plugin::message::CfgInf,
    cc_plugin::message::CfgInfPoll,
    cc_plugin::message::CfgRst,
    cc_plugin::message::CfgDat,
    cc_plugin::message::CfgDatUser,
    cc_plugin::message::CfgDatStandard,
    cc_plugin::message::CfgDatPoll,
    cc_plugin::message::CfgTp,
    cc_plugin::message::CfgTpPoll,
    cc_plugin::message::CfgRate,
    cc_plugin::message::CfgRatePoll,
    cc_plugin::message::CfgCfg,
    cc_plugin::message::CfgFxn,
    cc_plugin::message::CfgFxnPoll/*,
    cc_plugin::message::CfgRxm,
    cc_plugin::message::CfgRxmPoll,
    cc_plugin::message::CfgEkf,
    cc_plugin::message::CfgEkfPoll*/
> AllMessages;

}  // namespace cc_plugin

}  // namespace ublox





