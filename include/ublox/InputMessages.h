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

#include "Message.h"

#include "message/NavPosecef.h"
#include "message/NavPosllh.h"
#include "message/NavStatus.h"
#include "message/NavDop.h"
#include "message/NavSol.h"
#include "message/NavPvt.h"
#include "message/NavVelecef.h"
#include "message/NavVelned.h"
#include "message/NavTimegps.h"
#include "message/NavTimeutc.h"
#include "message/NavClock.h"
#include "message/NavSvinfo.h"
#include "message/NavDgps.h"
#include "message/NavSbas.h"
#include "message/NavEkfstatus.h"
#include "message/NavAopstatus.h"

#include "message/RxmRaw.h"
#include "message/RxmSfrb.h"
#include "message/RxmSvsi.h"
#include "message/RxmAlm.h"
#include "message/RxmEph.h"
#include "message/RxmPosreq.h"

#include "message/InfError.h"
#include "message/InfWarning.h"
#include "message/InfNotice.h"
#include "message/InfTest.h"
#include "message/InfDebug.h"
#include "message/InfUser.h"

#include "message/AckNak.h"
#include "message/AckAck.h"

#include "message/CfgPrt.h"
#include "message/CfgMsg.h"
#include "message/CfgMsgCurrent.h"
#include "message/CfgInf.h"
#include "message/CfgRst.h"
#include "message/CfgDat.h"
#include "message/CfgTp.h"
#include "message/CfgRate.h"
#include "message/CfgFxn.h"
#include "message/CfgTm.h"
#include "message/CfgRxm.h"

namespace ublox
{

template <typename TMessage = Message>
using InputMessages =
    std::tuple<
        message::NavPosecef<TMessage>,
        message::NavPosllh<TMessage>,
        message::NavStatus<TMessage>,
        message::NavDop<TMessage>,
        message::NavSol<TMessage>,
        message::NavPvt<TMessage>,
        message::NavVelecef<TMessage>,
        message::NavVelned<TMessage>,
        message::NavTimegps<TMessage>,
        message::NavTimeutc<TMessage>,
        message::NavClock<TMessage>,
        message::NavSvinfo<TMessage>,
        message::NavDgps<TMessage>,
        message::NavSbas<TMessage>,
        message::NavEkfstatus<TMessage>,
        message::NavAopstatus<TMessage>/*,
        message::RxmRaw<TMessage>,
        message::RxmSfrb<TMessage>,
        message::RxmSvsi<TMessage>,
        message::RxmAlm<TMessage>,
        message::RxmEph<TMessage>,
        message::RxmPosreq<TMessage>,
        message::InfError<TMessage>,
        message::InfWarning<TMessage>,
        message::InfNotice<TMessage>,
        message::InfTest<TMessage>,
        message::InfDebug<TMessage>,
        message::InfUser<TMessage>,
        message::AckNak<TMessage>,
        message::AckAck<TMessage>,
        message::CfgPrt<TMessage>,
        message::CfgMsg<TMessage>,
        message::CfgMsgCurrent<TMessage>,
        message::CfgInf<TMessage>,
        message::CfgRst<TMessage>,
        message::CfgDat<TMessage>,
        message::CfgTp<TMessage>,
        message::CfgRate<TMessage>,
        message::CfgFxn<TMessage>,
        message::CfgTm<TMessage>,
        message::CfgRxm<TMessage>*/
    >;

}  // namespace ublox
