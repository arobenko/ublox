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

#include "CfgNavx5Poll.h"

template class ublox::message::CfgNavx5Poll<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgNavx5Poll<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgNavx5Poll>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

CfgNavx5Poll::CfgNavx5Poll() = default;
CfgNavx5Poll::~CfgNavx5Poll() = default;

CfgNavx5Poll& CfgNavx5Poll::operator=(const CfgNavx5Poll&) = default;
CfgNavx5Poll& CfgNavx5Poll::operator=(CfgNavx5Poll&&) = default;


const char* CfgNavx5Poll::nameImpl() const
{
    static const char* Str = "CFG-NAVX5 (Poll)";
    return Str;
}


}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

