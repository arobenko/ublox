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

#include "cc_plugin/message/NavPosecef.h"
#include "cc_plugin/message/NavPosllh.h"
#include "cc_plugin/message/NavStatus.h"
#include "cc_plugin/message/NavDop.h"
#include "cc_plugin/message/NavSol.h"
#include "cc_plugin/message/NavPosutm.h"
#include "cc_plugin/message/NavVelecef.h"
#include "cc_plugin/message/NavVelned.h"
#include "cc_plugin/message/NavTimegps.h"
#include "cc_plugin/message/NavTimeutc.h"
#include "cc_plugin/message/NavClock.h"
#include "cc_plugin/message/NavSvinfo.h"
#include "cc_plugin/message/NavDgps.h"
#include "cc_plugin/message/NavSbas.h"
#include "cc_plugin/message/NavEkfstatus.h"

#include "cc_plugin/message/RxmRaw.h"
#include "cc_plugin/message/RxmSfrb.h"
#include "cc_plugin/message/RxmSvsi.h"
#include "cc_plugin/message/RxmAlm.h"
#include "cc_plugin/message/RxmEph.h"
#include "cc_plugin/message/RxmPosreq.h"

#include "cc_plugin/message/InfError.h"
#include "cc_plugin/message/InfWarning.h"
#include "cc_plugin/message/InfNotice.h"
#include "cc_plugin/message/InfTest.h"
#include "cc_plugin/message/InfDebug.h"
#include "cc_plugin/message/InfUser.h"

#include "cc_plugin/message/AckNak.h"
#include "cc_plugin/message/AckAck.h"

#include "cc_plugin/message/CfgPrt.h"

namespace ublox
{

namespace cc_plugin
{

typedef std::tuple<
    cc_plugin::message::NavPosecef,
    cc_plugin::message::NavPosllh,
    cc_plugin::message::NavStatus,
    cc_plugin::message::NavDop,
    cc_plugin::message::NavSol,
    cc_plugin::message::NavPosutm,
    cc_plugin::message::NavVelecef,
    cc_plugin::message::NavVelned,
    cc_plugin::message::NavTimegps,
    cc_plugin::message::NavTimeutc,
    cc_plugin::message::NavClock,
    cc_plugin::message::NavSvinfo,
    cc_plugin::message::NavDgps,
    cc_plugin::message::NavSbas,
    cc_plugin::message::NavEkfstatus,
    cc_plugin::message::RxmRaw,
    cc_plugin::message::RxmSfrb,
    cc_plugin::message::RxmSvsi,
    cc_plugin::message::RxmAlm,
    cc_plugin::message::RxmEph,
    cc_plugin::message::RxmPosreq,
    cc_plugin::message::InfError,
    cc_plugin::message::InfWarning,
    cc_plugin::message::InfNotice,
    cc_plugin::message::InfTest,
    cc_plugin::message::InfDebug,
    cc_plugin::message::InfUser,
    cc_plugin::message::AckNak,
    cc_plugin::message::AckAck,
    cc_plugin::message::CfgPrt
> RegularMessages;

}  // namespace cc_plugin

}  // namespace ublox




