//
// Copyright 2015 - 2016 (C). Alex Robenko. All rights reserved.
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
#include "ublox/Message.h"


namespace ublox
{

namespace cc_plugin
{

using ExtraMessageOptions = std::tuple<
    comms::option::ValidCheckInterface,
    comms::option::LengthInfoInterface
>;

template <typename... TOptions>
class MessageT : public comms_champion::MessageBase<ublox::MessageT, ExtraMessageOptions, TOptions...>
{
    using Base = comms_champion::MessageBase<ublox::MessageT, ExtraMessageOptions, TOptions...>;
public:
    virtual ~MessageT() = default;

protected:

    virtual QString idAsStringImpl() const override
    {
        return QString("0x%1").arg(static_cast<unsigned>(Base::getId()), 4, 16, QChar('0'));
    }

    virtual const QVariantList& fieldsPropertiesImpl() const override
    {
        static const QVariantList Props;
        return Props;
    }
};

using Message = MessageT<>;

}  // namespace cc_plugin

}  // namespace ublox
