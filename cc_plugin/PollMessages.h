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

#include "cc_plugin/message/NavPosecefPoll.h"
#include "cc_plugin/message/NavPosllhPoll.h"
#include "cc_plugin/message/NavStatusPoll.h"
#include "cc_plugin/message/NavDopPoll.h"
#include "cc_plugin/message/NavSolPoll.h"
#include "cc_plugin/message/NavPosutmPoll.h"
#include "cc_plugin/message/NavVelecefPoll.h"
#include "cc_plugin/message/NavVelnedPoll.h"
#include "cc_plugin/message/NavTimegpsPoll.h"
#include "cc_plugin/message/NavTimeutcPoll.h"

namespace ublox
{

namespace cc_plugin
{

typedef std::tuple<
    cc_plugin::message::NavPosecefPoll,
    cc_plugin::message::NavPosllhPoll,
    cc_plugin::message::NavStatusPoll,
    cc_plugin::message::NavDopPoll,
    cc_plugin::message::NavSolPoll,
    cc_plugin::message::NavPosutmPoll,
    cc_plugin::message::NavVelecefPoll,
    cc_plugin::message::NavVelnedPoll,
    cc_plugin::message::NavTimegpsPoll,
    cc_plugin::message::NavTimeutcPoll
> PollMessages;

}  // namespace cc_plugin

}  // namespace ublox




