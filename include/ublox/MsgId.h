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

#include <cstdint>

namespace ublox
{

enum MsgId : std::uint16_t
{
    MsgId_NAV_POSECEF = 0x0101,
    MsgId_NAV_POSLLH = 0x0102,
    MsgId_NAV_STATUS = 0x0103,
    MsgId_NAV_DOP = 0x0104,
    MsgId_NAV_SOL = 0x0106,
    MsgId_NAV_POSUTM = 0x0108,
    MsgId_NAV_VELECEF = 0x0111,
    MsgId_NAV_VELNED = 0x0112,
    MsgId_NAV_TIMEGPS = 0x0120,
    MsgId_NAV_TIMEUTC = 0x0121,
    MsgId_NAV_CLOCK = 0x0122,
    MsgId_NAV_SVINFO = 0x0130,
    MsgId_NAV_DGPS = 0x0131,
    MsgId_NAV_SBAS = 0x0132,
    MsgId_NAV_EKFSTATUS = 0x0140,
    MsgId_ACK_NAK = 0x0500,
    MsgId_ACK_ACK = 0x0501
};

}  // namespace ublox


