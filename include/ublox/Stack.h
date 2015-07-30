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

#include "comms/comms.h"

#include "Message.h"
#include "RegularMessages.h"
#include "protocol/ChecksumCalc.h"

namespace ublox
{

template <typename TField>
using SyncField1 =
    comms::field::IntValue<
        TField,
        std::uint8_t,
        comms::option::DefaultNumValue<0xb5>,
        comms::option::ValidNumValueRange<0xb5, 0xb5>
    >;

template <typename TField>
using SyncField2 =
    comms::field::IntValue<
        TField,
        std::uint8_t,
        comms::option::DefaultNumValue<0x62>,
        comms::option::ValidNumValueRange<0x62, 0x62>
    >;

template <typename TField>
using ChecksumField =
    comms::field::IntValue<
        TField,
        std::uint16_t
    >;

template <typename TField>
using LengthField =
    comms::field::IntValue<
        TField,
        std::uint16_t
    >;

template <typename TField, typename... TOptions>
using DataField =
    comms::field::ArrayList<
        TField,
        std::uint8_t,
        TOptions...
    >;

template <
    typename TMsgBase = Message,
    typename TMessages = RegularMessages<TMsgBase>,
    typename TMsgAllocOptions = std::tuple<>,
    typename TDataFieldStorageOptions = std::tuple<> >
using Stack =
    comms::protocol::SyncPrefixLayer<
        SyncField1<typename TMsgBase::Field>,
        comms::protocol::SyncPrefixLayer<
            SyncField2<typename TMsgBase::Field>,
            comms::protocol::ChecksumLayer<
                ChecksumField<typename TMsgBase::Field>,
                protocol::ChecksumCalc,
                comms::protocol::MsgIdLayer<
                    ublox::field::MsgId,
                    TMessages,
                    comms::protocol::MsgSizeLayer<
                        LengthField<typename TMsgBase::Field>,
                        comms::protocol::MsgDataLayer<
                            TMsgBase,
                            DataField<typename TMsgBase::Field, TDataFieldStorageOptions>
                        >
                    >,
                    TMsgAllocOptions
                >
            >
        >
    >;


}  // namespace ublox



