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

#include "CfgTp5Poll.h"

template class ublox::message::CfgTp5Poll<ublox::cc_plugin::Message>;
template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgTp5Poll<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgTp5Poll>;

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

namespace message
{

CfgTp5Poll::CfgTp5Poll() = default;
CfgTp5Poll::~CfgTp5Poll() = default;

CfgTp5Poll& CfgTp5Poll::operator=(const CfgTp5Poll&) = default;
CfgTp5Poll& CfgTp5Poll::operator=(CfgTp5Poll&&) = default;


const char* CfgTp5Poll::nameImpl() const
{
    static const char* Str = "CFG-TP5 (Poll)";
    return Str;
}


}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

