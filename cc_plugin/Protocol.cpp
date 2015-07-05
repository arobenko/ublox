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

#include "Protocol.h"

#include "comms/comms.h"

#include "AllMessages.h"
#include "PollMessages.h"

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

Protocol::~Protocol() = default;

const std::string& Protocol::nameImpl() const
{
    static const std::string Str("UBlox");
    return Str;
}

Protocol::MessagesList Protocol::createAllMessagesImpl()
{
    return Base::createAllMessagesInTuple<cc_plugin::AllMessages>();
}

cc::MessageInfo::MessagePtr Protocol::cloneMessageImpl(
        const Message& msg)
{
    static const QString PollSuffix("-Poll");
    auto fullIdStr = msg.idAsString();
    auto pollIdx = fullIdStr.indexOf(PollSuffix);
    if (pollIdx < 0) {
        return Base::cloneMessageImpl(msg);
    }

    cc::MessageInfo::MessagePtr clonedMsg;
    do {
        auto idStr = fullIdStr.left(pollIdx);
        bool ok = false;
        auto idNum = static_cast<Message::MsgIdType>(idStr.toUInt(&ok, 16));
        if (!ok) {
            break;
        }

        auto pollLenStr = fullIdStr.right(fullIdStr.size() - (pollIdx + PollSuffix.size()));
        if (pollLenStr.isEmpty()) {
            clonedMsg = createPollMsg(idNum);
            break;
        }

        assert(!"NYI");
    } while (false);

    if (clonedMsg) {
        clonedMsg->assign(msg);
    }

    return clonedMsg;
}

cc::MessageInfo::MessagePtr Protocol::createPollMsg(Message::MsgIdType id)
{
    static const comms::MsgFactory<Message, PollMessages> Factory;
    auto msg = Factory.createMsg(id);
    if (!msg) {
        assert(!"Attempt to create unknown message");
        return cc::MessageInfo::MessagePtr();
    }

    return cc::MessageInfo::MessagePtr(msg.release());
}

}  // namespace cc_plugin

}  // namespace ublox


