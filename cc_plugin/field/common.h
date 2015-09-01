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

#include <QtCore/QVariantList>
#include <QtCore/QVariantMap>

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
const QVariantMap& props_reserved(unsigned idx);

// TODO: remove

const QVariantMap& resProperties();
const QVariantMap& resProperties(unsigned idx);
const QVariantMap& padProperties();
const QVariantMap& itowProperties();
const QVariantMap& svidProperties();
const QVariantMap& elevProperties();
const QVariantMap& azimProperties();


}  // namespace common

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox


