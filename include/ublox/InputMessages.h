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
#include "message/NavPosutm.h"
#include "message/NavVelecef.h"
#include "message/NavVelned.h"
#include "message/NavTimegps.h"
#include "message/NavTimeutc.h"
#include "message/NavClock.h"
#include "message/NavSvinfo.h"

#include "message/AckNak.h"
#include "message/AckAck.h"


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
        message::NavPosutm<TMessage>,
        message::NavVelecef<TMessage>,
        message::NavVelned<TMessage>,
        message::NavTimegps<TMessage>,
        message::NavTimeutc<TMessage>,
        message::NavClock<TMessage>,
        message::NavSvinfo<TMessage>,
        message::AckNak<TMessage>,
        message::AckAck<TMessage>
    >;

}  // namespace ublox
