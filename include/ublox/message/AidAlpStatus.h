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
///     data transfer. @b
///     Inherits from
///     <a href="https://dl.dropboxusercontent.com/u/46999418/comms_champion/comms/html/classcomms_1_1MessageBase.html">comms::MessageBase</a>
///     while providing @b TMsgBase as common interface class as well as
///     @b comms::option::StaticNumIdImpl, @b comms::option::FieldsImpl, and
///     @b comms::option::DispatchImpl as options. @n
///     See @ref AidAlpStatusFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AidAlpStatus : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALP>,
        comms::option::FieldsImpl<AidAlpStatusFields::All>,
        comms::option::DispatchImpl<AidAlpStatus<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALP>,
        comms::option::FieldsImpl<AidAlpStatusFields::All>,
        comms::option::DispatchImpl<AidAlpStatus<TMsgBase> >
    > Base;
public:

    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_status, ///< status field, see @ref AidAlpStatusFields::status
        FieldIdx_numOfValues ///< number of available fields
    };

    static_assert(std::tuple_size<typename Base::AllFields>::value == FieldIdx_numOfValues,
        "Number of fields is incorrect");

    /// @brief Default constructor
    AidAlpStatus() = default;

    /// @brief Copy constructor
    AidAlpStatus(const AidAlpStatus&) = default;

    /// @brief Move constructor
    AidAlpStatus(AidAlpStatus&& other) = default;

    /// @brief Destructor
    virtual ~AidAlpStatus() = default;

    /// @brief Copy assignment
    AidAlpStatus& operator=(const AidAlpStatus&) = default;

    /// @brief Move assignment
    AidAlpStatus& operator=(AidAlpStatus&&) = default;

protected:
    virtual comms::ErrorStatus readImpl(
        typename Base::ReadIterator& iter,
        std::size_t len) override
    {
        auto& allFields = Base::fields();
        auto& statusField = std::get<FieldIdx_status>(allFields);
        if (len != statusField.length()) {
            return comms::ErrorStatus::InvalidMsgData;
        }

        return Base::readImpl(iter, len);
    }

};


}  // namespace message

}  // namespace ublox





