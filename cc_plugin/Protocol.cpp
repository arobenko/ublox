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

#include "Protocol.h"

#include "cc_plugin/Stack.h"
#include "cc_plugin/TransportMessage.h"

namespace cc = comms_champion;

namespace ublox
{

namespace cc_plugin
{

class ProtocolImpl : public
    comms_champion::ProtocolBase<
        cc_plugin::Stack,
        cc_plugin::TransportMessage
    >
{
    typedef comms_champion::ProtocolBase<
        cc_plugin::Stack,
        cc_plugin::TransportMessage
    > Base;
public:
    friend class ublox::cc_plugin::Protocol;

    ProtocolImpl() = default;
    virtual ~ProtocolImpl() = default;

protected:
    virtual const QString& nameImpl() const override
    {
        static const QString Str("UBlox");
        return Str;
    }

    using Base::createInvalidMessageImpl;
    using Base::createRawDataMessageImpl;
    using Base::createExtraInfoMessageImpl;
};


Protocol::Protocol()
  : m_pImpl(new ProtocolImpl())
{
}

Protocol::~Protocol() = default;

const QString& Protocol::nameImpl() const
{
    return m_pImpl->name();
}

Protocol::MessagesList Protocol::readImpl(const comms_champion::DataInfo& dataInfo, bool final)
{
    return m_pImpl->read(dataInfo, final);
}

comms_champion::DataInfoPtr Protocol::writeImpl(cc::Message& msg)
{
    return m_pImpl->write(msg);
}

Protocol::MessagesList Protocol::createAllMessagesImpl()
{
    return m_pImpl->createAllMessages();
}

cc::MessagePtr Protocol::createMessageImpl(const QString& idAsString, unsigned idx)
{
    return static_cast<cc::Protocol*>(m_pImpl.get())->createMessage(idAsString, idx);
}

Protocol::UpdateStatus Protocol::updateMessageImpl(cc::Message& msg)
{
    return m_pImpl->updateMessage(msg);
}

cc::MessagePtr Protocol::cloneMessageImpl(const cc::Message& msg)
{
    return m_pImpl->cloneMessage(msg);
}

cc::MessagePtr Protocol::createInvalidMessageImpl()
{
    return m_pImpl->createInvalidMessageImpl();
}

cc::MessagePtr Protocol::createRawDataMessageImpl()
{
    return m_pImpl->createRawDataMessageImpl();
}

comms_champion::MessagePtr Protocol::createExtraInfoMessageImpl()
{
    return m_pImpl->createExtraInfoMessageImpl();
}

}  // namespace cc_plugin

}  // namespace ublox


