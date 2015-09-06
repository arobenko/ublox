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

#include <iterator>

#include "comms/Message.h"
#include "ublox/Message.h"

#include "ublox/field/cfg.h"

namespace ublox
{

namespace message
{

using CfgPrt_PortId = field::cfg::PortId;

enum
{
    CfgPrt_txReady_en,
    CfgPrt_txReady_pol,
    CfgPrt_txReady_pin,
    CfgPrt_txReady_thres,
    CfgPrt_txReady_numOfValues
};

enum
{
    CfgPrt_inProtoMask_inUbx,
    CfgPrt_inProtoMask_inNmea,
    CfgPrt_inProtoMask_inRtcm,
    CfgPrt_inProtoMask_numOfValues
};

enum
{
    CfgPrt_outProtoMask_outUbx,
    CfgPrt_outProtoMask_outNmea,
    CfgPrt_outProtoMask_numOfValues
};

enum
{
    CfgPrt_flags_reserved,
    CfgPrt_flags_extendedTxTimeout,
    CfgPrt_flags_numOfValues
};

}  // namespace message

}  // namespace ublox





