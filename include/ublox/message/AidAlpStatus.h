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
///     See @ref AidAlpStatusFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AidAlpStatus : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALP>,
        comms::option::FieldsImpl<AidAlpStatusFields::All>,
        comms::option::MsgType<AidAlpStatus<TMsgBase> >,
        comms::option::DispatchImpl,
        comms::option::MsgDoRead
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALP>,
        comms::option::FieldsImpl<AidAlpStatusFields::All>,
        comms::option::MsgType<AidAlpStatus<TMsgBase> >,
        comms::option::DispatchImpl,
        comms::option::MsgDoRead
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_status, ///< status field, see @ref AidAlpStatusFields::status
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        AidAlpStatusFields::status& status; ///< status field, see @ref AidAlpStatusFields::status
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const AidAlpStatusFields::status& status; ///< status field, see @ref AidAlpStatusFields::status
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, status);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

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

    /// @brief Provide custom read functionality.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        auto& allFields = Base::fields();
        auto& statusField = std::get<FieldIdx_status>(allFields);
        if (len != statusField.length()) {
            return comms::ErrorStatus::InvalidMsgData;
        }

        return Base::doRead(iter, len);
    }

};


}  // namespace message

}  // namespace ublox





