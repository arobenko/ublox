//
// Copyright 2015 - 2017 (C). Alex Robenko. All rights reserved.
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

#include "comms_champion/comms_champion.h"
#include "ublox/message/CfgTp5Poll.h"
#include "cc_plugin/Message.h"
#include "cc_plugin/ProtocolMessageBase.h"

namespace ublox
{

namespace cc_plugin
{

namespace message
{

class CfgTp5Poll : public
    ProtocolMessageBase<
        ublox::message::CfgTp5Poll<ublox::cc_plugin::Message>,
        CfgTp5Poll>
{
public:
    CfgTp5Poll();
    CfgTp5Poll(const CfgTp5Poll&) = delete;
    CfgTp5Poll(CfgTp5Poll&&) = delete;
    virtual ~CfgTp5Poll();

    CfgTp5Poll& operator=(const CfgTp5Poll&);
    CfgTp5Poll& operator=(CfgTp5Poll&&);

protected:
    virtual const char* nameImpl() const override;
};

}  // namespace message

}  // namespace cc_plugin

}  // namespace ublox

extern template class ublox::message::CfgTp5Poll<ublox::cc_plugin::Message>;
extern template class ublox::cc_plugin::ProtocolMessageBase<
    ublox::message::CfgTp5Poll<ublox::cc_plugin::Message>,
    ublox::cc_plugin::message::CfgTp5Poll>;

