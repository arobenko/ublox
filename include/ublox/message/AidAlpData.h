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
/// @brief Contains definition of AID-ALP (<b>data transfer</b>) message
///     and its fields.

#pragma once

#include "comms/Message.h"
#include "ublox/Message.h"

#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the AID-ALP (<b>data transfer</b>)
///     message fields.
/// @see AidAlpData
struct AidAlpDataFields
{
    /// @brief Definition of "status" field.
    using alpData = field::common::ListT<field::common::U2>;


    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        alpData
    >;
};

/// @brief Definition of AID-ALP  (<b>data transfer</b>) message
/// @details
///     This message is sent as an intput to the receiver. @n
///     Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref AidAlpDataFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class AidAlpData : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALP>,
        comms::option::FieldsImpl<AidAlpDataFields::All>,
        comms::option::MsgType<AidAlpData<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_AID_ALP>,
        comms::option::FieldsImpl<AidAlpDataFields::All>,
        comms::option::MsgType<AidAlpData<TMsgBase> >
    > Base;
public:
#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_alpData, ///< alpData field, see @ref AidAlpDataFields::alpData
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        AidAlpDataFields::alpData& alpData; ///< alpData field, see @ref AidAlpDataFields::alpData
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const AidAlpDataFields::alpData& alpData; ///< alpData field, see @ref AidAlpDataFields::alpData
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, id);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    AidAlpData() = default;

    /// @brief Copy constructor
    AidAlpData(const AidAlpData&) = default;

    /// @brief Move constructor
    AidAlpData(AidAlpData&& other) = default;

    /// @brief Destructor
    virtual ~AidAlpData() = default;

    /// @brief Copy assignment
    AidAlpData& operator=(const AidAlpData&) = default;

    /// @brief Move assignment
    AidAlpData& operator=(AidAlpData&&) = default;
};


}  // namespace message

}  // namespace ublox





