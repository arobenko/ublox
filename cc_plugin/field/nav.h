//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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

#include "comms/CompileControl.h"

CC_DISABLE_WARNINGS()
#include <QtCore/QVariantMap>
CC_ENABLE_WARNINGS()

namespace ublox
{

namespace cc_plugin
{

namespace field
{

namespace nav
{

const QVariantMap& props_iTOW();
const QVariantMap& props_fTOW();
const QVariantMap& props_ecefX();
const QVariantMap& props_ecefY();
const QVariantMap& props_ecefZ();
const QVariantMap& props_ecefVX();
const QVariantMap& props_ecefVY();
const QVariantMap& props_ecefVZ();
const QVariantMap& props_pAcc();
const QVariantMap& props_sAcc();
const QVariantMap& props_lon();
const QVariantMap& props_lat();
const QVariantMap& props_height();
const QVariantMap& props_hMSL();
const QVariantMap& props_hAcc();
const QVariantMap& props_vAcc();
const QVariantMap& props_gpsFix();
const QVariantMap& props_fixType();
QVariantMap createProps_xDOP(char prefix);
const QVariantMap& props_pDOP();
const QVariantMap& props_week();
const QVariantMap& props_numSV();
const QVariantMap& props_year();
const QVariantMap& props_month();
const QVariantMap& props_day();
const QVariantMap& props_hour();
const QVariantMap& props_min();
const QVariantMap& props_sec();
const QVariantMap& props_tAcc();
const QVariantMap& props_nano();
const QVariantMap& props_gSpeed();
const QVariantMap& props_heading();
const QVariantMap& props_velN();
const QVariantMap& props_velE();
const QVariantMap& props_velD();
const QVariantMap& props_numCh();
const QVariantMap& props_cnt();
const QVariantMap& props_svid();

}  // namespace nav

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox




