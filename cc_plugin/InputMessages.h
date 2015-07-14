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

#include "cc_plugin/message/AckNak.h"
#include "cc_plugin/message/AckAck.h"

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
    cc_plugin::message::AckNak,
    cc_plugin::message::AckAck
> InputMessages;

}  // namespace cc_plugin

}  // namespace ublox




