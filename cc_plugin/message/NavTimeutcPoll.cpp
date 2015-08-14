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

#include "NavTimeutcPoll.h"

template class ublox::message::NavTimeutcPoll<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::NavTimeutcPoll<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::NavTimeutcPoll>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

NavTimeutcPoll::NavTimeutcPoll() = default;
NavTimeutcPoll::~NavTimeutcPoll() = default;

NavTimeutcPoll& NavTimeutcPoll::operator=(const NavTimeutcPoll&) = default;
NavTimeutcPoll& NavTimeutcPoll::operator=(NavTimeutcPoll&&) = default;


const char* NavTimeutcPoll::nameImpl() const
{
    static const char* Str = "NAV-TIMEUTC (Poll)";
    return Str;
}

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

