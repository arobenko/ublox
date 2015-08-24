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

const QVariantMap& props_iTOW();
const QVariantMap& props_ecefX();
const QVariantMap& props_ecefY();
const QVariantMap& props_ecefZ();
const QVariantMap& props_pAcc();
const QVariantMap& props_lon();
const QVariantMap& props_lat();
const QVariantMap& props_height();
const QVariantMap& props_hMSL();
const QVariantMap& props_hAcc();
const QVariantMap& props_vAcc();

// TODO: remove
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
const QVariantMap& velPropertiesN();
const QVariantMap& velPropertiesE();
const QVariantMap& velPropertiesD();
const QVariantMap& speedProperties();
const QVariantMap& groundSpeedProperties();
const QVariantMap& headingProperties();
const QVariantMap& caccProperties();
const QVariantMap& leapSecProperties();
const QVariantMap& timeValidProperties();
const QVariantMap& taccProperties();
const QVariantMap& nanoProperties();
const QVariantMap& yearProperties();
const QVariantMap& monthProperties();
const QVariantMap& dayProperties();
const QVariantMap& hourProperties();
const QVariantMap& minProperties();
const QVariantMap& secProperties();
const QVariantMap& clkbProperties();
const QVariantMap& clkdProperties();
const QVariantMap& faccProperties();
const QVariantMap& nchProperties();
const QVariantMap& svidProperties();
const QVariantMap& chNumProperties();
const QVariantMap& infoFlagsProperties();
const QVariantMap& qiProperties();
const QVariantMap& cnoProperties();
const QVariantMap& elevProperties();
const QVariantMap& azimProperties();
const QVariantMap& prresProperties();
const QVariantMap& ageProperties();
const QVariantMap& baseIdProperties();
const QVariantMap& baseHealthProperties();
const QVariantMap& dgpsStatusProperties();
const QVariantMap& dgpsFlagsProperties();
const QVariantMap& agechProperties();
const QVariantMap& prcProperties();
const QVariantMap& prrcProperties();
const QVariantMap& geoProperties();
const QVariantMap& modeProperties();
const QVariantMap& sysProperties();
const QVariantMap& serviceProperties();
const QVariantMap& cntProperties();
const QVariantMap& udreProperties();
const QVariantMap& icProperties();
const QVariantMap& pulsesProperties();
const QVariantMap& periodProperties();
const QVariantMap& gyromeanProperties();
const QVariantMap& temperatureProperties();
const QVariantMap& directionProperties();
const QVariantMap& calibStatusProperties();
const QVariantMap& pulseScaleProperties();
const QVariantMap& gyroBiasProperties();
const QVariantMap& gyroScaleProperties();
const QVariantMap& accPulseScaleProperties();
const QVariantMap& accGyroBiasProperties();
const QVariantMap& accGyroScaleProperties();
const QVariantMap& measUsedProperties();


}  // namespace nav

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox




