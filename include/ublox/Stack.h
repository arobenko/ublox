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

/// @file
/// @brief Contains definition of transport layers protocol stack of ublox
///     binary protocol.

#pragma once

#include "comms/comms.h"

#include "Message.h"
#include "field/MsgId.h"
#include "protocol/ChecksumCalc.h"

namespace ublox
{

namespace details
{

/// @brief Field representing first byte in synchronisation information in
///     message wrapping.
/// @details <b>SYNC CHAR 1</b> with value 0xb5 as described in UBX protocol
///     specification.
template <typename TField>
using SyncField1 =
    comms::field::IntValue<
        TField,
        std::uint8_t,
        comms::option::DefaultNumValue<0xb5>,
        comms::option::ValidNumValueRange<0xb5, 0xb5>
    >;

/// @brief Field representing second byte in synchronisation information in
///     message wrapping.
/// @details <b>SYNC CHAR 2</b> with value 0x62 as described in UBX protocol
///     specification.
template <typename TField>
using SyncField2 =
    comms::field::IntValue<
        TField,
        std::uint8_t,
        comms::option::DefaultNumValue<0x62>,
        comms::option::ValidNumValueRange<0x62, 0x62>
    >;

/// @brief Field representing last two checksum bytes in message wrapping.
/// @details @b CK_A and @b CK_B as described in UBX protocol specification.
template <typename TField>
using ChecksumField =
    comms::field::IntValue<
        TField,
        std::uint16_t
    >;

/// @brief Field representing remaining length in message wrapping.
/// @details @b LENGTH as sescribed in UBX protocol specification.
template <typename TField>
using LengthField =
    comms::field::IntValue<
        TField,
        std::uint16_t
    >;

/// @brief Field representing full message payload.
template <typename TField, typename... TOptions>
using DataField =
    comms::field::ArrayList<
        TField,
        std::uint8_t,
        TOptions...
    >;

} // namespace details

/// @brief Definition of Ublox binary protocol stack of layers.
/// @details It is used to process incoming binary stream of data and create
///     allocate message objects for received messages. It also responsible to
///     serialise outgoing messages and wrap their payload with appropriate transport
///     information. See <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/page_prot_stack_tutorial.html">Protocol Stack Tutorial</a>
///     page in @b COMMS library tutorial for more information.@n
///     The outermost layer is
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1protocol_1_1SyncPrefixLayer.html">comms::protocol::SyncPrefixLayer</a>.
///     Please see its documentation for public interface description.
/// @tparam TMsgBase Interface class for all the messages, expected to be some
///     variant of ublox::MessageT class with options.
/// @tparam TMessages Types of all messages that this protocol stack must
///     identify during read and support creation of proper message object.
///     The types of the messages must be bundled in
///     <a href="http://en.cppreference.com/w/cpp/utility/tuple">std::tuple</a>.
/// @tparam TMsgAllocOptions The contents of this template parameter are passed
///     as options to
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1protocol_1_1MsgIdLayer.html">comms::protocol::MsgIdLayer</a>
///     protocol layer in @b COMMS library. They are used to specify whether
///     dynamic memory allocation is allowed or "in place" allocation for
///     message objects must be implemented. It is expected to be either
///     single @b COMMS library option or multiple options bundled in
///     <a href="http://en.cppreference.com/w/cpp/utility/tuple">std::tuple</a>.
/// @tparam TDataFieldStorageOptions The contents of this template parameters
///     are passed to the definition of storage field of
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1protocol_1_1MsgDataLayer.html">comms::protocol::MsgDataLayer</a>
///     layer. The field is a variant of
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1field_1_1ArrayList.html">comms::field::ArrayList</a>
///     which uses <a href="http://en.cppreference.com/w/cpp/container/vector">std::vector</a>
///     as its internal storage by default. The option(s) specified in this
///     template parameter is/are forwarded to the definition of the storage
///     field (comms::field::ArrayList).
template <
    typename TMsgBase,
    typename TMessages,
    typename TMsgAllocOptions = std::tuple<>,
    typename TDataFieldStorageOptions = std::tuple<> >
using Stack =
    comms::protocol::SyncPrefixLayer<
        details::SyncField1<typename TMsgBase::Field>,
        comms::protocol::SyncPrefixLayer<
            details::SyncField2<typename TMsgBase::Field>,
            comms::protocol::ChecksumLayer<
                details::ChecksumField<typename TMsgBase::Field>,
                protocol::ChecksumCalc,
                comms::protocol::MsgIdLayer<
                    ublox::field::MsgId,
                    TMessages,
                    comms::protocol::MsgSizeLayer<
                        details::LengthField<typename TMsgBase::Field>,
                        comms::protocol::MsgDataLayer<
                            TMsgBase,
                            details::DataField<typename TMsgBase::Field, TDataFieldStorageOptions>
                        >
                    >,
                    TMsgAllocOptions
                >
            >
        >
    >;


}  // namespace ublox



