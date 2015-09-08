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

#include <QtCore/QVariantMap>

namespace ublox
{

namespace cc_plugin
{

namespace field
{

namespace cfg
{

const QVariantMap& props_portID();
const QVariantMap& props_readOnlyPortID();
const QVariantMap& props_txReady();
const QVariantMap& props_inProtoMask();
const QVariantMap& props_outProtoMask();
const QVariantMap& props_prtFlags();
const QVariantMap& props_protocolID();
const QVariantMap& props_datumNum();
const QVariantMap& props_datumName();
const QVariantMap& props_datMajA();
const QVariantMap& props_datFlat();
const QVariantMap& props_datDX();
const QVariantMap& props_datDY();
const QVariantMap& props_datDZ();
const QVariantMap& props_datRotX();
const QVariantMap& props_datRotY();
const QVariantMap& props_datRotZ();
const QVariantMap& props_datScale();

}  // namespace cfg

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox

