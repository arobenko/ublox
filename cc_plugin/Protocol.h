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


#pragma once

#include <memory>
#include "comms_champion/comms_champion.h"

namespace ublox
{

namespace cc_plugin
{

class ProtocolImpl;
class Protocol : public comms_champion::Protocol
{
public:
    Protocol();
    virtual ~Protocol();

protected:
    virtual const QString& nameImpl() const override;
    virtual MessagesList readImpl(const comms_champion::DataInfo& dataInfo, bool final) override;
    virtual comms_champion::DataInfoPtr writeImpl(comms_champion::Message& msg) override;
    virtual MessagesList createAllMessagesImpl() override;
    virtual comms_champion::MessagePtr createMessageImpl(const QString& idAsString, unsigned idx) override;
    virtual UpdateStatus updateMessageImpl(comms_champion::Message& msg) override;
    virtual comms_champion::MessagePtr cloneMessageImpl(const comms_champion::Message& msg) override;
    virtual comms_champion::MessagePtr createInvalidMessageImpl() override;
    virtual comms_champion::MessagePtr createRawDataMessageImpl() override;
    virtual comms_champion::MessagePtr createExtraInfoMessageImpl() override;

private:
    std::unique_ptr<ProtocolImpl> m_pImpl;
};

}  // namespace cc_plugin

}  // namespace ublox

