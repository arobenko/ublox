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


#pragma once

#include <tuple>
#include "cc_plugin/Message.h"

#include "cc_plugin/message/NavPosecef.h"
#include "cc_plugin/message/NavPosecefPoll.h"
#include "cc_plugin/message/NavPosllh.h"
#include "cc_plugin/message/NavPosllhPoll.h"
#include "cc_plugin/message/NavStatus.h"
#include "cc_plugin/message/NavStatusPoll.h"
#include "cc_plugin/message/NavDop.h"
#include "cc_plugin/message/NavDopPoll.h"
#include "cc_plugin/message/NavSol.h"
#include "cc_plugin/message/NavSolPoll.h"
#include "cc_plugin/message/NavPvt.h"
#include "cc_plugin/message/NavPvtPoll.h"
#include "cc_plugin/message/NavOdo.h"
#include "cc_plugin/message/NavOdoPoll.h"
#include "cc_plugin/message/NavResetodo.h"
#include "cc_plugin/message/NavVelecef.h"
#include "cc_plugin/message/NavVelecefPoll.h"
#include "cc_plugin/message/NavVelned.h"
#include "cc_plugin/message/NavVelnedPoll.h"
#include "cc_plugin/message/NavTimegps.h"
#include "cc_plugin/message/NavTimegpsPoll.h"
#include "cc_plugin/message/NavTimeutc.h"
#include "cc_plugin/message/NavTimeutcPoll.h"
#include "cc_plugin/message/NavClock.h"
#include "cc_plugin/message/NavClockPoll.h"
#include "cc_plugin/message/NavTimeglo.h"
#include "cc_plugin/message/NavTimegloPoll.h"
#include "cc_plugin/message/NavTimebds.h"
#include "cc_plugin/message/NavTimebdsPoll.h"
#include "cc_plugin/message/NavTimegal.h"
#include "cc_plugin/message/NavTimegalPoll.h"
#include "cc_plugin/message/NavTimels.h"
#include "cc_plugin/message/NavTimelsPoll.h"
#include "cc_plugin/message/NavSvinfo.h"
#include "cc_plugin/message/NavSvinfoPoll.h"
#include "cc_plugin/message/NavDgps.h"
#include "cc_plugin/message/NavDgpsPoll.h"
#include "cc_plugin/message/NavSbas.h"
#include "cc_plugin/message/NavSbasPoll.h"
#include "cc_plugin/message/NavOrb.h"
#include "cc_plugin/message/NavOrbPoll.h"
#include "cc_plugin/message/NavSat.h"
#include "cc_plugin/message/NavSatPoll.h"
#include "cc_plugin/message/NavGeofence.h"
#include "cc_plugin/message/NavGeofencePoll.h"
#include "cc_plugin/message/NavEkfstatusPoll.h"
#include "cc_plugin/message/NavAopstatusU8.h"
#include "cc_plugin/message/NavAopstatusPoll.h"
#include "cc_plugin/message/NavEoe.h"

#include "cc_plugin/message/RxmSfrbx.h"
#include "cc_plugin/message/RxmMeasx.h"
#include "cc_plugin/message/RxmRawx.h"
#include "cc_plugin/message/RxmRawxPoll.h"
#include "cc_plugin/message/RxmSvsi.h"
#include "cc_plugin/message/RxmSvsiPoll.h"
#include "cc_plugin/message/RxmPmreqV0.h"
#include "cc_plugin/message/RxmPmreq.h"
#include "cc_plugin/message/RxmRlmShort.h"
#include "cc_plugin/message/RxmRlmLong.h"
#include "cc_plugin/message/RxmImes.h"
#include "cc_plugin/message/RxmImesPoll.h"

#include "cc_plugin/message/InfError.h"
#include "cc_plugin/message/InfWarning.h"
#include "cc_plugin/message/InfNotice.h"
#include "cc_plugin/message/InfTest.h"
#include "cc_plugin/message/InfDebug.h"

#include "cc_plugin/message/AckNak.h"
#include "cc_plugin/message/AckAck.h"

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
#include "cc_plugin/message/CfgRate.h"
#include "cc_plugin/message/CfgRatePoll.h"
#include "cc_plugin/message/CfgCfg.h"
#include "cc_plugin/message/CfgRxm.h"
#include "cc_plugin/message/CfgRxmPoll.h"
#include "cc_plugin/message/CfgAnt.h"
#include "cc_plugin/message/CfgAntPoll.h"
#include "cc_plugin/message/CfgSbas.h"
#include "cc_plugin/message/CfgSbasPoll.h"
#include "cc_plugin/message/CfgNmeaExtV1.h"
#include "cc_plugin/message/CfgNmeaExt.h"
#include "cc_plugin/message/CfgNmea.h"
#include "cc_plugin/message/CfgNmeaPoll.h"
#include "cc_plugin/message/CfgUsb.h"
#include "cc_plugin/message/CfgUsbPoll.h"
#include "cc_plugin/message/CfgOdo.h"
#include "cc_plugin/message/CfgOdoPoll.h"
#include "cc_plugin/message/CfgNavx5.h"
#include "cc_plugin/message/CfgNavx5Poll.h"
#include "cc_plugin/message/CfgNav5.h"
#include "cc_plugin/message/CfgNav5Poll.h"
#include "cc_plugin/message/CfgTp5.h"
#include "cc_plugin/message/CfgTp5PollSelect.h"
#include "cc_plugin/message/CfgTp5Poll.h"
#include "cc_plugin/message/CfgRinv.h"
#include "cc_plugin/message/CfgRinvPoll.h"
#include "cc_plugin/message/CfgItfm.h"
#include "cc_plugin/message/CfgItfmPoll.h"
#include "cc_plugin/message/CfgPm2.h"
#include "cc_plugin/message/CfgPm2Poll.h"
#include "cc_plugin/message/CfgTmode2.h"
#include "cc_plugin/message/CfgTmode2Poll.h"
#include "cc_plugin/message/CfgGnss.h"
#include "cc_plugin/message/CfgGnssPoll.h"
#include "cc_plugin/message/CfgLogfilter.h"
#include "cc_plugin/message/CfgLogfilterPoll.h"
#include "cc_plugin/message/CfgTxslot.h"
#include "cc_plugin/message/CfgPwr.h"
#include "cc_plugin/message/CfgHnr.h"
#include "cc_plugin/message/CfgHnrPoll.h"
#include "cc_plugin/message/CfgEsrc.h"
#include "cc_plugin/message/CfgEsrcPoll.h"
#include "cc_plugin/message/CfgDosc.h"
#include "cc_plugin/message/CfgDoscPoll.h"
#include "cc_plugin/message/CfgSmgr.h"
#include "cc_plugin/message/CfgSmgrPoll.h"
#include "cc_plugin/message/CfgGeofence.h"
#include "cc_plugin/message/CfgGeofencePoll.h"
#include "cc_plugin/message/CfgDgnss.h"
#include "cc_plugin/message/CfgDgnssPoll.h"
#include "cc_plugin/message/CfgTmode3.h"
#include "cc_plugin/message/CfgTmode3Poll.h"
#include "cc_plugin/message/CfgFixseed.h"
#include "cc_plugin/message/CfgDynseed.h"
#include "cc_plugin/message/CfgPms.h"
#include "cc_plugin/message/CfgPmsPoll.h"

#include "cc_plugin/message/UpdSosRestored.h"
#include "cc_plugin/message/UpdSosAck.h"
#include "cc_plugin/message/UpdSosClear.h"
#include "cc_plugin/message/UpdSosCreate.h"
#include "cc_plugin/message/UpdSosPoll.h"

#include "cc_plugin/message/MonIo.h"
#include "cc_plugin/message/MonIoPoll.h"
#include "cc_plugin/message/MonVer.h"
#include "cc_plugin/message/MonVerPoll.h"
#include "cc_plugin/message/MonMsgpp.h"
#include "cc_plugin/message/MonMsgppPoll.h"
#include "cc_plugin/message/MonRxbuf.h"
#include "cc_plugin/message/MonRxbufPoll.h"
#include "cc_plugin/message/MonTxbuf.h"
#include "cc_plugin/message/MonTxbufPoll.h"
#include "cc_plugin/message/MonHw.h"
#include "cc_plugin/message/MonHwPoll.h"
#include "cc_plugin/message/MonHw2.h"
#include "cc_plugin/message/MonHw2Poll.h"
#include "cc_plugin/message/MonRxr.h"
#include "cc_plugin/message/MonPatch.h"
#include "cc_plugin/message/MonPatchPoll.h"
#include "cc_plugin/message/MonGnss.h"
#include "cc_plugin/message/MonGnssPoll.h"
#include "cc_plugin/message/MonSmgr.h"
#include "cc_plugin/message/MonSmgrPoll.h"

#include "cc_plugin/message/AidIni.h"
#include "cc_plugin/message/AidIniPoll.h"
#include "cc_plugin/message/AidHui.h"
#include "cc_plugin/message/AidHuiPoll.h"
#include "cc_plugin/message/AidData.h"
#include "cc_plugin/message/AidAlm.h"
#include "cc_plugin/message/AidAlmPollSv.h"
#include "cc_plugin/message/AidAlmPoll.h"
#include "cc_plugin/message/AidEph.h"
#include "cc_plugin/message/AidEphPollSv.h"
#include "cc_plugin/message/AidEphPoll.h"
#include "cc_plugin/message/AidAopU8.h"
#include "cc_plugin/message/AidAopPollSv.h"
#include "cc_plugin/message/AidAopPoll.h"

#include "cc_plugin/message/TimTp.h"
#include "cc_plugin/message/TimTpPoll.h"
#include "cc_plugin/message/TimTm2.h"
#include "cc_plugin/message/TimTm2Poll.h"
#include "cc_plugin/message/TimSvin.h"
#include "cc_plugin/message/TimSvinPoll.h"
#include "cc_plugin/message/TimVrfy.h"
#include "cc_plugin/message/TimVrfyPoll.h"
#include "cc_plugin/message/TimDosc.h"
#include "cc_plugin/message/TimTos.h"
#include "cc_plugin/message/TimSmeas.h"
#include "cc_plugin/message/TimVcocal.h"
#include "cc_plugin/message/TimVcocalExt.h"
#include "cc_plugin/message/TimVcocalStop.h"
#include "cc_plugin/message/TimVcocalPoll.h"
#include "cc_plugin/message/TimFchg.h"
#include "cc_plugin/message/TimFchgPoll.h"
#include "cc_plugin/message/TimHoc.h"

#include "cc_plugin/message/EsfMeas.h"
#include "cc_plugin/message/EsfMeasPoll.h"
#include "cc_plugin/message/EsfStatus.h"
#include "cc_plugin/message/EsfStatusPoll.h"
#include "cc_plugin/message/EsfIns.h"
#include "cc_plugin/message/EsfInsPoll.h"

#include "cc_plugin/message/MgaGpsEph.h"
#include "cc_plugin/message/MgaGpsAlm.h"
#include "cc_plugin/message/MgaGpsHealth.h"
#include "cc_plugin/message/MgaGpsUtc.h"
#include "cc_plugin/message/MgaGpsIono.h"
#include "cc_plugin/message/MgaGalEph.h"
#include "cc_plugin/message/MgaGalAlm.h"
#include "cc_plugin/message/MgaGalTimeoffset.h"
#include "cc_plugin/message/MgaGalUtc.h"
#include "cc_plugin/message/MgaBdsEph.h"
#include "cc_plugin/message/MgaBdsAlm.h"
#include "cc_plugin/message/MgaBdsHealth.h"
#include "cc_plugin/message/MgaBdsUtc.h"
#include "cc_plugin/message/MgaBdsIono.h"
#include "cc_plugin/message/MgaQzssEph.h"
#include "cc_plugin/message/MgaQzssAlm.h"
#include "cc_plugin/message/MgaQzssHealth.h"
#include "cc_plugin/message/MgaGloEph.h"
#include "cc_plugin/message/MgaGloAlm.h"
#include "cc_plugin/message/MgaGloTimeoffset.h"
#include "cc_plugin/message/MgaAno.h"
#include "cc_plugin/message/MgaFlashData.h"
#include "cc_plugin/message/MgaFlashStop.h"
#include "cc_plugin/message/MgaFlashAck.h"
#include "cc_plugin/message/MgaIniPosXyz.h"
#include "cc_plugin/message/MgaIniPosLlh.h"
#include "cc_plugin/message/MgaIniTimeUtc.h"
#include "cc_plugin/message/MgaIniTimeGnss.h"
#include "cc_plugin/message/MgaIniClkd.h"
#include "cc_plugin/message/MgaIniFreq.h"
#include "cc_plugin/message/MgaIniEop.h"
#include "cc_plugin/message/MgaAck.h"
#include "cc_plugin/message/MgaDbd.h"
#include "cc_plugin/message/MgaDbdPoll.h"

#include "cc_plugin/message/LogErase.h"
#include "cc_plugin/message/LogString.h"
#include "cc_plugin/message/LogCreate.h"
#include "cc_plugin/message/LogInfo.h"
#include "cc_plugin/message/LogInfoPoll.h"
#include "cc_plugin/message/LogRetrieve.h"
#include "cc_plugin/message/LogRetrievepos.h"
#include "cc_plugin/message/LogRetrievestring.h"
#include "cc_plugin/message/LogFindtimeCmd.h"
#include "cc_plugin/message/LogFindtime.h"
#include "cc_plugin/message/LogRetrieveposextra.h"

#include "cc_plugin/message/SecSign.h"
#include "cc_plugin/message/SecUniqid.h"

namespace ublox
{

namespace cc_plugin
{

using Ublox8Messages = std::tuple<
    cc_plugin::message::NavPosecef,
    cc_plugin::message::NavPosecefPoll,
    cc_plugin::message::NavPosllh,
    cc_plugin::message::NavPosllhPoll,
    cc_plugin::message::NavStatus,
    cc_plugin::message::NavStatusPoll,
    cc_plugin::message::NavDop,
    cc_plugin::message::NavDopPoll,
    cc_plugin::message::NavSol,
    cc_plugin::message::NavSolPoll,
    cc_plugin::message::NavPvt,
    cc_plugin::message::NavPvtPoll,
    cc_plugin::message::NavOdo,
    cc_plugin::message::NavOdoPoll,
    cc_plugin::message::NavResetodo,
    cc_plugin::message::NavVelecef,
    cc_plugin::message::NavVelecefPoll,
    cc_plugin::message::NavVelned,
    cc_plugin::message::NavVelnedPoll,
    cc_plugin::message::NavTimegps,
    cc_plugin::message::NavTimegpsPoll,
    cc_plugin::message::NavTimeutc,
    cc_plugin::message::NavTimeutcPoll,
    cc_plugin::message::NavClock,
    cc_plugin::message::NavClockPoll,
    cc_plugin::message::NavTimeglo,
    cc_plugin::message::NavTimegloPoll,
    cc_plugin::message::NavTimebds,
    cc_plugin::message::NavTimebdsPoll,
    cc_plugin::message::NavTimegal,
    cc_plugin::message::NavTimegalPoll,
    cc_plugin::message::NavTimels,
    cc_plugin::message::NavTimelsPoll,
    cc_plugin::message::NavSvinfo,
    cc_plugin::message::NavSvinfoPoll,
    cc_plugin::message::NavDgps,
    cc_plugin::message::NavDgpsPoll,
    cc_plugin::message::NavSbas,
    cc_plugin::message::NavSbasPoll,
    cc_plugin::message::NavOrb,
    cc_plugin::message::NavOrbPoll,
    cc_plugin::message::NavSat,
    cc_plugin::message::NavSatPoll,
    cc_plugin::message::NavGeofence,
    cc_plugin::message::NavGeofencePoll,
    cc_plugin::message::NavAopstatusU8,
    cc_plugin::message::NavAopstatusPoll,
    cc_plugin::message::NavEoe,
    cc_plugin::message::RxmSfrbx,
    cc_plugin::message::RxmMeasx,
    cc_plugin::message::RxmRawx,
    cc_plugin::message::RxmRawxPoll,
    cc_plugin::message::RxmSvsi,
    cc_plugin::message::RxmSvsiPoll,
    cc_plugin::message::RxmPmreqV0,
    cc_plugin::message::RxmPmreq,
    cc_plugin::message::RxmRlmShort,
    cc_plugin::message::RxmRlmLong,
    cc_plugin::message::RxmImes,
    cc_plugin::message::RxmImesPoll,
    cc_plugin::message::InfError,
    cc_plugin::message::InfWarning,
    cc_plugin::message::InfNotice,
    cc_plugin::message::InfTest,
    cc_plugin::message::InfDebug,
    cc_plugin::message::AckNak,
    cc_plugin::message::AckAck,
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
    cc_plugin::message::CfgRate,
    cc_plugin::message::CfgRatePoll,
    cc_plugin::message::CfgCfg,
    cc_plugin::message::CfgRxm,
    cc_plugin::message::CfgRxmPoll,
    cc_plugin::message::CfgAnt,
    cc_plugin::message::CfgAntPoll,
    cc_plugin::message::CfgSbas,
    cc_plugin::message::CfgSbasPoll,
    cc_plugin::message::CfgNmeaExtV1,
    cc_plugin::message::CfgNmeaExt,
    cc_plugin::message::CfgNmea,
    cc_plugin::message::CfgNmeaPoll,
    cc_plugin::message::CfgUsb,
    cc_plugin::message::CfgUsbPoll,
    cc_plugin::message::CfgOdo,
    cc_plugin::message::CfgOdoPoll,
    cc_plugin::message::CfgNavx5,
    cc_plugin::message::CfgNavx5Poll,
    cc_plugin::message::CfgNav5,
    cc_plugin::message::CfgNav5Poll,
    cc_plugin::message::CfgTp5,
    cc_plugin::message::CfgTp5PollSelect,
    cc_plugin::message::CfgTp5Poll,
    cc_plugin::message::CfgRinv,
    cc_plugin::message::CfgRinvPoll,
    cc_plugin::message::CfgItfm,
    cc_plugin::message::CfgItfmPoll,
    cc_plugin::message::CfgPm2,
    cc_plugin::message::CfgPm2Poll,
    cc_plugin::message::CfgTmode2,
    cc_plugin::message::CfgTmode2Poll,
    cc_plugin::message::CfgGnss,
    cc_plugin::message::CfgGnssPoll,
    cc_plugin::message::CfgLogfilter,
    cc_plugin::message::CfgLogfilterPoll,
    cc_plugin::message::CfgTxslot,
    cc_plugin::message::CfgPwr,
    cc_plugin::message::CfgHnr,
    cc_plugin::message::CfgHnrPoll,
    cc_plugin::message::CfgEsrc,
    cc_plugin::message::CfgEsrcPoll,
    cc_plugin::message::CfgDosc,
    cc_plugin::message::CfgDoscPoll,
    cc_plugin::message::CfgSmgr,
    cc_plugin::message::CfgSmgrPoll,
    cc_plugin::message::CfgGeofence,
    cc_plugin::message::CfgGeofencePoll,
    cc_plugin::message::CfgDgnss,
    cc_plugin::message::CfgDgnssPoll,
    cc_plugin::message::CfgTmode3,
    cc_plugin::message::CfgTmode3Poll,
    cc_plugin::message::CfgFixseed,
    cc_plugin::message::CfgDynseed,
    cc_plugin::message::CfgPms,
    cc_plugin::message::CfgPmsPoll,
    cc_plugin::message::UpdSosRestored,
    cc_plugin::message::UpdSosAck,
    cc_plugin::message::UpdSosClear,
    cc_plugin::message::UpdSosCreate,
    cc_plugin::message::UpdSosPoll,
    cc_plugin::message::MonIo,
    cc_plugin::message::MonIoPoll,
    cc_plugin::message::MonVer,
    cc_plugin::message::MonVerPoll,
    cc_plugin::message::MonMsgpp,
    cc_plugin::message::MonMsgppPoll,
    cc_plugin::message::MonRxbuf,
    cc_plugin::message::MonRxbufPoll,
    cc_plugin::message::MonTxbuf,
    cc_plugin::message::MonTxbufPoll,
    cc_plugin::message::MonHw,
    cc_plugin::message::MonHwPoll,
    cc_plugin::message::MonHw2,
    cc_plugin::message::MonHw2Poll,
    cc_plugin::message::MonRxr,
    cc_plugin::message::MonPatch,
    cc_plugin::message::MonPatchPoll,
    cc_plugin::message::MonGnss,
    cc_plugin::message::MonGnssPoll,
    cc_plugin::message::MonSmgr,
    cc_plugin::message::MonSmgrPoll,
    cc_plugin::message::AidIni,
    cc_plugin::message::AidIniPoll,
    cc_plugin::message::AidHui,
    cc_plugin::message::AidHuiPoll,
    cc_plugin::message::AidData,
    cc_plugin::message::AidAlm,
    cc_plugin::message::AidAlmPollSv,
    cc_plugin::message::AidAlmPoll,
    cc_plugin::message::AidEph,
    cc_plugin::message::AidEphPollSv,
    cc_plugin::message::AidEphPoll,
    cc_plugin::message::AidAopU8,
    cc_plugin::message::AidAopPollSv,
    cc_plugin::message::AidAopPoll,
    cc_plugin::message::TimTp,
    cc_plugin::message::TimTpPoll,
    cc_plugin::message::TimTm2,
    cc_plugin::message::TimTm2Poll,
    cc_plugin::message::TimSvin,
    cc_plugin::message::TimSvinPoll,
    cc_plugin::message::TimVrfy,
    cc_plugin::message::TimVrfyPoll,
    cc_plugin::message::TimDosc,
    cc_plugin::message::TimTos,
    cc_plugin::message::TimSmeas,
    cc_plugin::message::TimVcocal,
    cc_plugin::message::TimVcocalExt,
    cc_plugin::message::TimVcocalStop,
    cc_plugin::message::TimVcocalPoll,
    cc_plugin::message::TimFchg,
    cc_plugin::message::TimFchgPoll,
    cc_plugin::message::EsfMeas,
    cc_plugin::message::EsfMeasPoll,
    cc_plugin::message::EsfStatus,
    cc_plugin::message::EsfStatusPoll,
    cc_plugin::message::EsfIns,
    cc_plugin::message::EsfInsPoll,
    cc_plugin::message::MgaGpsEph,
    cc_plugin::message::MgaGpsAlm,
    cc_plugin::message::MgaGpsHealth,
    cc_plugin::message::MgaGpsUtc,
    cc_plugin::message::MgaGpsIono,
    cc_plugin::message::MgaGalEph,
    cc_plugin::message::MgaGalAlm,
    cc_plugin::message::MgaGalTimeoffset,
    cc_plugin::message::MgaGalUtc,
    cc_plugin::message::MgaBdsEph,
    cc_plugin::message::MgaBdsAlm,
    cc_plugin::message::MgaBdsHealth,
    cc_plugin::message::MgaBdsUtc,
    cc_plugin::message::MgaBdsIono,
    cc_plugin::message::MgaQzssEph,
    cc_plugin::message::MgaQzssAlm,
    cc_plugin::message::MgaQzssHealth,
    cc_plugin::message::MgaGloEph,
    cc_plugin::message::MgaGloAlm,
    cc_plugin::message::MgaGloTimeoffset,
    cc_plugin::message::MgaAno,
    cc_plugin::message::MgaFlashData,
    cc_plugin::message::MgaFlashStop,
    cc_plugin::message::MgaFlashAck,
    cc_plugin::message::MgaIniPosXyz,
    cc_plugin::message::MgaIniPosLlh,
    cc_plugin::message::MgaIniTimeUtc,
    cc_plugin::message::MgaIniTimeGnss,
    cc_plugin::message::MgaIniClkd,
    cc_plugin::message::MgaIniFreq,
    cc_plugin::message::MgaIniEop,
    cc_plugin::message::MgaAck,
    cc_plugin::message::MgaDbd,
    cc_plugin::message::MgaDbdPoll,
    cc_plugin::message::LogErase,
    cc_plugin::message::LogString,
    cc_plugin::message::LogCreate,
    cc_plugin::message::LogInfo,
    cc_plugin::message::LogInfoPoll,
    cc_plugin::message::LogRetrieve,
    cc_plugin::message::LogRetrievepos,
    cc_plugin::message::LogRetrievestring,
    cc_plugin::message::LogFindtimeCmd,
    cc_plugin::message::LogFindtime,
    cc_plugin::message::LogRetrieveposextra,
    cc_plugin::message::SecSign,
    cc_plugin::message::SecUniqid
>;

}  // namespace cc_plugin

}  // namespace ublox





