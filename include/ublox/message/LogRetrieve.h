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
/// @brief Contains definition of LOG-RETRIEVE message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/common.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the LOG-RETRIEVE message fields.
/// @see LogRetrieve
struct LogRetrieveFields
{
    /// @brief Definition of "startNumber" field.
    using startNumber = field::common::U4;

    /// @brief Definition of "entryCount" field.
    using entryCount =
        field::common::U4T<
            comms::option::ValidNumValueRange<0, 256>
        >;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved" field.
    using reserved = field::common::res3;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        startNumber,
        entryCount,
        version,
        reserved
    >;
};

/// @brief Definition of LOG-RETRIEVE message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref LogRetrieveFields and for definition of the fields this message contains.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class LogRetrieve : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_RETRIEVE>,
        comms::option::FieldsImpl<LogRetrieveFields::All>,
        comms::option::MsgType<LogRetrieve<TMsgBase> >
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_RETRIEVE>,
        comms::option::FieldsImpl<LogRetrieveFields::All>,
        comms::option::MsgType<LogRetrieve<TMsgBase> >
    > Base;
public:

#ifdef FOR_DOXYGEN_DOC_ONLY
    /// @brief Index to access the fields
    enum FieldIdx
    {
        FieldIdx_startNumber, ///< @b startNumber field, see @ref LogRetrieveFields::startNumber
        FieldIdx_entryCount, ///< @b entryCount field, see @ref LogRetrieveFields::entryCount
        FieldIdx_version, ///< @b version field, see @ref LogRetrieveFields::version
        FieldIdx_reserved, ///< @b reserved field, see @ref LogRetrieveFields::reserved
        FieldIdx_numOfValues ///< number of available fields
    };

    /// @brief Access to fields bundled as a struct
    struct FieldsAsStruct
    {
        LogRetrieveFields::startNumber& startNumber; ///< @b startNumber field, see @ref LogRetrieveFields::startNumber
        LogRetrieveFields::entryCount& entryCount; ///< @b entryCount field, see @ref LogRetrieveFields::entryCount
        LogRetrieveFields::version& version; ///< @b version field, see @ref LogRetrieveFields::version
        LogRetrieveFields::reserved& reserved; ///< @b reserved field, see @ref LogRetrieveFields::reserved
    };

    /// @brief Access to @b const fields bundled as a struct
    struct ConstFieldsAsStruct
    {
        const LogRetrieveFields::startNumber& startNumber; ///< @b startNumber field, see @ref LogRetrieveFields::startNumber
        const LogRetrieveFields::entryCount& entryCount; ///< @b entryCount field, see @ref LogRetrieveFields::entryCount
        const LogRetrieveFields::version& version; ///< @b version field, see @ref LogRetrieveFields::version
        const LogRetrieveFields::reserved& reserved; ///< @b reserved field, see @ref LogRetrieveFields::reserved
    };

    /// @brief Get access to fields bundled into a struct
    FieldsAsStruct fieldsAsStruct();

    /// @brief Get access to @b const fields bundled into a struct
    ConstFieldsAsStruct fieldsAsStruct() const;

#else
    COMMS_MSG_FIELDS_ACCESS(Base, startNumber, entryCount, version, reserved);
#endif // #ifdef FOR_DOXYGEN_DOC_ONLY

    /// @brief Default constructor
    LogRetrieve() = default;

    /// @brief Copy constructor
    LogRetrieve(const LogRetrieve&) = default;

    /// @brief Move constructor
    LogRetrieve(LogRetrieve&& other) = default;

    /// @brief Destructor
    virtual ~LogRetrieve() = default;

    /// @brief Copy assignment
    LogRetrieve& operator=(const LogRetrieve&) = default;

    /// @brief Move assignment
    LogRetrieve& operator=(LogRetrieve&&) = default;
};


}  // namespace message

}  // namespace ublox

