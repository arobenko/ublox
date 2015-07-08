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

namespace nav
{

const QVariantMap& itowProperties();
const QVariantMap& ecefPropertiesX();
const QVariantMap& ecefPropertiesY();
const QVariantMap& ecefPropertiesZ();
const QVariantMap& ecefPropertiesVX();
const QVariantMap& ecefPropertiesVY();
const QVariantMap& ecefPropertiesVZ();
const QVariantMap& paccProperties();
const QVariantMap& lonProperties();
const QVariantMap& latProperties();
const QVariantMap& heightProperties();
const QVariantMap& hmslProperties();
const QVariantMap& haccProperties();
const QVariantMap& vaccProperties();
const QVariantMap& eastProperties();
const QVariantMap& northProperties();
const QVariantMap& altProperties();
const QVariantMap& zoneProperties();
const QVariantMap& hemProperties();
const QVariantMap& gdopProperties();
const QVariantMap& pdopProperties();
const QVariantMap& tdopProperties();
const QVariantMap& vdopProperties();
const QVariantMap& hdopProperties();
const QVariantMap& ndopProperties();
const QVariantMap& edopProperties();
const QVariantMap& gpsFixProperties();
const QVariantMap& flagsProperties();
const QVariantMap& diffStatusProperties();
const QVariantMap& ttffProperties();
const QVariantMap& msssProperties();
const QVariantMap& fracProperties();
const QVariantMap& weekProperties();
const QVariantMap& saccProperties();
const QVariantMap& numSvProperties();

}  // namespace nav

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox



