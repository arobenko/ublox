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

namespace ublox
{

namespace cc_plugin
{

template <typename TMsgBase, typename TActualMsg>
class ProtocolMessageBase : public comms_champion::ProtocolMessageBase<TMsgBase, TActualMsg>
{
    typedef comms_champion::ProtocolMessageBase<TMsgBase, TActualMsg> Base;
public:
    ProtocolMessageBase() = default;
    ProtocolMessageBase(const ProtocolMessageBase&) = default;
    ProtocolMessageBase(ProtocolMessageBase&&) = default;
    virtual ~ProtocolMessageBase() = default;

    ProtocolMessageBase& operator=(const ProtocolMessageBase&) = default;
    ProtocolMessageBase& operator=(ProtocolMessageBase&&) = default;

protected:
    virtual QString idAsStringImpl() const override
    {
        auto fullId = Base::getId();
        uint idNum = static_cast<std::uint8_t>(fullId);
        uint classNum = static_cast<std::uint8_t>(fullId >> 8);
        return QString("0x%1-0x%2")
            .arg(classNum, 2, 16, QChar('0'))
            .arg(idNum, 2, 16, QChar('0'));
    }

};

}  // namespace cc_plugin

}  // namespace ublox


