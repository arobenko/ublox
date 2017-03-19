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
#include <QtCore/QVariantList>
#include <QtCore/QVariantMap>
CC_ENABLE_WARNINGS()

namespace ublox
{

namespace cc_plugin
{

namespace field
{

namespace common
{

const QVariantList& emptyProperties();
const QVariantMap& props_iTOW();
const QVariantMap& props_week();
const QVariantMap& props_numSV();
const QVariantMap& props_svid();
const QVariantMap& props_reserved(unsigned idx);
const QVariantMap& props_gnssId();

QVariantMap createProps_reservedBundle(unsigned resIdx, unsigned elemCount);
QVariantMap createProps_reservedBundleTwoParts(unsigned idx);
QVariantMap createProps_utcStandard(bool serialisedHidden = false);


}  // namespace common

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox


