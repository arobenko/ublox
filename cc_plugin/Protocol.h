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

#include "comms_champion/comms_champion.h"
#include "cc_plugin/Stack.h"
#include "cc_plugin/TransportMessage.h"
#include "cc_plugin/RawDataMessage.h"

namespace ublox
{

namespace cc_plugin
{

class Protocol : public
    comms_champion::ProtocolBase<
        cc_plugin::Stack,
        cc_plugin::TransportMessage,
        RawDataMessage >
{
    typedef comms_champion::ProtocolBase<
        cc_plugin::Stack,
        cc_plugin::TransportMessage,
        RawDataMessage > Base;
public:
    Protocol() = default;
    virtual ~Protocol();

protected:
    virtual const std::string& nameImpl() const override;
    virtual MessagesList createAllMessagesImpl() override;
    virtual comms_champion::MessageInfo::MessagePtr cloneMessageImpl(
        const Message& msg) override;
    virtual comms_champion::MessageInfoPtr createMessageImpl(const QString& idAsString) override;

private:
    comms_champion::MessageInfo::MessagePtr createPollMsg(Message::MsgIdType id);

    comms_champion::MessageInfo::MessagePtr createMessageInternal(const QString& idAsString);
};

}  // namespace cc_plugin

}  // namespace ublox


