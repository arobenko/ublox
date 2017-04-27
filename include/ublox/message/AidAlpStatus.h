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
/// @brief Contains definition of AID-ALP (<b>data transfer status</b>) message
///     and its fields.

#pragma once

#include <iterator>

#include "comms/Message.h"
#include "ublox/Message.h"

#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the AID-ALP (<b>data transfer status</b>)
///     message fields.
/// @see AidAlpStatus
struct AidAlpStatusFields
{
    /// @brief Enumerator for available statuses
    enum class Status : std::uint8_t
    {
        NAK, ///< Indicates NAK status message
        ACK, ///< Indicates ACK status message
        NumOfValues ///< Number of available values
    };

    /// @brief Definition of "status" field.
    using status =
        field::common::EnumT<
            Status,
            comms::option::ValidNumValueRange<0, (int)Status::NumOfValues - 1>
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        status
    >;
};

/// @brief Definition of AID-ALP  (<b>data transfer status</b>) message
/// @details
///     This message is sent by the receiver as a response to @ref AidAlpData
///     message with either @b ack or @b nak status values. @n
///     @b NOTE, that it can also be sent to the receiver to indicate end of the
///     data transfer. @n
///     Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref AidAlpStatusFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AidAlpStatus : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALP>,
        comms::option::FieldsImpl<AidAlpStatusFields::All>,
        comms::option::MsgType<AidAlpStatus<TMsgBase> >
    >
{
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b status for @ref AidAlpStatusFields::status field
    COMMS_MSG_FIELDS_ACCESS(status);

    /// @brief Default constructor
    AidAlpStatus() = default;

    /// @brief Copy constructor
    AidAlpStatus(const AidAlpStatus&) = default;

    /// @brief Move constructor
    AidAlpStatus(AidAlpStatus&& other) = default;

    /// @brief Destructor
    ~AidAlpStatus() = default;

    /// @brief Copy assignment
    AidAlpStatus& operator=(const AidAlpStatus&) = default;

    /// @brief Move assignment
    AidAlpStatus& operator=(AidAlpStatus&&) = default;

    /// @brief Provide custom read functionality.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        using Base = typename std::decay<decltype(comms::toMessageBase(*this))>::type;
        if (len != field_status().length()) {
            return comms::ErrorStatus::InvalidMsgData;
        }

        return Base::doRead(iter, len);
    }

};


}  // namespace message

}  // namespace ublox





