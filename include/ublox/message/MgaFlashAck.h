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

/// @file
/// @brief Contains definition of MGA-FLASH-ACK message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-FLASH-ACK message fields.
/// @see MgaFlashAck
struct MgaFlashAckFields
{

    /// @brief Definition of "type" field.
    using type  =
    field::common::U1T<
        comms::option::ValidNumValueRange<3, 3>,
        comms::option::DefaultNumValue<3>,
        comms::option::FailOnInvalid
    >;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Enumeration value for @ref ack field.
    enum class Ack : std::uint8_t
    {
        Ack, ///< Message received and written to flash
        NackRetransmit, ///< Retransmission required
        NackGivup, ///< Give up
        NumOfValues ///< number of available values
    };

    /// @brief Definition of "ack" field.
    using ack =
        field::common::EnumT<
            Ack,
            comms::option::ValidNumValueRange<0, (int)Ack::NumOfValues - 1>
        >;
    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "sequence" field.
    using sequence = field::common::res2;


    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        ack,
        reserved1,
        sequence
    >;
};

/// @brief Definition of MGA-FLASH-ACK message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaFlashAckFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaFlashAck : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_FLASH>,
        comms::option::FieldsImpl<MgaFlashAckFields::All>,
        comms::option::MsgType<MgaFlashAck<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaFlashAckFields::type field
    ///     @li @b version for @ref MgaFlashAckFields::version field
    ///     @li @b ack for @ref MgaFlashAckFields::ack field
    ///     @li @b reserved1 for @ref MgaFlashAckFields::reserved1 field
    ///     @li @b sequence for @ref MgaFlashAckFields::sequence field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        ack,
        reserved1,
        sequence
    );

    /// @brief Default constructor
    MgaFlashAck() = default;

    /// @brief Copy constructor
    MgaFlashAck(const MgaFlashAck&) = default;

    /// @brief Move constructor
    MgaFlashAck(MgaFlashAck&& other) = default;

    /// @brief Destructor
    ~MgaFlashAck() = default;

    /// @brief Copy assignment
    MgaFlashAck& operator=(const MgaFlashAck&) = default;

    /// @brief Move assignment
    MgaFlashAck& operator=(MgaFlashAck&&) = default;
};


}  // namespace message

}  // namespace ublox





