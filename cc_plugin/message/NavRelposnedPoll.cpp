//
// Copyright 2017 (C). Alex Robenko. All rights reserved.
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

#include "NavRelposnedPoll.h"

template class ublox::message::NavRelposnedPoll<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavRelposnedPoll<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavRelposnedPoll>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

NavRelposnedPoll::NavRelposnedPoll() = default;
NavRelposnedPoll::~NavRelposnedPoll() = default;

NavRelposnedPoll& NavRelposnedPoll::operator=(const NavRelposnedPoll&) = default;
NavRelposnedPoll& NavRelposnedPoll::operator=(NavRelposnedPoll&&) = default;

const char* NavRelposnedPoll::nameImpl() const
{
    static const char* Str = "NAV-RELPOSNED (Poll)";
    return Str;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

