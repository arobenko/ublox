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
    cc::MessageInfo::MessagePtr clonedMsg = createMessageInternal(msg.idAsString());
    if (!clonedMsg) {
        return Base::cloneMessageImpl(msg);
    }
    clonedMsg->assign(msg);
    return clonedMsg;
}

cc::MessageInfoPtr Protocol::createMessageImpl(const QString& idAsString)
{
    auto clonedMsg = createMessageInternal(idAsString);
    if (!clonedMsg) {
        return Base::createMessageImpl(idAsString);
    }

    auto msgInfo = cc::makeMessageInfo();
    msgInfo->setAppMessage(std::move(clonedMsg));
    updateMessageInfo(*msgInfo);
    return msgInfo;
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

cc::MessageInfo::MessagePtr Protocol::createMessageInternal(const QString& idAsString)
{
    static const QString PollSuffix("-Poll");
    auto pollIdx = idAsString.indexOf(PollSuffix);
    if (pollIdx < 0) {
        return cc::MessageInfo::MessagePtr();
    }

    cc::MessageInfo::MessagePtr msg;
    do {
        auto idStr = idAsString.left(pollIdx);
        bool ok = false;
        auto idNum = static_cast<Message::MsgIdType>(idStr.toUInt(&ok, 16));
        if (!ok) {
            break;
        }

        auto pollLenStr = idAsString.right(idAsString.size() - (pollIdx + PollSuffix.size()));
        if (pollLenStr.isEmpty()) {
            msg = createPollMsg(idNum);
            break;
        }

        assert(!"NYI");
    } while (false);

    return msg;
}

}  // namespace cc_plugin

}  // namespace ublox


