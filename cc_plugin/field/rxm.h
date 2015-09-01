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

namespace rxm
{

const QVariantMap& props_week();
const QVariantMap& props_numSV();
const QVariantMap& props_svid();


// TODO: remove

const QVariantMap& itowProperties();
const QVariantMap& weekProperties();
const QVariantMap& nsvProperties();
const QVariantMap& cpMesProperties();
const QVariantMap& prMesProperties();
const QVariantMap& doMesProperties();
const QVariantMap& svProperties();
const QVariantMap& mesQiProperties();
const QVariantMap& cnoProperties();
const QVariantMap& lliProperties();
const QVariantMap& numVisProperties();
const QVariantMap& numSvProperties();
const QVariantMap& svidProperties();
const QVariantMap& statusInfoSvFlagProperties();
const QVariantMap& azimProperties();
const QVariantMap& elevProperties();
const QVariantMap& ageProperties();
const QVariantMap& chnProperties();
QVariantMap dwordProperties(unsigned idx);
const QVariantMap& howProperties();
QVariantMap sfxdxProperties(unsigned idx1, unsigned idx2);

}  // namespace rxm

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox


