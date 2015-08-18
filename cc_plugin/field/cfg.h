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

const QVariantMap& portIdProperties();
const QVariantMap& prtModeProperties();
const QVariantMap& baudrateProperties();
const QVariantMap& inProtoMaskProperties();
const QVariantMap& outProtoMaskProperties();
const QVariantMap& prtFlagsProperties();
const QVariantMap& rateProperties();
QVariantMap rateProperties(unsigned idx);
const QVariantMap& protocolIdProperties();
QVariantMap infMsgMaskProperties(unsigned idx);
const QVariantMap& navBbrProperties();
const QVariantMap& resetProperties();
const QVariantMap& datumNumProperties();
const QVariantMap& datumProperties();
const QVariantMap& majXProperties();
const QVariantMap& flatProperties();
const QVariantMap& dXProperties();
const QVariantMap& dYProperties();
const QVariantMap& dZProperties();
const QVariantMap& rotXProperties();
const QVariantMap& rotYProperties();
const QVariantMap& rotZProperties();
const QVariantMap& scaleProperties();
const QVariantMap& intervalProperties();
const QVariantMap& lengthProperties();
const QVariantMap& statusProperties();
const QVariantMap& timeRefProperties();
const QVariantMap& antennaCableDelayProperties();
const QVariantMap& rfGroupDelayProperties();
const QVariantMap& userDelayProperties();

}  // namespace cfg

}  // namespace field

}  // namespace cc_plugin

}  // namespace ublox

