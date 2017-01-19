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
/// @brief Contains definition of LOG-RETRIEVESTRING message and its fields.

#pragma once

#include "ublox/Message.h"
#include "ublox/field/log.h"

namespace ublox
{

namespace message
{

/// @brief Accumulates details of all the LOG-RETRIEVESTRING message fields.
/// @see LogRetrievestring
struct LogRetrievestringFields
{
    /// @brief Definition of "entryIndex" field.
    using entryIndex  = field::common::U4;

    /// @brief Definition of "version" field.
    using version =
        field::common::U1T<
            comms::option::ValidNumValueRange<0, 0>
        >;

    /// @brief Definition of "reserved1" field.
    using reserved1 = field::common::res1;

    /// @brief Definition of "year" field.
    using year = field::log::year;

    /// @brief Definition of "month" field.
    using month = field::log::month;

    /// @brief Definition of "day" field.
    using day = field::log::day;

    /// @brief Definition of "hour" field.
    using hour = field::log::hour;

    /// @brief Definition of "minute" field.
    using minute = field::log::minute;

    /// @brief Definition of "second" field.
    using second = field::log::second;

    /// @brief Definition of "reserved2" field.
    using reserved2 = field::common::res1;

    /// @brief Definition of "byteCount" field.
    using byteCount = field::common::U2;

    /// @brief Definition of "bytes" field.
    using bytes =
        field::common::StringT<
            comms::option::SequenceSizeForcingEnabled
        >;

    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        entryIndex,
        version,
        reserved1,
        year,
        month,
        day,
        hour,
        minute,
        second,
        reserved2,
        byteCount,
        bytes
    >;
};

/// @brief Definition of LOG-RETRIEVESTRING message
/// @details Inherits from @b comms::MessageBase
///     while providing @b TMsgBase as common interface class as well as
///     various implementation options. @n
///     See @ref LogRetrievestringFields and for definition of the fields this message contains
///         and COMMS_MSG_FIELDS_ACCESS() for fields access details.
/// @tparam TMsgBase Common interface class for all the messages.
template <typename TMsgBase = Message>
class LogRetrievestring : public
    comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_RETRIEVESTRING>,
        comms::option::FieldsImpl<LogRetrievestringFields::All>,
        comms::option::MsgType<LogRetrievestring<TMsgBase> >,
        comms::option::HasDoRefresh
    >
{
    typedef comms::MessageBase<
        TMsgBase,
        comms::option::StaticNumIdImpl<MsgId_LOG_RETRIEVESTRING>,
        comms::option::FieldsImpl<LogRetrievestringFields::All>,
        comms::option::MsgType<LogRetrievestring<TMsgBase> >,
        comms::option::HasDoRefresh
    > Base;
public:

    /// @brief Allow access to internal fields.
    /// @details See definition of @b COMMS_MSG_FIELDS_ACCESS macro
    ///     related to @b comms::MessageBase class from COMMS library
    ///     for details.
    ///
    ///     The field names are:
    ///     @li @b entryIndex for @ref LogRetrievestringFields::entryIndex field
    ///     @li @b version for @ref LogRetrievestringFields::version field
    ///     @li @b reserved1 for @ref LogRetrievestringFields::reserved1 field
    ///     @li @b year for @ref LogRetrievestringFields::year field
    ///     @li @b month for @ref LogRetrievestringFields::month field
    ///     @li @b day for @ref LogRetrievestringFields::day field
    ///     @li @b hour for @ref LogRetrievestringFields::hour field
    ///     @li @b minute for @ref LogRetrievestringFields::minute field
    ///     @li @b second for @ref LogRetrievestringFields::second field
    ///     @li @b reserved2 for @ref LogRetrievestringFields::reserved2 field
    ///     @li @b byteCount for @ref LogRetrievestringFields::byteCount field
    ///     @li @b bytes for @ref LogRetrievestringFields::bytes field
    COMMS_MSG_FIELDS_ACCESS(Base,
        entryIndex,
        version,
        reserved1,
        year,
        month,
        day,
        hour,
        minute,
        second,
        reserved2,
        byteCount,
        bytes
    );

    /// @brief Default constructor
    LogRetrievestring() = default;

    /// @brief Copy constructor
    LogRetrievestring(const LogRetrievestring&) = default;

    /// @brief Move constructor
    LogRetrievestring(LogRetrievestring&& other) = default;

    /// @brief Destructor
    virtual ~LogRetrievestring() = default;

    /// @brief Copy assignment
    LogRetrievestring& operator=(const LogRetrievestring&) = default;

    /// @brief Move assignment
    LogRetrievestring& operator=(LogRetrievestring&&) = default;

    /// @brief Provides custom read functionality.
    /// @details The number of characters in @b bytes (@ref LogRetrievestringFields::bytes)
    ///     string is determined by the value of @b byteCount
    ///     (@ref LogRetrievestringFields::byteCount) field.
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        auto es = Base::template readFieldsUntil<FieldIdx_bytes>(iter, len);
        if (es != comms::ErrorStatus::Success) {
            return es;
        }

        auto& allFields = Base::fields();
        auto& countField = std::get<FieldIdx_byteCount>(allFields);
        auto& bytesField = std::get<FieldIdx_bytes>(allFields);
        bytesField.forceReadElemCount(countField.value());

        return Base::template readFieldsFrom<FieldIdx_bytes>(iter, len);
    }

    /// @brief Provides custom refresh functionality
    /// @details The value of @b byteCount (@ref LogRetrievestringFields::byteCount)
    ///     field is determined by the size of the internal string of
    ///     @b bytes (@ref LogRetrievestringFields::bytes) field.
    /// @return @b true in case the value of "byteCount" field was modified, @b false otherwise
    bool doRefresh()
    {
        auto& allFields = Base::fields();
        auto& countField = std::get<FieldIdx_byteCount>(allFields);
        auto& bytesField = std::get<FieldIdx_bytes>(allFields);
        if (countField.value() == bytesField.value().size()) {
            return false;
        }

        countField.value() = bytesField.value().size();
        return true;
    }

};


}  // namespace message

}  // namespace ublox

