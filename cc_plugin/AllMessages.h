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
#include "cc_plugin/message/NavPosecefPoll.h"
#include "cc_plugin/message/NavPosllh.h"
#include "cc_plugin/message/NavPosllhPoll.h"
#include "cc_plugin/message/NavDop.h"
#include "cc_plugin/message/NavDopPoll.h"
#include "cc_plugin/message/NavPosutm.h"
#include "cc_plugin/message/NavPosutmPoll.h"

#include "cc_plugin/message/AckNak.h"
#include "cc_plugin/message/AckAck.h"

namespace ublox
{

namespace cc_plugin
{

typedef std::tuple<
    cc_plugin::message::NavPosecef,
    cc_plugin::message::NavPosecefPoll,
    cc_plugin::message::NavPosllh,
    cc_plugin::message::NavPosllhPoll,
    cc_plugin::message::NavDop,
    cc_plugin::message::NavDopPoll,
    cc_plugin::message::NavPosutm,
    cc_plugin::message::NavPosutmPoll,
    cc_plugin::message::AckNak,
    cc_plugin::message::AckAck
> AllMessages;

}  // namespace cc_plugin

}  // namespace ublox




