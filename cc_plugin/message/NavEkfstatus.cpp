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

#include <cassert>

#include "NavEkfstatus.h"
#include "cc_plugin/field/common.h"
#include "cc_plugin/field/nav.h"

template class ublox::message::NavEkfstatus<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavEkfstatus<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavEkfstatus>;


namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

namespace
{

QVariantList createFieldsProperties()
{
    QVariantList props;
    props.append(cc_plugin::field::nav::pulsesProperties());
    props.append(cc_plugin::field::nav::periodProperties());
    props.append(cc_plugin::field::nav::gyromeanProperties());
    props.append(cc_plugin::field::nav::temperatureProperties());
    props.append(cc_plugin::field::nav::directionProperties());
    props.append(cc_plugin::field::nav::calibStatusProperties());
    props.append(cc_plugin::field::nav::pulseScaleProperties());
    props.append(cc_plugin::field::nav::gyroBiasProperties());
    props.append(cc_plugin::field::nav::gyroScaleProperties());
    props.append(cc_plugin::field::nav::accPulseScaleProperties());
    props.append(cc_plugin::field::nav::accGyroBiasProperties());
    props.append(cc_plugin::field::nav::accGyroScaleProperties());
    props.append(cc_plugin::field::nav::measUsedProperties());
    props.append(cc_plugin::field::common::resProperties());

    assert(props.size() == NavEkfstatus::FieldIdx_NumOfValues);
    return props;
}

}  // namespace

NavEkfstatus::NavEkfstatus() = default;
NavEkfstatus::~NavEkfstatus() = default;

NavEkfstatus& NavEkfstatus::operator=(const NavEkfstatus&) = default;
NavEkfstatus& NavEkfstatus::operator=(NavEkfstatus&&) = default;

const char* NavEkfstatus::nameImpl() const
{
    static const char* Str = "NAV-EKFSTATUS";
    return Str;
}

const QVariantList& NavEkfstatus::fieldsPropertiesImpl() const
{
    static const auto Props = createFieldsProperties();
    return Props;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

