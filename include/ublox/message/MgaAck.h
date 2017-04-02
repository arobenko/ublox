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

/// @file
/// @brief Contains definition of MGA-ACK message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the MGA-ACK message fields.
/// @see MgaAck
struct MgaAckFields
{
    /// @brief Value enumeration for @ref type field.
    enum class Type : std::uint8_t
    {
        NotUsed, ///< message was not used
        Accepted, ///< message was accepted for use
        NumOfValues  /// number of available values
    };

    /// @brief Definition of "type" field.
    using type  =
        field::common::EnumT<
            Type,
            comms::option::ValidNumValueRange<0, (int)Type::NumOfValues - 1>
        >;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Value enumeration for @ref infoCode field.
    enum class InfoCode : std::uint8_t
    {
        DataAccepted, ///< The receiver accepted the data
        NoTime, ///< The receiver doesn't know the time
        BadVersion, ///< The message version is not supported by the receiver
        BadSize, ///< The message size does not match the message version
        DatabaseError, ///< The message data could not be stored to the database
        NotReady, ///< The receiver is not ready to use the message data
        UknownType, ///< The message type is unknow
        NumOfValues  /// number of available values
    };

    /// @brief Definition of "infoCode" field.
    using infoCode  =
        field::common::EnumT<
            InfoCode,
            comms::option::ValidNumValueRange<0, (int)InfoCode::NumOfValues - 1>
        >;


    /// @brief Definition of "msgId" field.
    using msgId = field::common::U1;

    /// @brief Definition of "msgPayloadStart" field.
    using msgPayloadStart = field::common::U4;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        type,
        version,
        infoCode,
        msgId,
        msgPayloadStart
    >;
};

/// @brief Definition of MGA-ACK message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref MgaAckFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class MgaAck : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_MGA_ACK>,
        comms::option::FieldsImpl<MgaAckFields::All>,
        comms::option::MsgType<MgaAck<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b type for @ref MgaAckFields::type field
    ///     @li @b version for @ref MgaAckFields::version field
    ///     @li @b infoCode for @ref MgaAckFields::infoCode field
    ///     @li @b msgId for @ref MgaAckFields::msgId field
    ///     @li @b msgPayloadStart for @ref MgaAckFields::msgPayloadStart field
    COMMS_MSG_FIELDS_ACCESS(
        type,
        version,
        infoCode,
        msgId,
        msgPayloadStart
    );

    /// @brief Default constructor
    MgaAck() = default;

    /// @brief Copy constructor
    MgaAck(const MgaAck&) = default;

    /// @brief Move constructor
    MgaAck(MgaAck&& other) = default;

    /// @brief Destructor
    ~MgaAck() = default;

    /// @brief Copy assignment
    MgaAck& operator=(const MgaAck&) = default;

    /// @brief Move assignment
    MgaAck& operator=(MgaAck&&) = default;
};

}  // namespace message

}  // namespace ublox

